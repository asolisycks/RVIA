#define MAIN
//#include "C_PostgreSQL.hpp"
//#include "C_Utils.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <format>  // C++20
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <string>
#include <vector>


#include "C_PostgreSQL.hpp"
#include "C_Utils.h"

static std::string obtenerTokenDB(const long lEmpleado, std::string sToken, std::string& sTokenDB, std::string& sExpiraDB)
{
    C_PostgreSQL objPSQL;
    C_Utils      objUtils;

    if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
    {
        std::cerr << "EXCEPCION CAPTURADA CONNECT TOKEN: " << objPSQL.getLastError() << '\n';
    }
    else
    {
        std::string  sSQL = STRING_EMPTY;

        sSQL.append(objUtils.stringFormat("SELECT fun_obtener_token('%ld'::integer, '%s');", lEmpleado, sToken.c_str()));

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
                    sToken = STRING_EMPTY;

                    sToken.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);

                    sToken.erase(std::remove(sToken.begin(), sToken.end(), '('), sToken.end());
                    sToken.erase(std::remove(sToken.begin(), sToken.end(), ')'), sToken.end());
                    sToken.erase(std::remove(sToken.begin(), sToken.end(), '\"'), sToken.end());
                    sToken.erase(std::remove(sToken.begin(), sToken.end(), '"'), sToken.end());
 
                    // Cambia las letras con acentos por letras sin acentos
                    std::string acentos = "áéíóúÁÉÍÓÚ";
                    std::string sin_acentos = "aeiouAEIOU";

                    for (size_t i = 0; i < sToken.size(); ++i)
                    {
                        size_t pos = acentos.find(sToken[i]);
                        if (pos != std::string::npos) {
                            sToken[i] = sin_acentos[pos];
                        }
                    }

                    char* next_token1 = NULL;
                    char* prtTok = NULL;
                    char cTok[10000] = { 0 };

                    memcpy_s(cTok, sizeof(cTok), sToken.c_str(), sToken.length());
                    prtTok = strtok_s(cTok, ",", &next_token1);

                    std::cout << "Token " << sToken << std::endl;

                    int iCont = 0;
                    while (prtTok != NULL)
                    {
                        iCont++;

                        switch (iCont)
                        {
                            case 1: 
                                sTokenDB = STRING_EMPTY;                                
                                sTokenDB.append(prtTok);
                                break;
                            case 2:
                                sExpiraDB = STRING_EMPTY;
                                sExpiraDB.append(prtTok);
                            break;
                        default:
                            break;
                        }

                        prtTok = strtok_s(NULL, ",", &next_token1);
                    }
                    prtTok = NULL;
                    next_token1 = NULL;
                }
            }

            vcstRecords.clear();
        }

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return sTokenDB + sExpiraDB;
}

//Bueno
static bool registrarToken(long lEmpleado, std::string sToken, std::string sFecha)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    C_PostgreSQL objPSQL;
    C_Utils objUtils;

    if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
    {
        std::cerr << "EXCEPCION CAPTURADA AL QUERER GRABAR EL TOKEN: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_token( '%ld'::BIGINT, '%s'::VARCHAR, '%s'::TIMESTAMP );",
            lEmpleado, sToken.c_str(), sFecha.c_str()));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "EXCEPCION CAPTURADA QUERY EXEC: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    bReturn = true;
                    //sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

// Enumeración para el resultado de la validación del token
enum class ResultadoValidacion
{
    Exito,
    ErrorAperturaArchivo,
    ErrorTokenNoCoincide,
    ErrorTokenExpirado
};

// Comprueba si el token proporcionado es válido
ResultadoValidacion esTokenValido2(std::string& sTokenProporcionado, const std::string &sFechaProporcionado)
{
    std::string sToken = " ";
    std::string sFecha = " ";

    if (sTokenProporcionado.length() == 0)
    {
        // Leer el token y la fecha de expiración del archivo
        std::ifstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
        if (!tokenFile.is_open())
        {
            std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA LEER EL TOKEN.\n";
            return ResultadoValidacion::ErrorAperturaArchivo;
        }

        std::getline(tokenFile, sToken);  // Leer el token
        sTokenProporcionado = sToken;
        std::getline(tokenFile, sFecha);  // Leer la fecha de expiración
    }
    else
    {
        obtenerTokenDB(90329121L, sTokenProporcionado, sToken, sFecha);
	}

    // Convierte la fecha de expiración a time_t
    std::tm fechaExpiracion = {};
    std::istringstream ss(sFecha);
    ss >> std::get_time(&fechaExpiracion, "%Y-%m-%d %H:%M:%S");
    std::time_t tExpiracion = std::mktime(&fechaExpiracion);

    std::cout << "Token proporcionado " << sTokenProporcionado << std::endl;
    std::cout << "Token guardado en archivo o BD " << sToken << std::endl;
    std::cout << "Fecha guardada en archivo o BD " << sFecha << std::endl;

    // Comprobar si el token proporcionado coincide con el token guardado
    if (sTokenProporcionado != sToken)
    {
        return ResultadoValidacion::ErrorTokenNoCoincide;
    }

    // Comprobar si la fecha y hora actuales son anteriores a la fecha de expiración
    auto ahora = std::chrono::system_clock::now();
    std::time_t tAhora = std::chrono::system_clock::to_time_t(ahora);


    if (tAhora > tExpiracion)
    {
        return ResultadoValidacion::ErrorTokenExpirado;
    }

    return ResultadoValidacion::Exito;
}

// Genera un token seguro de la longitud especificada
static std::string generarTokenSeguro(int longitud) 
{
    std::vector<unsigned char> buffer(longitud);

    // Genera un número aleatorio seguro
    if (RAND_bytes(buffer.data(), buffer.size()) != 1)
    {
        std::cerr << "Error al generar el número aleatorio.\n";
        return "";
    }

    // Crea un objeto de contexto para el hash
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr)
    {
        std::cerr << "Error al crear el objeto de contexto para el hash.\n";
        return "";
    }

    // Inicializa el objeto de contexto para usar SHA256
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1)
    {
        std::cerr << "Error al inicializar el objeto de contexto para usar SHA256.\n";
        EVP_MD_CTX_free(context);
        return "";
    }

    // Actualiza el hash con el número aleatorio
    if (EVP_DigestUpdate(context, buffer.data(), buffer.size()) != 1)
    {
        std::cerr << "Error al actualizar el hash con el número aleatorio.\n";
        EVP_MD_CTX_free(context);
        return "";
    }

    // Finaliza el hash y obtiene el resultado
    //unsigned char hash[EVP_MD_get_size(EVP_sha256())];
    std::vector<unsigned char> hash(EVP_MD_get_size(EVP_sha256()));
    unsigned int lengthOfHash = 0;
    if (EVP_DigestFinal_ex(context, hash.data(), &lengthOfHash) != 1)
    {
        std::cerr << "Error al finalizar el hash y obtener el resultado.\n";
        EVP_MD_CTX_free(context);
        return "";
    }

    // Libera el objeto de contexto
    EVP_MD_CTX_free(context);

    // Convierte el hash a una cadena hexadecimal
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < lengthOfHash; ++i)
    {
        ss << std::setw(2) << static_cast<int>(hash[i]);
    }

    return ss.str();
}

//NOTA: El siguiente código es una versión anterior de la función esTokenValido. 
// La versión actualizada se encuentra en el archivo main.cpp. en la función esTokenValido2.
////bool esTokenValido(const std::string& tokenProporcionado)
////{
////    // Leer el token y la fecha de expiración del archivo
////    std::ifstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
////    if (!tokenFile.is_open())
////    {
////        std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA LEER EL TOKEN.\n";
////        return false;
////    }
////
////    std::string tokenGuardado;
////    std::getline(tokenFile, tokenGuardado);  // Leer el token
////
////    std::string sFechaExpiracion;
////    std::getline(tokenFile, sFechaExpiracion);  // Leer la fecha de expiración
////
////    // Convierte la fecha de expiración a time_t
////    std::tm fechaExpiracion = {};
////    std::istringstream ss(sFechaExpiracion);
////    ss >> std::get_time(&fechaExpiracion, "%Y-%m-%d %H:%M:%S");
////    std::time_t tExpiracion = std::mktime(&fechaExpiracion);
////
////    // Comprobar si el token proporcionado coincide con el token guardado
////    if (tokenProporcionado != tokenGuardado)
////    {
////        return false;
////    }
////
////    // Comprobar si la fecha y hora actuales son anteriores a la fecha de expiración
////    auto ahora = std::chrono::system_clock::now();
////    std::time_t tAhora = std::chrono::system_clock::to_time_t(ahora);
////    if (tAhora > tExpiracion)
////    {
////        return false;
////    }
////
////    return true;
////}

int main(int argc, char* argv[])
{
    std::cout << "argc: " << argc << std::endl;
    std::cout << "argv[0]: " << argv[0] << std::endl;

    if (argc > 1)
    {
		int iArg1 = std::stoi(argv[1]);

        if (iArg1 == 1)
        {
            std::string sToken = generarTokenSeguro(32);  // Genera un token seguro de 32 bytes
            std::cout << "TOKEN GENERADO: " << sToken << "\n";

            // Calcula la fecha de expiración del token (5 minutos a partir de ahora)
            auto ahora = std::chrono::system_clock::now();
            auto expiracion = ahora + std::chrono::minutes(1);
            std::time_t tExpiracion = std::chrono::system_clock::to_time_t(expiracion);
            std::tm fechaExpiracion;
            localtime_s(&fechaExpiracion, &tExpiracion);
            std::stringstream ss;
            ss << std::put_time(&fechaExpiracion, "%Y-%m-%d %H:%M:%S");
            std::string sFechaExpiracion = ss.str();

            // Guarda el token y su fecha de expiración en un archivo
            std::ofstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
            if (tokenFile.is_open())
            {
                tokenFile << sToken << "\n";
                tokenFile << sFechaExpiracion << "\n";
                tokenFile.close();
            }
            else
            {
                std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA GUARDAR EL TOKEN.\n";
            }

            std::cout << "Se ha generado un token" << std::endl;

            registrarToken(90329121L, sToken, sFechaExpiracion);
        }
        else if (iArg1 == 2)
        {
			std::string sTokenProporcionado;
            std::string sFechaProporcionado;

			std::ifstream tokenFile2("c:\\sys\\progs\\parse\\bito\\token.txt");
            if (tokenFile2.is_open())
            {
				std::getline(tokenFile2, sTokenProporcionado);
				tokenFile2.close();
			}
            else
            {
				std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA LEER EL TOKEN.\n";
			}   
            
            // Comprueba si el token proporcionado es válido
			//std::string tokenProporcionado = /* el token proporcionado por el usuario */;
			ResultadoValidacion resultado = esTokenValido2(sTokenProporcionado, sFechaProporcionado);
            switch (resultado)
            {
			case ResultadoValidacion::Exito:
				std::cout << "El token es válido.\n";
				break;
			case ResultadoValidacion::ErrorAperturaArchivo:
				std::cout << "No se pudo abrir el archivo para leer el token.\n";
				break;
			case ResultadoValidacion::ErrorTokenNoCoincide:
				std::cout << "El token proporcionado no coincide con el token guardado.\n";
				break;
			case ResultadoValidacion::ErrorTokenExpirado:
				std::cout << "El token ha expirado.\n";
				break;
			}
		}
    }
    else
    {
		std::cout << "No se proporcionaron argumentos.\n";
	}
    
    return 0;
}