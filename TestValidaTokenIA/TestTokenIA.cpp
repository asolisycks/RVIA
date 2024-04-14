#include <iostream>
#include <string>
#include <format>  // C++20
#include <ctime>
#include <cstdlib>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <fstream>  // Para manejar archivos
#include <locale>
#include <random>
#include <map>

#include "C_PostgreSQL.hpp"
#include "C_Utils.h"

// Estructura para almacenar la información del token
struct TokenInfo 
{
    std::time_t expiryTime;
};

// Mapa para almacenar los tokens generados
std::map<std::string, TokenInfo> tokens;

// Función para verificar si un token es válido
bool verificarToken(std::string token) 
{
    std::time_t now = std::time(0);

    std::cout << "Token: " << token << std::endl;
    std::cout << "Expiry time: " << tokens[token].expiryTime << std::endl;
    if (tokens.count(token) > 0 && tokens[token].expiryTime > now) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

int main() 
{
    // Lee el token y su tiempo de expiración de un archivo
    std::string token;
    std::time_t expiryTime;
    std::ifstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
    
    if (tokenFile.is_open()) 
    {
        getline(tokenFile, token);
        tokenFile >> expiryTime;
        tokenFile.close();
        tokens[token] = { expiryTime };
    }
    else 
    {
        std::cout << "No se pudo abrir el archivo para leer el token.\n";
        return 1;
    }

    // Verifica el token
    if (verificarToken(token)) 
    {
        std::cout << "El token es válido.\n";
    }
    else 
    {
        std::cout << "El token no es válido o ha expirado.\n";
    }

    return 0;
}

std::string obtenerTokenDB(const long lEmpleado, std::string &sTokenDB, std::string &sExpiraDB)
{
    std::string sToken      = STRING_EMPTY;
    
    sTokenDB    = STRING_EMPTY;
    sExpiraDB   = STRING_EMPTY;

    C_PostgreSQL objPSQL;
    C_Utils      objUtils;

    if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
    {
        std::cerr << "EXCEPCION CAPTURADA CONNECT TOKEN: " << objPSQL.getLastError() << '\n';
    }
    else
    {
        std::string  sSQL = STRING_EMPTY;

        sSQL.append(objUtils.stringFormat("SELECT fun_obtener_token('%ld'::integer);", lEmpleado));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "EXCEPCION CAPTURADA QUERY: " << objPSQL.getLastError() << '\n';
        }
        else
        {
            std::vector<ES_Records> vcstRecords;

            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //sToken.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);

                    //// Reemplaza los paréntesis y las comillas dobles por espacios en blanco
                    //std::replace(sToken.begin(), sToken.end(), '(', ' ');
                    //std::replace(sToken.begin(), sToken.end(), ')', ' ');
                    //std::replace(sToken.begin(), sToken.end(), '\"', ' ');
                    //std::replace(sToken.begin(), sToken.end(), '"', ' ');

                    //// Cambia las letras con acentos por letras sin acentos
                    //std::string acentos = "áéíóúÁÉÍÓÚ";
                    //std::string sin_acentos = "aeiouAEIOU";

                    //for (size_t i = 0; i < sToken.size(); ++i)
                    //{
                    //    size_t pos = acentos.find(sToken[i]);
                    //    if (pos != std::string::npos) {
                    //        sToken[i] = sin_acentos[pos];
                    //    }
                    //}

                    //char* next_token1 = NULL;
                    //char* prtTok = NULL;
                    //char cTok[10000] = { 0 };

                    //memcpy_s(cTok, sizeof(cTok), sToken.c_str(), sToken.length());
                    //prtTok = strtok_s(cTok, ",", &next_token1);

                    //int iCont = 0;
                    //while (prtTok != NULL)
                    //{
                    //    iCont++;

                    //    switch (iCont)
                    //    {
                    //    //case 1:
                    //    //    break;
                    //    //case 2: // 
                    //    //    sTokenDB.append(prtTok);
                    //    //    // Elimina los espacios en blanco
                    //    //    sTokenDB.erase(std::remove(sTokenDB.begin(), sTokenDB.end(), ' '), sTokenDB.end());
                    //    //    break;
                    //    case 1: //
                    //        sExpiraDB.append(prtTok);
                    //        sTokenDB = sTokenDB + "," + prtTok;

                            try
                            {
                                
                                std::tm expires_at;
                                std::istringstream ss(vcstRecords[j].vcValues[i]);
                                ss >> std::get_time(&expires_at, "%Y-%m-%d %H:%M:%S");

                                std::time_t now = std::time(0);
                                double seconds = difftime(now, mktime(&expires_at));

                                if (seconds > 0)
                                {
                                    std::cout << "El token es válido" << std::endl;
                                    //return true;
                                }
                                else
                                {
                                    std::cout << "El token no es válido" << std::endl;
                                    //return false;
                                }
                            }
                            catch (const std::exception& e)
                            {
                                std::cerr << e.what() << std::endl;
                            }

     //                       break;
     //                   default:
     //                       break;
					//	}

					//	prtTok = strtok_s(NULL, ",", &next_token1);
					//}

     //               prtTok = NULL;
     //               next_token1 = NULL;
                }
            }

            vcstRecords.clear();
        }

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return sToken;
}

//--------------------------
// Aplicacion2.cpp
// Verificar la vigencia del token
static bool esTokenValido(std::string token) 
{
    try 
    {
        std::tm expires_at;
        std::istringstream ss(token.c_str());
        ss >> std::get_time(&expires_at, "%Y-%m-%d %H:%M:%S");

        std::time_t now = std::time(0);
        double seconds = difftime(now, mktime(&expires_at));

        if (seconds > 0) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    return false;
}

static bool esFormatoFechaCorrecto(const std::string& fecha)
{
    std::tm tm = {};
    std::istringstream ss(fecha);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) 
    {
        return false;
    }
    else
    {
        return true;
    }
}

//int main()
//{
//    std::string token;
//    //std::cout << "Introduce el token: ";
//    //std::cin >> token;
//    
//    long lEmpleado = 90329121L; 
//    std::string sTokenDB  = STRING_EMPTY;
//    std::string sExpiraDB = STRING_EMPTY;
//
//    token = obtenerTokenDB(lEmpleado, sTokenDB, sExpiraDB );
//
//    if (esFormatoFechaCorrecto(sExpiraDB))
//    {
//        std::cout << "El formato de la fecha es correcto." << std::endl;
//    }
//    else
//    {
//        std::cout << "El formato de la fecha es incorrecto." << std::endl;
//    }
//
//    // Verificar la vigencia del token
//    if (esTokenValido(sExpiraDB))
//    {
//        std::cout << "El token es válido" << std::endl;
//    }
//    else 
//    {
//        std::cout << "El token no es válido" << std::endl;
//    }
//
//    return 0;
//}
