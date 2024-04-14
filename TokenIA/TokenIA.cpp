#define MAIN

#include <windows.h>
#include <chrono>
#include <iostream>
#include <string>
#include <format>  // C++20
#include <ctime>
#include <cstdlib>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>
#include <fstream>  // Para manejar archivos
#include <locale>
#include <random>
#include <codecvt>

#include "C_PostgreSQL.hpp"
#include "C_Utils.h"

//Bueno
//static bool registrarToken(long lEmpleado, std::string sToken, std::string sFecha)
//{
//    bool bReturn = false;
//    std::string sSQL = STRING_EMPTY;
//    std::string sResp = STRING_EMPTY;
//
//    std::vector<ES_Records> vcstRecords;
//
//    C_PostgreSQL objPSQL;
//    C_Utils objUtils;
//
//    if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
//    {
//        std::cerr << "EXCEPCION CAPTURADA AL QUERER GRABAR EL TOKEN: " << objPSQL.getLastError() << '\n';
//        bReturn = false;
//    }
//    else
//    {
//        bReturn = false;
//        -- INSERT
//        sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
//        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_token( '%ld'::BIGINT, '%s'::VARCHAR, '%s'::VARCHAR );",
//            lEmpleado, sToken.c_str(), sFecha.c_str()));
//
//        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
//        {
//            std::cerr << "EXCEPCION CAPTURADA QUERY EXEC: " << objPSQL.getLastError() << '\n';
//            bReturn = false;
//        }
//        else
//        {
//            objPSQL.getRecords(vcstRecords);
//
//            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
//            {
//                for (int j = 0; j < vcstRecords.size(); j++)
//                {
//                    csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
//                    iRespuesta = _ttoi(csResp);
//                    bReturn = true;
//                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
//                }
//            }
//        }
//
//        sSQL = STRING_EMPTY;
//
//        objPSQL.clearRecords();
//        objPSQL.closeConnection();
//    }
//
//    return bReturn;
//}

// Función para generar un token seguro
//static std::string generarToken()
//{
//    unsigned char temp[SHA256_DIGEST_LENGTH];  // Temporal array
//    char buf[2*SHA256_DIGEST_LENGTH + 1];
//    memset(buf, 0x0, 2*SHA256_DIGEST_LENGTH);
//    memset(temp, 0x0, SHA256_DIGEST_LENGTH);
//
//    // Genera un número aleatorio
//    int random = std::rand();
//
//    // Convierte el número aleatorio a una cadena
//    std::string randomString = std::format("{}", random);  // C++20
//
//    // Calcula el hash SHA-256 del número aleatorio
//    SHA256((unsigned char*)randomString.c_str(), randomString.length(), temp);
//
//    for (int i=0; i < SHA256_DIGEST_LENGTH; i++) 
//    {
//        sprintf_s((char*)&(buf[i*2]), 3, "%02x", temp[i]);  // Usa sprintf_s en lugar de sprintf
//    }
//
//    return std::string(buf);
//}

// Función para desencriptar los datos
static std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

    int out_len1 = (int)ciphertext.size();
    int out_len2 = 0;
    unsigned char* out = (unsigned char*)malloc(out_len1);

    EVP_DecryptUpdate(ctx, out, &out_len1, (unsigned char*)ciphertext.c_str(), (int)ciphertext.size());
    EVP_DecryptFinal_ex(ctx, out + out_len1, &out_len2);

    std::string plaintext((char*)out, out_len1 + out_len2);
    free(out);
    EVP_CIPHER_CTX_free(ctx);

    return plaintext;
}

static bool getDataFileINI(std::string& decrypted_ipname, std::string& decrypted_dbname, std::string& decrypted_dbport, std::string& decrypted_dbuser,
    std::string& decrypted_dbpass, const int iDataBase)
{
    // Leer los datos encriptados del archivo rvia.ini
    std::string line = STRING_EMPTY;
    std::string encrypted_ipname_read = STRING_EMPTY;
    std::string encrypted_dbname_read = STRING_EMPTY;
    std::string encrypted_dbport_read = STRING_EMPTY;
    std::string encrypted_dbuser_read = STRING_EMPTY;
    std::string encrypted_dbpass_read = STRING_EMPTY;
    std::string sFileINI = STRING_EMPTY;

    std::string key = "jasrkey";  // Reemplazar con la generación de clave real
    std::string iv  = "jasriv";   // Reemplazar con la generación de IV real
    
    // 1 = Producción
    // 2 = Desarrollo
    if (iDataBase == 1)
    {
        sFileINI = "C:\\sys\\progs\\parse\\prorvia.ini";
    }
    else
    {
        sFileINI = "C:\\sys\\progs\\parse\\devrvia.ini";
    }

    //validar si existe el archivo.
    std::ifstream in(sFileINI);
    if (!in)
    {
        std::cerr << "No se pudieron obtener los datos de conexión." << std::endl;
        return false;
    }

    while (std::getline(in, line))
    {
        if (line.find("PI=") == 0) encrypted_ipname_read = line.substr(3);
        else if (line.find("DB=") == 0) encrypted_dbname_read = line.substr(3);
        else if (line.find("PORT=") == 0) encrypted_dbport_read = line.substr(5);
        else if (line.find("USR=") == 0) encrypted_dbuser_read = line.substr(4);
        else if (line.find("PW=") == 0) encrypted_dbpass_read = line.substr(3);
    }
    in.close();

    // Desencriptar los datos
    decrypted_ipname = decrypt(encrypted_ipname_read, key, iv);
    decrypted_dbname = decrypt(encrypted_dbname_read, key, iv);

    // Eliminar JASR del nombre de la base de datos.
    decrypted_dbname.erase(decrypted_dbname.size() - 4, 4);

    decrypted_dbport = decrypt(encrypted_dbport_read, key, iv);
    decrypted_dbuser = decrypt(encrypted_dbuser_read, key, iv);
    decrypted_dbpass = decrypt(encrypted_dbpass_read, key, iv);

    return true;
}

// Generar un token aleatorio seguro usando OpenSSL
static bool registrarToken(long lEmpleado, std::string sToken, std::string sFecha, const int iParam)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    C_PostgreSQL objPSQL;
    C_Utils objUtils;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iParam);

    //if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
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

// Genera un token seguro de la longitud especificada
static std::string generarTokenSeguro(int longitud)
{
    std::vector<unsigned char> buffer(longitud);

    // Genera un número aleatorio seguro
    if (RAND_bytes(buffer.data(), (int)buffer.size()) != 1)
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

int main(int argc, char* argv[])
{
    std::locale::global(std::locale("es_MX.UTF8"));
    setlocale(LC_ALL, "es_MX.UTF8");

    std::string sPath;
    std::string lEmpleadoStr;
    long lEmpleado = 0L; 
    int iParam = 0;

    if (argc > 1)
    {
        try
        {
            iParam = atoi(argv[1]);

            //Selecciona el archivo de configuración de producción o desarrollo
            // 1 = Producción
            // 2 = Desarrollo
            // Diferente a 1 o 2 = Salir
            if (iParam == 1 || iParam == 2)
            {
                do
                {
                    std::cout << "INGRESE EL NUMERO DE EMPLEADO: ";
                    std::cin >> lEmpleadoStr;

                    try
                    {
                        lEmpleado = std::stol(lEmpleadoStr);
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << "Error: " << e.what() << '\n';
                        continue;
                    }

                    if (lEmpleado <= 9000000 || lEmpleado >= 99999999)
                    {
                        std::cout << "EL NUMERO DE EMPLEADO DEBE SER MAYOR A 9000000 Y MENOR A 99999999.\n";
                    }
                    else
                    {
                        break;
                    }
                } while (true);

                std::string sToken = generarTokenSeguro(32);  // Genera un token seguro de 32 bytes
                //std::string sToken = generarToken();
                std::cout << "TOKEN GENERADO: " << sToken << "\n";

                // Calcula la fecha de expiración del token (5 minutos a partir de ahora)
                auto ahora = std::chrono::system_clock::now();
                //auto expiracion = ahora + std::chrono::minutes(1); // El token expira después de 1 minutos
                auto expiracion = ahora + std::chrono::hours(72); // El token expira después de 72 horas
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

                if (registrarToken(lEmpleado, sToken, sFechaExpiracion, iParam))
                {
                    std::cout << "Token guardado en la base de datos.\n";
                }
                else
                {
                    std::cerr << "Error al guardar el token en la base de datos.\n";
                }

                //// Guarda el token y su tiempo de expiración en un archivo
                //std::ofstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
                //if (tokenFile.is_open()) 
                //{
                //    tokenFile << sToken;
                //    std::cout << sToken << std::endl;
                //    //std::string sFecha = std::format("{:%Y-%m-%d %H:%M:%S}", std::time(0) + 72 * 60 * 60);
                //    //std::cout << std::time(0) + 72 * 60 * 60 << std::endl;
                //    //tokenFile << std::time(0) + 72 * 60 * 60;  // El token expira después de 72 horas
                //    //tokenFile << sFecha;
                //    std::cout << std::time(0) + 1 * 60 << std::endl;
                //    tokenFile << std::time(0) + 1 * 60;  // El token expira después de 1 minutos
                //    tokenFile.close();

                //    //registrarToken(lEmpleado, sToken, sFecha);
                //} 
                //else 
                //{
                //    std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA GUARDAR EL TOKEN.\n";
                //}    
            }
            else
            {
                std::cerr << "Error: Debe seleccionar 1 para producción o 2 para desarrollo.\n";
                return 0;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            //std::cerr << "Error: Debe seleccionar 1 para producción o 2 para desarrollo.\n";
			return 0;
        }
    }
    else
    {
		std::cerr << "NO SE PROPORCIONO EL PARAMETRO DE ENTORNO" << ":(" << std::endl;
        
        //const char* src = "\U0001F622";  // Emoji de tristeza
        //int src_len = strlen(src);

        //// Convertir de UTF-8 a UTF-16
        //int wlen = MultiByteToWideChar(CP_UTF8, 0, src, src_len, NULL, 0);
        //wchar_t* wstr = new wchar_t[wlen + 1];
        //MultiByteToWideChar(CP_UTF8, 0, src, src_len, wstr, wlen);
        //wstr[wlen] = 0;

        //// Convertir de UTF-16 a ANSI
        //int len = WideCharToMultiByte(CP_ACP, 0, wstr, wlen, NULL, 0, NULL, NULL);
        //char* str = new char[len + 1];
        //WideCharToMultiByte(CP_ACP, 0, wstr, wlen, str, len, NULL, NULL);
        //str[len] = 0;

        //std::cout << str << std::endl;

        //delete[] wstr;
        //delete[] str;

	}
    

    return 0;
}

//// Generar un token aleatorio
//static std::string generarToken() 
//{
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(0, 15);
//
//    std::string token;
//    for (int n = 0; n < 64; ++n) 
//    {
//        int randomNum = dis(gen);
//        token.append(std::to_string(randomNum));
//    }
//
//    //unsigned char temp[SHA256_DIGEST_LENGTH];  // Temporal array
//    //    char buf[2*SHA256_DIGEST_LENGTH + 1];
//    //    memset(buf, 0x0, 2*SHA256_DIGEST_LENGTH);
//    //    memset(temp, 0x0, SHA256_DIGEST_LENGTH);
//
//    unsigned char hash[SHA256_DIGEST_LENGTH];
//    SHA256_CTX sha256;
//    SHA256_Init(&sha256);
//    SHA256_Update(&sha256, token.c_str(), token.size());
//    SHA256_Final(hash, &sha256);
//
//    std::stringstream ss;
//    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
//    {
//        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
//    }
//
//    return ss.str();
//}

////// Generar un token aleatorio
////std::string generarToken() 
////{
////    std::random_device rd;
////    std::mt19937 gen(rd());
////    std::uniform_int_distribution<> dis(0, 15);
////
////    std::string token;
////    for (int n = 0; n < 64; ++n) 
////    {
////        int randomNum = dis(gen);
////        token.append(std::to_string(randomNum));
////    }
////
////    unsigned char hash[EVP_MAX_MD_SIZE];
////    unsigned int hash_len;
////    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
////    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
////    EVP_DigestUpdate(ctx, token.c_str(), token.size());
////    EVP_DigestFinal_ex(ctx, hash, &hash_len);
////    EVP_MD_CTX_free(ctx);
////
////    std::stringstream ss;
////    for (unsigned int i = 0; i < hash_len; i++)
////    {
////        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
////    }
////
////    return ss.str();
////}

////// Guardar el token en la base de datos
////static void guardarToken(std::string sToken, long &lEmpleado)
////{
////    try
////    {
////        //std::time_t t = std::time(0);
////        //std::tm now;
////        //localtime_s(&now, &t);
////        //std::stringstream ss;
////        //ss << std::put_time(&now, "%Y-%m-%d %H:%M:%S");
////        //std::string sFecha = ss.str();
////
////        std::time_t t_exp = std::time(0) + 5 * 60; // 5 minutes from now
////        std::tm exp;
////        localtime_s(&exp, &t_exp);
////        std::stringstream ss_exp;
////        ss_exp << std::put_time(&exp, "%Y-%m-%d %H:%M:%S");
////        std::string sFechaExp = ss_exp.str();
////
////        registrarToken(lEmpleado, sToken, sFechaExp);
////        std::cout << "Token guardado: " << sToken << std::endl;
////    }
////    catch (const std::exception& e) 
////    {
////        std::cerr << e.what() << std::endl;
////    }
////}
////
////int main() 
////{
////    std::string lEmpleadoStr    = " ";
////    long        lEmpleado       = 0L;
////
////    do
////    {
////        std::cout << "INGRESE EL NUMERO DE EMPLEADO: ";
////        std::cin >> lEmpleadoStr;
////    
////        try
////        {
////            lEmpleado = std::stol(lEmpleadoStr);
////        }
////        catch (const std::exception& e)
////        {
////            std::cerr << "Error: " << e.what() << '\n';
////            continue;
////        }
////    
////        if (lEmpleado <= 9000000 || lEmpleado >= 99999999)
////        {
////            std::cout << "EL NUMERO DE EMPLEADO DEBE SER MAYOR A 9000000 Y MENOR A 99999999.\n";
////        }
////        else
////        {
////            break;
////        }
////    } while (true);
////
////    std::string sToken = generarToken();
////    guardarToken(sToken, lEmpleado);
////
////    return 0;
////}
