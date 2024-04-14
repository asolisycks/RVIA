// IniEncryptDecryptRVIA.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <fstream>
#include <string>

// Función para encriptar los datos
std::string encrypt(const std::string& plaintext, const std::string& key, const std::string& iv) 
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

    int out_len1 = (int)plaintext.size() + 16;
    int out_len2 = 0;
    unsigned char* out = (unsigned char*)malloc(out_len1);

    EVP_EncryptUpdate(ctx, out, &out_len1, (unsigned char*)plaintext.c_str(), (int)plaintext.size());
    EVP_EncryptFinal_ex(ctx, out + out_len1, &out_len2);

    std::string ciphertext((char*)out, out_len1 + out_len2);
    free(out);
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext;
}

// Función para desencriptar los datos
std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv) 
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

// Función para solicitar la entrada de datos
std::string requestInput(const std::string& prompt) 
{
    std::string input;

    do 
    {
        std::cout << prompt;
        std::getline(std::cin, input);
    } while (input.size() < 3);

    return input;
}

int main(int _argc, char* _argv[])
{
    std::locale::global(std::locale("es_MX.UTF8"));
    setlocale(LC_ALL, "es_MX.UTF8");

    std::string sPath;// = _argv[1];

    try
    {
        if (_argc > 1)
        {
            int iParam = atoi(_argv[1]);

			if (iParam == 1)
			{
				sPath = "C:\\sys\\progs\\parse\\prorvia.ini";
			}
            else if (iParam == 2)
            {
				sPath = "C:\\sys\\progs\\parse\\devrvia.ini";
			}
			else
			{
				return 0;
			}

            // Solicitar la entrada de datos
            std::string ipname = requestInput("Introduce el número de la IP: ");
            std::string dbname = requestInput("Introduce el nombre de la base de datos: ");

            // Agregamos JASR al nombre de la base de datos.
            dbname += "jasr";
            std::string dbport = requestInput("Introduce el puerto de la base de datos: ");
            std::string dbuser = requestInput("Introduce el usuario de la base de datos: ");
            std::string dbpass = requestInput("Introduce la contraseña de la base de datos: ");

            // Generar una clave e IV aleatorios
            std::string key = "jasrkey";  // Reemplazar con la generación de clave real
            std::string iv = "jasriv";   // Reemplazar con la generación de IV real

            // Encriptar los datos
            std::string encrypted_ipname = encrypt(ipname, key, iv);
            std::string encrypted_dbname = encrypt(dbname, key, iv);
            std::string encrypted_dbport = encrypt(dbport, key, iv);
            std::string encrypted_dbuser = encrypt(dbuser, key, iv);
            std::string encrypted_dbpass = encrypt(dbpass, key, iv);

            // Guardar los datos encriptados en el archivo rvia.ini
            std::ofstream out(sPath);
            out << "[CVFIGA]" << std::endl;
            out << "PI=" << encrypted_ipname << std::endl;
            out << "DB=" << encrypted_dbname << std::endl;
            out << "PORT=" << encrypted_dbport << std::endl;
            out << "USR=" << encrypted_dbuser << std::endl;
            out << "PW=" << encrypted_dbpass << std::endl;
            out.close();


            // Leer los datos encriptados del archivo rvia.ini
            std::ifstream in(sPath);
            std::string line;
            std::string encrypted_ipname_read, encrypted_dbname_read, encrypted_dbport_read, encrypted_dbuser_read, encrypted_dbpass_read;

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
            std::string decrypted_ipname = decrypt(encrypted_ipname_read, key, iv);
            std::string decrypted_dbname = decrypt(encrypted_dbname_read, key, iv);

            // Eliminar JASR del nombre de la base de datos.
            decrypted_dbname.erase(decrypted_dbname.size() - 4, 4);

            std::string decrypted_dbport = decrypt(encrypted_dbport_read, key, iv);
            std::string decrypted_dbuser = decrypt(encrypted_dbuser_read, key, iv);
            std::string decrypted_dbpass = decrypt(encrypted_dbpass_read, key, iv);

            // Imprimir los datos desencriptados
            std::cout << "Nombre de la IP: " << decrypted_ipname << std::endl;
            std::cout << "Nombre de la base de datos: " << decrypted_dbname << std::endl;
            std::cout << "Puerto de la base de datos: " << decrypted_dbport << std::endl;
            std::cout << "Usuario de la base de datos: " << decrypted_dbuser << std::endl;
            std::cout << "Contraseña de la base de datos: " << decrypted_dbpass << std::endl;
		}
        else
        {
            std::cerr << "No se proporcionó el parámetro de entorno" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
		std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
