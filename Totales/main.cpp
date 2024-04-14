#define MAIN

//Claro, aquí tienes un ejemplo de cómo podrías hacerlo en C++20. Este código lee un archivo llamado `archivo.txt` y almacena la información de los programas de programación en un arreglo de estructuras.
//```cpp
#include <format>  // C++20
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <regex>

//Claro, aquí tienes un ejemplo de cómo podrías hacerlo en C++20. Este código lee un archivo llamado `archivo.txt` y almacena la información de los programas de programación en un arreglo de estructuras.También maneja correctamente los nombres de lenguajes que contienen más de una palabra.
//
//```cpp
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>

struct Programa
{
    std::string lenguaje;
    int archivos;
    int lineasBlanco;
    int comentarios;
    int lineasCodigo;

    Programa() : lenguaje(""), archivos(0), lineasBlanco(0), comentarios(0), lineasCodigo(0) {}
};

int main()
{
    std::ifstream archivo("C:\\Temp\\Bito\\test\\cobrosproveedorintranet\\totales.txt");
    std::string linea;
    std::vector<Programa> programas;

    if (archivo.is_open())
    {
        while (getline(archivo, linea))
        {
            if (linea.find("---------------------------------------------------------------------------------") != std::string::npos)
            {
                continue;
            }

            while (getline(archivo, linea))
            {
                if (linea.find("---------------------------------------------------------------------------------") != std::string::npos)
                {
                    continue;
                }

                if (linea.find("Language                       files          blank        comment           code") != std::string::npos)
                {
                    continue;
                }

                if (linea.find("SUM:") != std::string::npos )
                {
                    continue;
                }

                std::string s = linea; // "VB for Applications                1              4              2              6";

                // Separa las palabras y los números
                std::regex words_regex("[^\\s+]+");
                auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
                auto words_end = std::sregex_iterator();

                Programa p; // Nueva instancia de Programa
                std::vector<int> numbers; // Nuevo vector numbers

                for (std::sregex_iterator i = words_begin; i != words_end; ++i)
                {
                    std::smatch match = *i;
                    std::string match_str = match.str();
                    if (std::all_of(match_str.begin(), match_str.end(), ::isalpha))
                    {
                        p.lenguaje += match_str + " ";
                    }
                    else if (std::all_of(match_str.begin(), match_str.end(), ::isdigit))
                    {
                        numbers.push_back(std::stoi(match_str));
                    }
                }

                p.lenguaje.erase(p.lenguaje.end() - 1); // Elimina el último espacio

                // Asigna los números a las variables de la estructura
                if (numbers.size() >= 4)
                {
                    p.archivos      = numbers[0];
                    p.lineasBlanco  = numbers[1];
                    p.comentarios   = numbers[2];
                    p.lineasCodigo  = numbers[3];
                }

                programas.push_back(p);
            }
            break;
        }
        archivo.close();

        for (const auto& p : programas)
        {
            std::cout << p.lenguaje << "," << p.archivos << "," << p.lineasBlanco << "," << p.comentarios << "," << p.lineasCodigo << std::endl;
        }

        programas.clear();

    }
    else
    {
        std::cout << "No se pudo abrir el archivo";
    }

    return 0;
}
//```
//
//Por favor, asegúrate de que el archivo `archivo.txt` esté en el mismo directorio que tu programa y tenga el formato correcto.Este código no maneja errores de formato en el archivo.

//////struct Programa 
//////{
//////    std::string lenguaje;
//////    int archivos;
//////    int lineasBlanco;
//////    int comentarios;
//////    int lineasCodigo;
//////
//////    Programa() : lenguaje(""), archivos(0), lineasBlanco(0), comentarios(0), lineasCodigo(0) {}
//////};
//////
//////int main() 
//////{
//////    std::ofstream arcCSV("C:\\Temp\\Bito\\test\\cobrosproveedorintranet\\totales.csv");
//////
//////    std::ifstream archivo("C:\\Temp\\Bito\\test\\cobrosproveedorintranet\\totales.txt");
//////    std::string linea;
//////    
//////
//////    std::vector<Programa> programas;
//////
//////    if (archivo.is_open())
//////    {
//////        linea.clear();
//////        while (getline(archivo, linea))
//////        {
//////            if (linea.find("-------------------------------------------------------------------------------") != std::string::npos)
//////            {
//////                continue;
//////            }
//////
//////            while (getline(archivo, linea))
//////            {
//////                if (linea.find("-------------------------------------------------------------------------------") != std::string::npos)
//////                {
//////                    continue;
//////                }
//////
//////                //if (linea.find("Language") != std::string::npos)
//////                //{
//////                //    continue;
//////                //}
//////
//////                Programa p;
//////                std::istringstream iss(linea);
//////                iss >> p.lenguaje >> p.archivos >> p.lineasBlanco >> p.comentarios >> p.lineasCodigo;
//////                programas.push_back(p);
//////            }
//////            break;
//////        }
//////        archivo.close();
//////    }
//////    else 
//////    {
//////        std::cout << "No se pudo abrir el archivo";
//////    }
//////
//////    std::cout << "Lenguaje,Archivos,Lineas en blanco, Comentarios, Lineas de codigo" << std::endl;
//////    arcCSV << "Lenguaje,Archivos,Lineas en blanco, Comentarios, Lineas de codigo" << std::endl;
//////    // Imprimir los programas
//////    for (const auto& p : programas)
//////    {
//////        std::cout << p.lenguaje << "," << p.archivos << "," << p.lineasBlanco << "," << p.comentarios << "," << p.lineasCodigo << std::endl;
//////        arcCSV << p.lenguaje << "," << p.archivos << "," << p.lineasBlanco << "," << p.comentarios << "," << p.lineasCodigo << std::endl;
//////    }
//////
//////    programas.clear();
//////    arcCSV.close();
//////
//////    std::cout << "Presione una tecla para terminar" << std::endl;
//////    int i = _getch();
//////
//////    return 0;
//////}
////////```
////////Por favor, asegúrate de que el archivo `archivo.txt` esté en el mismo directorio que tu programa y tenga el formato correcto.Este código no maneja errores de formato en el archivo.