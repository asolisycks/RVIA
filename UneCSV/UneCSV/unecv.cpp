#include "xlsxwriter.h"
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

// Función para leer un archivo CSV en un vector de strings.
std::vector<std::string> read_csv(const char* filename) 
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> data;

    while (std::getline(file, line)) 
    {
        data.push_back(line);
    }

    return data;
}

// Función para escribir los datos en una hoja de trabajo de Excel.
void write_to_worksheet(lxw_worksheet* worksheet, const std::vector<std::string>& data) 
{
    int row = 0;

    for (const auto& line : data) 
    {
        int col = 0;
        std::string cell;
        std::istringstream line_stream(line);

        while (std::getline(line_stream, cell, '|')) 
        {
            worksheet_write_string(worksheet, row, col, cell.c_str(), NULL);
            col++;
        }

        row++;
    }
}

int main(int argc, char* argv[]) 
{
    /* Comprobar el número de argumentos. */
    if (argc != 7) 
    {
        std::cerr << "Uso: " << argv[0] << " <archivo1.csv> <archivo2.csv> <archivo3.csv> <archivo4.csv> <archivo5.csv> <salida.xlsx>\n";
        return 1;
    }

    /* Leer los archivos CSV. */
    std::vector<std::string> data1 = read_csv(argv[1]);
    std::vector<std::string> data2 = read_csv(argv[2]);
    std::vector<std::string> data3 = read_csv(argv[3]);
    std::vector<std::string> data4 = read_csv(argv[4]);
    std::vector<std::string> data5 = read_csv(argv[5]);

    /* Crear un nuevo libro de trabajo y agregar dos hojas de trabajo. */
    lxw_workbook*  workbook     = workbook_new(argv[6]);
    lxw_worksheet* worksheet1   = workbook_add_worksheet(workbook, "totales");
    lxw_worksheet* worksheet2   = workbook_add_worksheet(workbook, "sentencias");
    lxw_worksheet* worksheet3   = workbook_add_worksheet(workbook, "obsoleto");
    lxw_worksheet* worksheet4   = workbook_add_worksheet(workbook, "IA_bito");
    lxw_worksheet* worksheet5   = workbook_add_worksheet(workbook, "finProyecto");

    /* Escribir los datos en las hojas de trabajo. */
    write_to_worksheet(worksheet1, data1);
    write_to_worksheet(worksheet2, data2);
    write_to_worksheet(worksheet3, data3);
    write_to_worksheet(worksheet4, data4);
    write_to_worksheet(worksheet5, data5);

    /* Guardar el archivo de Excel y liberar la memoria. */
    workbook_close(workbook);

    return 0;
}
