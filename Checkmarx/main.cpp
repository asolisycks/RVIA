#define MAIN

#include <iostream>
#include <string>
#include <curl/curl.h>

// Esta función se utiliza para escribir la respuesta de la API en una cadena
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* out) 
{
    size_t totalSize = size * nmemb;
    out->append((char*)contents, totalSize);
    return totalSize;
}

int main() 
{
    // Inicializa CURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error al inicializar CURL" << std::endl;
        return 1;
    }

    // Configura la URL de la API de Checkmarx
    std::string url = "https://checkmarx.example.com/cxrestapi/auth/identity/connect/token";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Configura los parámetros de la solicitud POST
    std::string postFields = "username=your_username&password=your_password&grant_type=password&scope=sast_rest_api&client_id=resource_owner_client&client_secret=014DF517-39D1-4453-B7B3-9930C563627C";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

    // Configura la función de devolución de llamada para escribir la respuesta
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Realiza la solicitud
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Error al realizar la solicitud: " << curl_easy_strerror(res) << std::endl;
    }
    else {
        std::cout << "Respuesta: " << response << std::endl;
    }

    // Limpia CURL
    curl_easy_cleanup(curl);

    return 0;
}


// ----------------------------- EJEMPLO MASTER ---------------------------------------
//#include <ctime>
//#include <filesystem>
//#include <fstream>
//#include <fstream>
//#include <iostream>
//#include <map>
//#include <sstream>
//#include <string>
//#include <vector>
//
//// Función para dividir una línea en tokens
//static std::vector<std::string> split(const std::string& s) {
//    std::vector<std::string> tokens;
//    std::string token;
//    std::istringstream tokenStream(s);
//    bool inQuotes = false;
//
//    for (char c : s) {
//        if (c == '\"') {
//            inQuotes = !inQuotes;
//        }
//        else if (c == ',' && !inQuotes) {
//            tokens.push_back(token);
//            token = "";
//        }
//        else {
//            token += c;
//        }
//    }
//    tokens.push_back(token); // Añadir el último token
//
//    return tokens;
//}
//
//static std::string getFilenameSinCheckmarx(const std::string& filePath)
//{
//    std::filesystem::path path(filePath);
//    return path.stem().string();
//}
//
//
//int main() 
//{
//    std::string filePath = "C:\\Temp\\Bito\\checkmarx_cobrosproveedorintranet.csv";
//    std::string projectName = getFilenameSinCheckmarx(filePath);
//    projectName.erase(0, 10); // Remove "checkmarx_"
//
//    std::cout << "File name without extension: " << projectName << std::endl;
//
//    std::ifstream file(filePath);
//    std::string line;
//    std::getline(file, line); // Leer la primera línea (cabecera)
//
//    std::map<std::string, int> severityCount;
//    std::vector<std::vector<std::string>> items;
//    std::string sFecha;
//
//    while (std::getline(file, line)) 
//    {
//        auto tokens = split(line);
//        sFecha = tokens[1]; // Fecha de detección
//        severityCount[tokens[14]]++; // Contar severidades
//        //Eliminar las comillas dobles de los campos del tokens[7] y guardar en otro archivo con el nombre de proyecto_items.csv y repetando la cabecera original.
//        // Eliminar las comillas dobles de los campos del tokens[7]
//        std::string field7 = tokens[7];
//        field7.erase(std::remove(field7.begin(), field7.end(), '\"'), field7.end());
//        tokens[7] = field7;
//        items.push_back(tokens); // Guardar los items
//    }
//
//    // Generar el archivo proyecto_cabecera.csv
//    std::string fileDest = "C:\\Temp\\Bito\\checkmarx_cobrosproveedorintranet_tot.csv";
//    std::ofstream out1(fileDest);
//    out1 << "\"ID Proyecto\",\"Nombre Proyecto\",\"High\",\"Medium\",\"Low\",\"Detection Date\"\n";
//    out1 << "\"1\",\"" << projectName << "\",\"" << severityCount["High"] << "\",\"" << severityCount["Medium"] << "\",\"" << severityCount["Low"] << "\",\"" << sFecha << "\"\n";
//
//    // Guardar en otro archivo con el nombre de proyecto_items.csv y respetando la cabecera original
//    std::ofstream out2("C:\\Temp\\Bito\\proyecto_items.csv", std::ios::app);
//    if (out2.tellp() == 0) 
//    {
//        out2 << "\"Project\",\"Id\",\"Detection Date\",\"Direct Link\",\"Query Name\",\"Source Folder\",\"Source Filename\",\"Source Line\",\"Source Object\",\"Destination Folder\",\"Destination Filename\",\"Destination Line\",\"Destination Object\",\"Result State\",\"Severity\",\"Result Severity\",\n";
//    }
//
//    for (const auto& item : items)
//    {
//        out2 << "\"" << projectName << "\",\"" << item[0] << "\",\"" << item[1] << "\",\"" << item[2] << "\",\"" << item[3] << "\",\"" << item[4] << "\",\"" << item[5] << "\",\"" << item[6] << "\",\"" << item[7] << "\",\"" << item[8] << "\",\"" << item[9] << "\",\"" << item[10] << "\",\"" << item[11] << "\",\"" << item[12] << "\",\"" << item[13] << "\",\"" << item[14] << "\"\n";
//    }
//
//    return 0;
//}


//---------------------------------------------- Ejemplo 1 ----------------------------------------------
////#include <ctime>
////#include <filesystem>
////#include <fstream>
////#include <iostream>
////#include <map>
////#include <sstream>
////#include <string>
////#include <vector>
////
////std::string getFileNameWithoutExtension(const std::string& filePath)
////{
////    std::filesystem::path path(filePath);
////    return path.stem().string();
////}
////
////// Función para dividir una línea en tokens
////std::vector<std::string> split(const std::string& s, char delimiter) 
////{
////    std::vector<std::string> tokens;
////    std::string token;
////    std::istringstream tokenStream(s);
////    
////    while (std::getline(tokenStream, token, delimiter)) 
////    {
////        tokens.push_back(token);
////    }
////    return tokens;
////}
////
////int main() 
////{
////    std::string filePath = "C:\\Temp\\Bito\\cobrosproveedorintranet.csv";
////    std::string fileNameWithoutExtension = getFileNameWithoutExtension(filePath);
////    std::cout << "File name without extension: " << fileNameWithoutExtension << std::endl;
////
////    std::ifstream file(filePath);
////    std::string line;
////    std::getline(file, line); // Leer la primera línea (cabecera)
////
////    std::map<std::string, int> severityCount;
////    std::vector<std::vector<std::string>> items;
////
////    while (std::getline(file, line)) 
////    {
////        //Elimina caracteres \" y \" y "".
////        //line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
////        //line.erase(std::remove(line.begin(), line.end(), '\''), line.end());
////        //line.erase(std::remove(line.begin(), line.end(), '\\'), line.end());
////        //line.erase(std::remove(line.begin(), line.end(), '""'), line.end());
////
////        auto tokens = split(line, ',');
////        severityCount[tokens[34]]++; // Contar severidades
////        items.push_back(tokens); // Guardar los items
////    }
////
////    // Generar el archivo proyecto_cabecera.csv
////    std::ofstream out1("C:\\Temp\\Bito\\proyecto_cabecera.csv");
////    out1 << "\"ID Proyecto\",\"Nombre Proyecto\",\"Altas\",\"Medias\",\"Bajas\",\"Fecha Actual\"\n";
////    out1 << "\"1\",\"" << fileNameWithoutExtension << "\",\"" << severityCount["High"] << "\",\"" << severityCount["Medium"] << "\",\"" << severityCount["Low"] << "\",\"" << std::time(0) << "\"\n";
////
////    // Generar el archivo proyecto_items.csv
////    std::ofstream out2("C:\\Temp\\Bito\\proyecto_items.csv");
////    out2 << "\"ID Proyecto\",\"SrcFileName\",\"Line\",\"Column\",\"NodeId\",\"Name\",\"DestFileName\",\"DestLine\",\"DestColumn\",\"DestNodeId\",\"DestName\",\"Result State\",\"Result Severity\",\"Link\",\"Detection Date\"\n";
////    
////    for (const auto& item : items) 
////    {
////        out2 << "\"1\",\"" << item[23] << "\",\"" << item[24] << "\",\"" << item[25] << "\",\"" << item[26] << "\",\"" << item[27] << "\",\"" << item[28] << "\",\"" << item[29] << "\",\"" << item[30] << "\",\"" << item[31] << "\",\"" << item[32] << "\",\"" << item[33] << "\",\"" << item[34] << "\",\"" << item[35] << "\",\"" << item[36] << "\"\n";
////    }
////
////    return 0;
////}
