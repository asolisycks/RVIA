#include "CIA.hpp"

// Identificar sentencias SQL
std::regex patternSql(R"((SELECT|INSERT|UPDATE|DELETE|ALTER TABLE|EXEC|select|insert|update|delete|alter table|exec|LOGIN|PASSWORD|DB_SERVER|sqlsrv:Server|ibm:DRIVER|dblib:host|odbc:Driver|informix:DSN=InformixDB|query\()\s.*)", std::regex_constants::icase);
std::smatch matchesSql;

std::regex patternObs(R"((call_user_method|call_user_method_array|define_syslog_variables|ereg|ereg_replace|eregi|eregi_replace|set_magic_quotes_runtime|session_register|session_unregister|session_is_registered|set_socket_blocking|split|spliti|sql_regcase|mysql_db_query|mysql_escape_string|mcrypt_generic_end|mysql_list_dbs|\$HTTP_RAW_POST_DATA|always_populate_raw_post_data|iconv|mbstring|salt|password_hash|capture_session_meta|ldap_sort|png2wbmp|jpeg2wbmp|__autoload|track_errors|\$php_errormsg|mbstring\.func_overload|unset|parse_str|gmp_random|fgetss|strip_tags|real|is_real|mysqli_connect|is_wctype|_loaddll|_unloaddll|_getdllprocaddr|_seterrormode|_beep|_sleep|_getsystime|_setsystime|_cgets|_cgetws|gets|_getws|_get_output_format))");
//std::regex patternObs(R"((call_user_method\(|call_user_method_array\(|define_syslog_variables\(|dl\(|ereg\(|ereg_replace\(|eregi\(|eregi_replace\(|set_magic_quotes_runtime\(|session_register\(|session_unregister\(|session_is_registered\(|set_socket_blocking\(|split\(|spliti\(|sql_regcase\(|mysql_db_query\(|mysql_escape_string\(|mcrypt_generic_end\(|mysql_list_dbs\(|\\$HTTP_RAW_POST_DATA|always_populate_raw_post_data|iconv|mbstring|salt|password_hash\(|capture_session_meta|ldap_sort\(|png2wbmp\(|jpeg2wbmp\(|__autoload\(|track_errors|\\$php_errormsg|mbstring.func_overload|\(unset\)|parse_str\(|gmp_random\(|fgetss\(|string.strip_tags|\(real\)|is_real\(|mysqli_connect\()\s.*)", std::regex_constants::icase);
//std::regex patternO(R"((call_user_method\(|call_user_method_array\(|define_syslog_variables\(|dl\(|ereg\(|ereg_replace\(|eregi\(|eregi_replace\(|set_magic_quotes_runtime\(|session_register\(|session_unregister\(|session_is_registered\(|set_socket_blocking\(|split\(|spliti\(|sql_regcase\(|mysql_db_query\(|mysql_escape_string\(|mcrypt_generic_end\(|mysql_list_dbs\(|\\$HTTP_RAW_POST_DATA|always_populate_raw_post_data|iconv|mbstring|salt|password_hash\(|capture_session_meta|ldap_sort\(|png2wbmp\(|jpeg2wbmp\(|__autoload\(|track_errors|\\$php_errormsg|mbstring.func_overload|\(unset\)|parse_str\(|gmp_random\(|fgetss\(|string.strip_tags|\(real\)|is_real\(|mysqli_connect\()|is_wctype\(|_loaddll\(|_unloaddll\(|_getdllprocaddr\(|_seterrormode\(|_beep\(|_sleep\(|_getsystime\(|_setsystime\(|_cgets\(|_cgetws\(|gets\(|_getws\(|_get_output_format\()\s.*)", std::regex_constants::icase);
std::smatch matchesObs;

CIA::CIA(std::string sNombreProyecto, long lNumColaborador)
{
    sNomProyecto = sNombreProyecto;
    lColaborador = lNumColaborador;
}

CIA::~CIA()
{
}

//Generar un ID de proyecto único
long CIA::generarIDProyecto()
{
    long lNumerico = 0L;

    // Generar un número aleatorio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 999); // Rango ajustado para garantizar no más de 3 dígitos

    // Obtener la fecha y hora actuales
    auto ahora = std::chrono::system_clock::now();
    std::time_t tAhora = std::chrono::system_clock::to_time_t(ahora);
    std::tm fechaHora;
    localtime_s(&fechaHora, &tAhora); // Cambio a localtime_s

    std::ostringstream ss;
    ss << std::put_time(&fechaHora, "%Y%m"); // Solo año, mes y día

    // Generar un ID de proyecto único
    std::string sID = std::to_string(distrib(gen)) + ss.str();

    // Convertir el ID del proyecto a un número entero
    lNumerico = std::stoll(sID);

    return lNumerico;
}


// Comprueba si el token proporcionado es válido
ResultadoValidacion CIA::esTokenValidoDB(const long lEmpleado, std::string sTokenProporcionado, const int iDataBase)
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
        tokenFile.close();
    }
    else
    {
        obtenerTokenDB(lEmpleado, sTokenProporcionado, sToken, sFecha, iDataBase);
    }

    // Convierte la fecha de expiración a time_t
    std::tm fechaExpiracion = {};
    std::istringstream ss(sFecha);
    ss >> std::get_time(&fechaExpiracion, "%Y-%m-%d %H:%M:%S");
    std::time_t tExpiracion = std::mktime(&fechaExpiracion);

    //std::cout << "Token proporcionado " << sTokenProporcionado << std::endl;
    //std::cout << "Token guardado en archivo o BD " << sToken << std::endl;
    //std::cout << "Fecha guardada en archivo o BD " << sFecha << std::endl;

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

//void CIA::menu() 
//{
//    system("cls");
//    std::cout << "                                          " << std::endl;
//    std::cout << "        Seleccione una opción:            " << std::endl;
//    std::cout << "__________________________________________" << std::endl;
//    std::cout << "F1   Obtener totales                      " << std::endl;
//    std::cout << "F2   Buscar sentencias SQL                " << std::endl;
//    std::cout << "F3   Buscar funciones obsoletas           " << std::endl;
//    //std::cout << "F4   Convertir con BITO                   " << std::endl;
//    std::cout << "F5   Calcular la Fecha Fin de Proyecto    " << std::endl;
//    std::cout << "F6   Todas las opciones anteriores        " << std::endl;
//    std::cout << "F7   Obtener totales por extensión        " << std::endl;
//    std::cout << "F8   Convertir con BITO no reprocesados   " << std::endl;
//    std::cout << "ESC. Salir                                " << std::endl;
//    std::cout << " " << std::endl;
//}

void CIA::menu()
{
    system("cls");
    std::locale::global(std::locale("es_MX.UTF8"));
    setlocale(LC_ALL, "es_MX.UTF8");
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "            Seleccione una opción:            " << std::endl;
    std::cout << "______________________________________________" << std::endl;
    std::cout << "F1   Obtener Totales del Proyecto Completo.   " << std::endl;
    std::cout << "F2   Buscar Sentencias SQL.                   " << std::endl;
    std::cout << "F3   Buscar Funciones obsoletas.              " << std::endl;
    std::cout << "F4   Calcular la Fecha Fin de Proyecto.       " << std::endl;
    std::cout << "F5   Obtener totales por extensión.           " << std::endl;
    std::cout << "F6   Convertir con BITO(Todos las anteriores)." << std::endl;
    std::cout << "ESC. Salir.                                   " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << " " << std::endl;
}

void CIA::printProgramInfo()
{
    std::string trademark = "JASR™";
    std::string author = "JOSE ARTURO SOLIS RAMIREZ";
    std::string version = "1.0.0";
    std::string creationDate = "06 de Diciembre, 2023";
    std::string company = "Coppel S.A. de C.V.";

    std::cout << "Marca Registrada: " << trademark << std::endl;
    std::cout << "Realizado por: " << author << std::endl;
    std::cout << "Ver: " << version << std::endl;
    std::cout << "Fecha de Creacion: " << creationDate << std::endl;
    std::cout << "Empresa: " << company << std::endl;
}

int CIA::pathFileCreatedCSV(std::string sPathFileCreatedCSV)
{
    int iRet = 0;

    std::string pathTotales = sPathFileCreatedCSV + "\\totales.csv";
    std::string pathSentencias = sPathFileCreatedCSV + "\\sentencias.csv";
    std::string pathObsoleto = sPathFileCreatedCSV + "\\obsoleto.csv";
    std::string pathIA = sPathFileCreatedCSV + "\\IA_bito.csv";
    std::string pathFinProyecto = sPathFileCreatedCSV + "\\finProyecto.csv";
    std::string pathBito = sPathFileCreatedCSV + "\\Bito.xlsx";

    std::string command = "c:\\sys\\progs\\parse\\UneCSV.exe \"" + pathTotales + "\" \"" + pathSentencias + "\" \"" + pathObsoleto + "\" \"" + pathIA + "\" \"" + pathFinProyecto + "\" \"" + pathBito + "\"";
    iRet = system(command.c_str());

    if (iRet == -1)
    {
        std::cout << std::endl;
        std::cout << "El valor de retorno de system() es -1, no se puede crear el proceso hijo." << std::endl;

    }
    else if (iRet == 127 )
    {
        std::cout << std::endl;
        std::cout << "El valor de retorno de system() es 127, no se puede ejecutar el shell." << std::endl;

    }
    else
    {
        std::cout << std::endl;
        std::cout << "Los archivos con los resultados se encuentran en la siguiente ruta: " << sPathFileCreatedCSV << std::endl;
    }
    
    return iRet;
}

/*
* (WORD)color =  
Attribute	                Significado
FOREGROUND_BLUE	            El color del texto contiene azul.
FOREGROUND_GREEN	        El color del texto contiene verde.
FOREGROUND_RED	            El color del texto contiene rojo.
FOREGROUND_INTENSITY	    El color del texto se intensifica.
BACKGROUND_BLUE	            El color de fondo contiene azul.
BACKGROUND_GREEN	        El color de fondo contiene verde.
BACKGROUND_RED	            El color de fondo contiene rojo.
BACKGROUND_INTENSITY	    El color de fondo se intensifica.
*/
void CIA::setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

// Función para obtener el ancho de la consola
int CIA::getConsoleWidth() 
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Función para centrar el texto
void CIA::printCentered(std::string text) 
{
    int consoleWidth = getConsoleWidth();
    int textLength = (int)text.length();
    int padding = (consoleWidth - textLength) / 2;
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << text << std::endl;
}

bool CIA::esNumeroNatural(std::string str) {
    for (char& c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool CIA::soloCaracteres(const std::string& str) 
{
    for (char c : str) 
    {
        if (std::isdigit(c)) 
        {
            return false;
        }
    }
    return true;
}

std::wstring CIA::convertStringToWString(const std::string& str)
{
    int wstr_len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wstr(wstr_len, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], wstr_len);
    return wstr;
}

std::string CIA::convertWStringToString(const std::wstring& wstr) 
{
    int str_len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string str(str_len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], str_len, NULL, NULL);
    return str;
}

//std::wstring CIA::convierte_Utf8_to_ws(std::string const& utf8) 
//{
//    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cnv;
//    std::wstring s = cnv.from_bytes(utf8);
//    if (cnv.converted() < utf8.size())
//    {
//        throw std::runtime_error("incomplete conversion");
//    }
//
//    return s;
//}

//std::string CIA::convierteWs_to_utf8(std::wstring const& s) 
//{
//    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cnv;
//    std::string utf8 = cnv.to_bytes(s);
//    if (cnv.converted() < s.size())
//    {
//        throw std::runtime_error("incomplete conversion");
//    }
//
//    return utf8;
//}

bool CIA::validateExtension(std::string sExtension)
{
    std::vector<std::string> validExtensions = { ".php", ".js", ".c", ".cpp", ".cs", ".java", ".py", ".rb", ".go", ".rs", ".swift", ".ts", ".jsp", ".sql", ".cfm", ".pl", ".vb", ".h", ".hpp"};

    sExtension = "." + sExtension;
    // Convertir la extensión a minúsculas
    std::transform(sExtension.begin(), sExtension.end(), sExtension.begin(), [](unsigned char c) { return std::tolower(c); });

    return find(validExtensions.begin(), validExtensions.end(), sExtension) != validExtensions.end();
}

std::string CIA::getFileNameWithoutExtension(std::string fileName)
{
    size_t lastDotIndex = fileName.find_last_of(".");

    if (lastDotIndex == std::string::npos)
    {
        return fileName;
    }

    return fileName.substr(0, lastDotIndex);
}

void CIA::eliminarArchivo(const std::string& sRutaArchivo)
{
    // Elimina el archivo si existe
    std::filesystem::remove(sRutaArchivo);
}

int CIA::obtieneTotales(char* cPathRoot, char* cPathTotales, std::vector<std::string> &vcLenguajes)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    ZeroMemory(&pi, sizeof(pi));

    char cFileCloc[600] = { 0 };
    memset(cFileCloc, ' ', sizeof(cFileCloc));

    strcpy_s(cFileCloc, "C:\\sys\\progs\\parse\\obtienedatosfuentes.exe ");
    strcat_s(cFileCloc, cPathRoot);
    //strcat_s(cFileCloc, "C:\\temp\\intranet");
    strcat_s(cFileCloc, " --report-file=");
    //strcat_s(cFileCloc, "C:\\temp\\intranet\\totales.txt");
    strcat_s(cFileCloc, cPathTotales);

    if (!CreateProcessA(NULL,   // No module name (use command line)
        cFileCloc,       // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NO_WINDOW,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        std::cout << "CreateProcess failed." << (int)GetLastError() << std::endl;
        return 1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Verificar si existe el archivo de totales
    // 0 = existe, -1 = no existe

    if (_access(cPathTotales, 0) == 0)
    {
        std::cout << "Procesando totales de archivos..." << std::endl;

        std::ifstream input_file(cPathTotales);

        char cPathTotalesCsv[300] = { 0 };
        sprintf_s(cPathTotalesCsv, sizeof(cPathTotalesCsv), "%s\\%s", cPathRoot, "totales.csv");
        std::wofstream output_file(cPathTotalesCsv);
        // Crear un objeto de conversión de caracteres UTF-8
        //std::locale loc(output_file.getloc(), new std::codecvt_utf8<wchar_t>);
        // Establecer la localidad del flujo de archivo
        //output_file.imbue(loc);

        std::string line;
        bool skip_line = true;
        std::wstring wstr; // Cadena de texto en formato UTF-8

        while (std::getline(input_file, line))
        {
            // Ignora la primera línea y las líneas que contienen '---'
            if (skip_line || line.find("---") != std::string::npos) {
                skip_line = false;
                continue;
            }

            //// Reemplaza los espacios con comas
            //for (char& c : line) {
            //    if (c == ' ') {
            //        c = ',';
            //    }
            //}

            // Divide la línea en palabras
            std::istringstream iss(line);
            std::vector<std::string> words;
            std::string word;

            while (iss >> word) 
            {
                words.push_back(word);
            }

            // Une las palabras con comas y escribe la línea en el archivo .csv
            for (size_t i = 0; i < words.size(); ++i) 
            {
                wstr = convertStringToWString(words[i]);
                
                output_file << wstr;

                if ((words[i].compare(".csv")) == 0)
                {
                    output_file << ",";
                    vcLenguajes.push_back(".js");
                }
                if ((words[i].compare("JavaScript")) == 0)
                {
                    vcLenguajes.push_back(".js");
                }
                else if ((words[i].compare("TypeScript")) == 0)
                {
                    output_file << ",";
					vcLenguajes.push_back(".ts");
				}
                else if ((words[i].compare("C++")) == 0)
                {
                    output_file << ",";
					vcLenguajes.push_back(".cpp");
				}
                else if ((words[i].compare("C")) == 0)
                {
					vcLenguajes.push_back(".c");
				}
                else if ((words[i].compare("C#")) == 0)
                {
                    vcLenguajes.push_back(".cs");
                }
                else if ((words[i].compare("Swift")) == 0)
                {
					vcLenguajes.push_back(".swift");
				}
                else if ((words[i].compare("Go")) == 0)
                {
					vcLenguajes.push_back(".go");
				}
                else if ((words[i].compare("Perl")) == 0)
                {
					vcLenguajes.push_back(".pl");
				}
                else if ((words[i].compare("Rust")) == 0)
                {
					vcLenguajes.push_back(".rs");
				}
                else if ((words[i].compare("Kotlin")) == 0)
                {
					vcLenguajes.push_back(".kt");
				}
                else if ((words[i].compare("Scala")) == 0)
                {
					vcLenguajes.push_back(".scala");
				}
                else if ((words[i].compare("Dart")) == 0)
                {
                    vcLenguajes.push_back(".dart");
                }
                else if ((words[i].compare("PHP")) == 0)
                {
                    output_file << ",";
                    vcLenguajes.push_back(".php");
                }
                else if ((words[i].compare("VISUAL BASIC")) == 0)
                {
                    vcLenguajes.push_back(".bas");
                }
                else if ((words[i].compare("Visual Basic.NET")) == 0)
                {
                    vcLenguajes.push_back(".vb");
                }
                else if ((words[i].compare("Python")) == 0)
                {
                    output_file << ",";
                    vcLenguajes.push_back(".py");
                }
                else
                {
                    //std::cout << "Lenguaje no encontrado: " << words[i] << std::endl;
                }

               /* output_file << wstr;*/
                if (i < words.size() - 1) 
                {
                    output_file << ",";
                }
            }

            words.clear();
            
            // Escribe la línea en el archivo .csv
            //wstr = convertStringToWString(line);
            //output_file << wstr << std::endl;
        }

        input_file.close();
        output_file.close();
    }
    else
    {
        std::cout << "El archivo de totales no existe" << std::endl;
    }

    return 0;
}


int CIA::getTotals(char* cPathRoot, char* cPathTotales)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    ZeroMemory(&pi, sizeof(pi));

    char cFileCloc[600] = { 0 };
    memset(cFileCloc, ' ', sizeof(cFileCloc));

    strcpy_s(cFileCloc, "C:\\sys\\progs\\parse\\obtienedatosfuentes.exe ");

    // Validar si el aplicativo existe
    if (_access(cFileCloc, 0) != 0)
	{
		return ERROR_FILE_NOT_FOUND;
	}

    strcat_s(cFileCloc, cPathRoot);
    //strcat_s(cFileCloc, "C:\\temp\\intranet");
    strcat_s(cFileCloc, " --report-file=");
    //strcat_s(cFileCloc, "C:\\temp\\intranet\\totales.txt");
    strcat_s(cFileCloc, cPathTotales);

    if (!CreateProcessA(NULL,   // No module name (use command line)
        cFileCloc,       // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NO_WINDOW,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        std::cout << "CREATE PROCESS FAILED." << (int)GetLastError() << " [getTotals] " << std::endl;
        return 1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

std::map<std::string, int> CIA::obtieneSentenciasSQLEnMapa(char* cRootPath, const long lIdProyecto, const int iDataBase)
{
    std::map<std::string, int> mapSentencias;

    std::string sLenguaje;
    char cBufferIni[26]    = { 0 };
    char cBufferFin[26]    = { 0 };
    int  iTotalFiles       = 0;
    std::wstring wstr; // Cadena de texto en formato UTF-8
    std::string sCadena; // Cadena de texto.

    std::filesystem::path root_directory = cRootPath;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    ctime_s(cBufferIni, sizeof cBufferIni, &start_time);
    // Eliminar el salto de línea
    cBufferIni[strcspn(cBufferIni, "\n")] = 0;

    iTotalFiles = search_files_Sql_in_directory(root_directory, mapSentencias, lIdProyecto, iDataBase);

    std::cout << std::endl;

    end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    ctime_s(cBufferFin, sizeof cBufferFin, &end_time);

    // Eliminar el salto de línea
    cBufferFin[strcspn(cBufferFin, "\n")] = 0;

    std::cout << "FINALIZA PROCESO DE BUSQUEDA DE SENTENCIAS, " << cBufferFin << "." << std::endl;

    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
    std::chrono::duration<double> elapsed_seconds = end - start;
    double execution_time = elapsed_seconds.count();

    // Imprime la duración
    std::cout << "Tiempo transcurrido: " << execution_time << " segundos" << std::endl;

    return mapSentencias;
}

//int CIA::obtieneSentenciasSQL(char* cRootPath, char* cSentencias, char *cLenguaje, const int iDataBase)
//{
//    std::string sLenguaje;
//    bool bContinuar = false;
//    char cBufferIni[26] = { 0 };
//    char cBufferFin[26] = { 0 };
//    std::wstring wstr; // Cadena de texto en formato UTF-8
//    std::string sCadena; // Cadena de texto.
//
//    if (memcmp(cLenguaje, "php", 3) != 0 )
//    {
//        do
//        {
//            std::cout << "Por favor, introduce el lenguaje a procesar. Ejemplo (PHP, CPP, C, JAVA): ";
//            std::cin >> sLenguaje;
//            if (!soloCaracteres(sLenguaje))
//            {
//                std::cout << "Error: Por favor captura solo la extensión del lenguaje. Ejemplo (PHP, CPP, C, JAVA)" << std::endl;
//                continue;
//            }
//            else
//            {
//                bContinuar = CIA::validateExtension(sLenguaje);
//            }
//        } while (bContinuar == false);
//    }
//    else
//    {
//        sLenguaje = cLenguaje;
//        bContinuar = CIA::validateExtension(sLenguaje);
//    }
//
//    std::filesystem::path root_directory = cRootPath;
//
//    // Obtener el nombre del archivo sin la extensión.
//    std::string sArchivoSentencias;
//    sArchivoSentencias = getFileNameWithoutExtension(cSentencias);
//
//    // Armamos el nombre del archivo de sentencias csv.
//    sArchivoSentencias = sArchivoSentencias + "_" + sLenguaje + ".csv";
//
//    // Se elimina el archivo de sentencias si existe.
//    eliminarArchivo(sArchivoSentencias);
//
//    std::ofstream csv_file(sArchivoSentencias);
//    //std::wofstream csv_file(sArchivoSentencias);
//
//    //wstr = convertStringToWString("Archivo|Línea|Sentencia SQL|");
//    csv_file << "ARCHIVO|LINEA|SENTENCIA SQL|" << std::endl;
//    //csv_file << wstr << std::endl;
//
//    int php_file_count_current = 0;
//
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    start                   = std::chrono::system_clock::now();
//    std::time_t start_time  = std::chrono::system_clock::to_time_t(start);
//    
//    // Copilot, actualiza ctime a modo seguro
//    // std::cout << "Inicia proceso de busqueda de Sentencias, " << std::ctime(&start_time) << "." << std::endl;
//    
//    ctime_s(cBufferIni, sizeof cBufferIni, &start_time);
//    // Eliminar el salto de línea
//    cBufferIni[strcspn(cBufferIni, "\n")] = 0;
//
//    //std::cout << "Inicia proceso de busqueda de Sentencias, " << cBufferIni << "." << std::endl;
//    //wstr = convertStringToWString("Inicia proceso de busqueda de Sentencias| | |");
//    csv_file << "INICIA PROCESO DE BUSQUEDA DE SENTENCIAS| | |" << cBufferIni << std::endl;
//
//    std::map<std::string, int> mapSentencias;
//
//    int total_php_files = search_files_Sql_in_directory(root_directory, csv_file, mapSentencias, iDataBase);
//
//    end                     = std::chrono::system_clock::now();
//    std::time_t end_time    = std::chrono::system_clock::to_time_t(end);
//
//    // std::cout << "Finaliza proceso de busqueda de Sentencias, " << std::ctime(&end_time) << "." << std::endl;
//    ctime_s(cBufferFin, sizeof cBufferFin, &end_time);
//    // Eliminar el salto de línea
//    cBufferFin[strcspn(cBufferFin, "\n")] = 0;
//
//    std::cout << "FINALIZA PROCESO DE BUSQUEDA DE SENTENCIAS, " << cBufferFin << "." << std::endl;
//
//    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    double execution_time = elapsed_seconds.count();
//    
//    // Imprime la duración
//    std::cout << "Tiempo transcurrido: " << execution_time << " segundos" << std::endl;
//
//    csv_file << "Inicia proceso de busqueda de Sentencias|" << cBufferIni << " segundos| |" << std::endl;
//    //sCadena = cBufferIni;
//    //wstr = convertStringToWString("Finaliza proceso de busqueda de Sentencias|" + sCadena + " segundos| |\n");
//    //csv_file << wstr << std::endl;
//
//    
//    csv_file << "Total de archivos PHP encontrados|" << total_php_files << "| |" << std::endl;
//    //sCadena = std::to_string(total_php_files);
//    //wstr = convertStringToWString("Total de archivos PHP encontrados|" + sCadena + "| |\n");
//
//
//    csv_file << "Total de ocurrencias en PHP encontrados|" << php_file_count_current << "| |" << std::endl;
//    //sCadena = std::to_string(php_file_count_current);
//    //wstr = convertStringToWString("Total de ocurrencias en PHP encontrados|" + sCadena + "| |\n");
//
//
//    csv_file << "Finaliza proceso de busqueda de Sentencias|" << cBufferFin << "| |" << std::endl;
//    //sCadena = cBufferFin;
//    //wstr = convertStringToWString("Finaliza proceso de busqueda de Sentencias|" + sCadena + "| |\n");
//
//    csv_file << "Tiempo transcurrido|" << execution_time << " segundos| |" << std::endl;
//    //sCadena = std::to_string(execution_time);
//    //wstr = convertStringToWString("Tiempo transcurrido|" + sCadena + " segundos| |\n");
//
//    csv_file.close();
//
//    return php_file_count_current;
//}


std::map<std::string, int> CIA::obtieneFuncionesObsoletasEnMapa(char* cRootPath, const long lIdProyecto, const int iDataBase)
{
    std::map<std::string, int> mapDeprecated;

    std::string sLenguaje;
    char cBufferIni[26]     = { 0 };
    char cBufferFin[26]     = { 0 };
    int iTotalDeprecated    = 0;

    std::filesystem::path root_directory = cRootPath;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    ctime_s(cBufferIni, sizeof cBufferIni, &start_time);

    // Eliminar el salto de línea
    cBufferIni[strcspn(cBufferIni, "\n")] = 0;

    std::cout << "INICIA PROCESO DE BUSQUEDA DE FUNCIONES OBSOLETAS, " << cBufferIni << "." << std::endl;
    iTotalDeprecated = search_files_deprecated_in_directory(root_directory, mapDeprecated, lIdProyecto, iDataBase);

    end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    ctime_s(cBufferFin, sizeof cBufferFin, &end_time);

    // Eliminar el salto de línea
    cBufferFin[strcspn(cBufferFin, "\n")] = 0;

    std::cout << "FINALIZA PROCESO DE BUSQUEDA DE FUNCIONES OBSOLETAS, " << cBufferFin << "." << std::endl;

    // Calcula la duración
    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
    std::chrono::duration<double> elapsed_seconds = end - start;
    double execution_time = elapsed_seconds.count();

    std::cout << "TOTAL DE ARCHIVOS ENCONTRADOS|" << iTotalDeprecated << "| |" << std::endl;
    std::cout << "FINALIZA PROCESO DE BUSQUEDA DE FUNCIONES OBSOLETAS|" << cBufferFin << " SEGUNDOS| |" << std::endl;

    // Imprime la duración
    std::cout << "TIEMPO TRANSCURRIDO: " << execution_time << " SEGUNDOS." << std::endl;

    return mapDeprecated;
}

//int CIA::obtieneFuncionesObsoletas(char* cRootPath, char* cDeprecated, char* cLenguaje)
//{
//    std::string sLenguaje;
//    char cBufferIni[26] = { 0 };
//    char cBufferFin[26] = { 0 };
//    bool bContinuar = false;
//
//    if (memcmp(cLenguaje, "php", 3) != 0)
//    {
//        do
//        {
//            std::cout << "Por favor, introduce el lenguaje a procesar. Ejemplo (PHP, CPP, C, JAVA): ";
//            std::cin >> sLenguaje;
//            if (!soloCaracteres(sLenguaje))
//            {
//                std::cout << "Error: Por favor captura solo la extensión del lenguaje. Ejemplo (PHP, CPP, C, JAVA)" << std::endl;
//                continue;
//            }
//            else
//            {
//                bContinuar = CIA::validateExtension(sLenguaje);
//            }
//        } while (bContinuar == false);
//    }
//    else
//    {
//        sLenguaje = cLenguaje;
//        bContinuar = CIA::validateExtension(sLenguaje);
//    }
//
//    // Obtener el nombre del archivo sin la extensión.
//    std::string sArchivoObsoletos;
//    sArchivoObsoletos = getFileNameWithoutExtension(cDeprecated);
//
//    // Armamos el nombre del archivo de sentencias csv.
//    sArchivoObsoletos = sArchivoObsoletos + "_" + sLenguaje + ".csv";
//
//    // Se elimina el archivo de sentencias si existe.
//    eliminarArchivo(sArchivoObsoletos);
//
//    std::filesystem::path root_directory = cRootPath;
//    std::ofstream csv_file_deprecated(sArchivoObsoletos);
//
//    csv_file_deprecated << "Archivo|Línea|deprecated|" << std::endl;
//
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    start = std::chrono::system_clock::now();
//    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
//
//    ctime_s(cBufferIni, sizeof cBufferIni, &start_time);
//    
//    // Eliminar el salto de línea
//    cBufferIni[strcspn(cBufferIni, "\n")] = 0;
//
//    std::cout << "Inicia proceso de busqueda de funciones obsoletas, " << cBufferIni << "." << std::endl;
//    csv_file_deprecated << "Inicia proceso de busqueda de funciones obsoletas|" << cBufferIni << "| |" << std::endl;
//
//    int total_php_deprecated = search_files_php_deprecated_in_directory(root_directory, csv_file_deprecated);
//
//    end = std::chrono::system_clock::now();
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//
//    ctime_s(cBufferFin, sizeof cBufferFin, &end_time);
//    
//    // Eliminar el salto de línea
//    cBufferFin[strcspn(cBufferFin, "\n")] = 0;
//
//    std::cout << "FINALIZA PROCESO DE BUSQUEDA DE FUNCIONES OBSOLETAS, " << cBufferFin << "." << std::endl;
//
//    // Calcula la duración
//    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    double execution_time = elapsed_seconds.count();
//    // Imprime la duración
//    std::cout << "TIEMPO TRANSCURRIDO: " << execution_time << " SEGUNDOS." << std::endl;
//
//    csv_file_deprecated << "Inicia proceso de busqueda de funciones obsoletas|" << cBufferIni << " segundos| |" << std::endl;
//    //csv_file_deprecated << "Tiempo de ejecución," << execution_time << " segundos" << std::endl;
//    csv_file_deprecated << "Total de archivos PHP obsoletos encontrados|" << total_php_deprecated << "| |" << std::endl;
//    csv_file_deprecated << "Finaliza proceso de busqueda de funciones obsoletas|" << cBufferFin << " segundos| |" << std::endl;
//    csv_file_deprecated << "Tiempo transcurrido|" << execution_time << " segundos| |" << std::endl;
//    csv_file_deprecated.close();
//
//    return total_php_deprecated;
//}

int CIA::obtieneBITO(char* cRootPath, char* cBito)
{
    char cPath[MAX_PATH]        = { 0 };
    char cFile[MAX_PATH]        = { 0 };
    char cFileBito[600]         = { 0 };
    char cPathFileBito[300]     = { 0 };
    char cPathFilePrompt[300]   = { 0 };
    char cStemBito[150]         = { 0 };
    char cBufferIniBito[26]     = { 0 };
    char cBufferFinBito[26]     = { 0 };
    //char cPathFileNoBito[MAX_PATH] = { 0 };
    int  iRespuestaSystem        = 0;

    double execution_time_bito = 0.0;
    double execution_time_in_minutes = 0.0;

    //std::ofstream csv_file_bito(cBito);

    //csv_file_bito << "ARCHIVO|HORA_INICIO|HORA_FIN|TIEMPO_EN_SEGUNDOS|TIEMPO_EN_MINUTOS|RESPUESTA_LINT|PHP_LINT_CHECK|COMENTARIOS_BITO" << std::endl;

    if (!std::filesystem::exists(cRootPath))
    {
        std::cerr << "El directorio no existe: " << cRootPath << std::endl;
        return 0;
    }

    std::string strStemBito;
    std::string sPathFileBitoTxt;
    std::string sContenidoTxtLint;
    std::string sRespuestaSystemLinter;

    std::string linea;
    std::string contenido;

    std::stringstream buffer_file;
    std::stringstream buffer_file_txt;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time);

    // Eliminar el salto de línea
    cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

    std::cout << "INICIA PROCESO DE CONVERSION DE ARCHIVOS CON IA, " << cBufferIniBito << "." << std::endl;
    //csv_file_bito << "INICIA PROCESO DE CONVERSION DE ARCHIVOS CON IA| | | | | | |" << cBufferIniBito << std::endl;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(cRootPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".php")
        {
            sprintf_s(cPath, sizeof(cPath), "%S", entry.path().parent_path().c_str());
            sprintf_s(cFile, sizeof(cFile), "%S", entry.path().filename().c_str());
            sprintf_s(cPathFileBito, sizeof(cPathFileBito), "%s\\%s", cPath, cFile);
            sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimization.pmt"); //cStem

            strStemBito = cFile;

            sprintf_s(cStemBito, sizeof(cStemBito), "%s", strStemBito.substr(0, strStemBito.find_last_of(".")).c_str());

            memset(cFileBito, ' ', sizeof(cFileBito));

            strcpy_s(cFileBito, "type ");
            strcat_s(cFileBito, cPathFileBito);
            strcat_s(cFileBito, " | bito.exe");
            strcat_s(cFileBito, cPathFilePrompt);
            strcat_s(cFileBito, " > ");
            strcat_s(cFileBito, cPath);
            strcat_s(cFileBito, "\\");
            strcat_s(cFileBito, cStemBito);
            strcat_s(cFileBito, ".bito");

            std::cout << cPathFileBito << std::endl;

            //Iniciamos el reloj
            std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
            startBito = std::chrono::system_clock::now();
            std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

            ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

            // Eliminar el salto de línea
            cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

            std::cout << "INICIA PROCESO DE CONVERSION CON IA, " << cBufferIniBito << "." << std::endl;

            system(cFileBito);

            ////memset(cStemBito, ' ', sizeof(cStemBito));
            ////sprintf_s(cStemBito, sizeof(cStemBito), "%s\\%s.bito", cPath, strStemBito.substr(0, strStemBito.find_last_of(".")).c_str());

            ////sprintf_s(cPathFileNoBito, sizeof(cPathFileNoBito), "%s\\NoConvertBito.csv", cPath);
            ////
            ////if (validarArchivoBito(cStemBito, cPathFileNoBito) == false)
            ////{
            ////    std::cout << "El archivo " << cStemBito << " no se convirtió con BITO." << std::endl;
            ////}
            ////else
            {
                //1 - Abres y lees el archivo original 'prueba_ws.php'.
                //2 - Renombras el archivo 'prueba_ws.php' como 'ori_prueba_ws.php'.
                //3 - Lees el archivo 'prueba_ws.bito.php', si encuentra una línea que contiene ````php`, cambia el estado de la variable bool `bCopy`. Si `bCopy` es verdadero, 
                //las líneas se escriben en `prueba_ws.php`, si es falso, las líneas se escriben en `prueba_ws.bito.txt`..
                //4. Si encuentra una línea que contiene solo `````, cambia el estado de la variable bool `bEnd`. Si `BEnd` es verdadero, 
                //las líneas se escriben en `prueba_ws.php`, si es falso, las líneas se escriben al final del archivo `prueba_ws.bito.txt`..
                //5 - Al final, cierra todos los archivos abiertos.
                sPathFileBitoTxt = " ";
                quitarComentariosBito(cPathFileBito, sPathFileBitoTxt);

                memset(cStemBito, ' ', sizeof(cStemBito));
                sprintf_s(cStemBito, sizeof(cStemBito), "%s\\%s.lin", cPath, strStemBito.substr(0, strStemBito.find_last_of(".")).c_str());

                // Ejecutar php -l para validar la sintaxis del archivo.
                sprintf_s(cFileBito, sizeof(cFileBito), "php -l %s > %s", cPathFileBito, cStemBito);  

                // Ejecutar el comando
                iRespuestaSystem = system(cFileBito);

                if (iRespuestaSystem == 0) 
                {
                    sRespuestaSystemLinter = "CORRECTO";
                }
                else if (iRespuestaSystem == 255) 
                {
                    sRespuestaSystemLinter = "INCORRECTO";
                }
                else 
                {
                    sRespuestaSystemLinter = "OCURRIÓ UN ERROR AL EJECUTAR EL COMANDO LINT";
                }

                // Leer el archivo de salida y obtener el resultado.
                std::ifstream input_file(cStemBito);
                if (input_file)
                {
                    buffer_file << input_file.rdbuf();
                    input_file.close();

                    sContenidoTxtLint = buffer_file.str();
                    // Elimina todos los caracteres de salto de línea
                    sContenidoTxtLint.erase(std::remove(sContenidoTxtLint.begin(), sContenidoTxtLint.end(), '\n'), sContenidoTxtLint.end());
                }
                else
                {
                    std::cerr << "No se pudo abrir el archivo: " << cStemBito << std::endl;
                }

                contenido = "";
                std::ifstream input_file_txt(sPathFileBitoTxt);
                if (input_file_txt) 
                {
                    while (std::getline(input_file_txt, linea)) 
                    {
                        // Elimina los saltos de línea y las comas
                        linea.erase(std::remove(linea.begin(), linea.end(), '\n'), linea.end());
                        linea.erase(std::remove(linea.begin(), linea.end(), ','), linea.end());
                        contenido += linea;
                    }
                    input_file_txt.close();
                }


                //std::ifstream input_file_txt(sPathFileBitoTxt);
                //if (input_file_txt) 
                //{
                //    buffer_file_txt << input_file_txt.rdbuf();
                //    input_file_txt.close();
                //}
                //else 
                //{
                //    std::cerr << "No se pudo abrir el archivo: " << sPathFileBitoTxt << std::endl;
                //}

                //sContenidoTxtBito = buffer_file_txt.str();

                //// Elimina los saltos de línea y las comas
                //for (size_t pos = sContenidoTxtBito.find("\n"); pos != std::string::npos; pos = sContenidoTxtBito.find("\n", pos)) 
                //{
                //    sContenidoTxtBito.erase(pos, 1);
                //}
                //for (size_t pos = sContenidoTxtBito.find(","); pos != std::string::npos; pos = sContenidoTxtBito.find(",", pos)) 
                //{
                //    sContenidoTxtBito.erase(pos, 1);
                //}

                //for (size_t pos = sContenidoTxtBito.find(","); pos != std::string::npos; pos = sContenidoTxtBito.find(",", pos)) 
                //{
                //    sContenidoTxtBito.replace(pos, 1, " ");
                //}
            }
            
            endBito = std::chrono::system_clock::now();
            std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

            ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

            // Eliminar el salto de línea
            cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

            // Calcula la duración
            //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
            std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
            execution_time_bito = elapsed_seconds_bito.count();
            execution_time_in_minutes = elapsed_seconds_bito.count() / 60;

            //csv_file_bito << cPathFileBito << "|" << cBufferIniBito << "|" << cBufferFinBito << "|" << execution_time_bito << "|" << execution_time_in_minutes << "|" << sRespuestaSystemLinter << "|" << sContenidoTxtLint << "|" << contenido << std::endl;
            buffer_file.str("");
            buffer_file_txt.str("");
            contenido = "";

            std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
            // Imprime la duración en segundos
            std::cout << "TIEMPO TRANSCURRIDO: " << execution_time_bito << " SEGUNDOS." << std::endl;
            // Imprime la duración en minutos
            std::cout << "TIEMPO TRANSCURRIDO: " << execution_time_in_minutes << " MINUTOS." << std::endl;

            std::cout << "" << std::endl;
        }
    }

    end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time);
    
    // Eliminar el salto de línea
    cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

    std::cout << "FINALIZA PROCESO DE CONVERSION DE TODOS LOS ARCHIVOS CON IA, " << cBufferFinBito << "." << std::endl;
    //csv_file_bito << "FINALIZA PROCESO DE CONVERSION DE TODOS LOS ARCHIVOS CON IA| | | | | |" << cBufferFinBito << std::endl;

    // Calcula la duración
    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
    std::chrono::duration<double> elapsed_seconds = end - start;
    double execution_time = elapsed_seconds.count();
    execution_time_in_minutes = elapsed_seconds.count() / 60;

    //csv_file_bito << "Tiempo transcurrido|" << execution_time << " segundos| | | | | " << std::endl;
    //csv_file_bito << "Tiempo transcurrido|" << execution_time_in_minutes << " minutos| | | | | | " << std::endl;

    // Imprime la duración
    std::cout << "Tiempo transcurrido: " << execution_time << " segundos." << std::endl;
    std::cout << "Tiempo transcurrido: " << execution_time_in_minutes << " minutos." << std::endl;

    //csv_file_bito.close();

    std::cout << "" << std::endl;
    std::cout << "Proceso finalizado..." << std::endl;
    std::cout << "Presiona una tecla para continuar..." << std::endl;
    int iTecla = 0;
    iTecla = _getch();
    menu();

    return 0;
}

std::set<std::string> CIA::cargarArchivosProcesados(std::string sRutaArchivoProcesados)
{
    std::set<std::string> archivosProcesados;
    std::ifstream archivo(sRutaArchivoProcesados);
    std::string linea;

    while (std::getline(archivo, linea))
    {
        archivosProcesados.insert(linea);
    }

    return archivosProcesados;
}


void CIA::guardarArchivosProcesados(std::string sRutaArchivoProcesados, const std::set<std::string>& archivosProcesados)
{
    std::ofstream archivo(sRutaArchivoProcesados);

    for (const auto& nombre : archivosProcesados)
    {
        archivo << nombre << "\n";
    }
}


int CIA::procesarArchivo(const std::string& sNombreArchivo, char* cExtension, std::string & sComentariosBito)
{
    char cFileBito[600]             = { 0 };
    char cPathFileNoBito[MAX_PATH]  = { 0 };

    std::string sPathFileBitoTxt;
    std::string sContenidoTxtLint;
    std::string sRespuestaSystemLinter;

    std::stringstream buffer_file;
    std::stringstream buffer_file_txt;

    std::string sLinea      = "";
    std::string sArcBito    = "";

    //Cargar el PROMPT por lenguaje de programación.
    sArcBito = generarArchivoBito(sNombreArchivo, cExtension);
    sprintf_s(cFileBito, sizeof(cFileBito), "%s", sArcBito.c_str());

    //// "C:\temp\root\procesar\Pruebas\factura\factura\buscafact.php"
    std::string sNombrePathArchivo = sNombreArchivo;
    //
    ////Obtener el nombre del archivo sin la extensión.
    std::string sNombreArchivoSinExtension = getFileNameWithoutExtension(sNombreArchivo);
    //Obtener la ruta del archivo.
    std::string sObtenerRutaArchivo = sNombrePathArchivo.substr(0, sNombrePathArchivo.find_last_of("\\"));
    //Crear un archivo con con el nombre del archivo con la ruta raíz y con la extensión .bito.
    std::string sNombreArchivoBito = sNombreArchivoSinExtension + ".bito";

    int iResBito = system(cFileBito);
    iResBito = iResBito;

    sprintf_s(cPathFileNoBito, sizeof(cPathFileNoBito), "%s\\NoConvertBito.csv", sObtenerRutaArchivo.c_str());

    if (validarArchivoBito(sNombreArchivoBito.c_str(), cPathFileNoBito) == false)
    {
        std::cout << "EL ARCHIVO " << sNombreArchivoBito.c_str() << " NO SE CONVIRTIO CON BITO." << std::endl;
    }
    else
    {
        //1 - Abres y lees el archivo original 'prueba_ws.cpp'.
        //2 - Renombras el archivo 'prueba_ws.php' como 'ori_prueba_ws.cpp'.
        //3 - Lees el archivo 'prueba_ws.bito.php', si encuentra una línea que contiene ````cpp`, cambia el estado de la variable bool `bCopy`. Si `bCopy` es verdadero, 
        //las líneas se escriben en `prueba_ws.cpp`, si es falso, las líneas se escriben en `prueba_ws.bito.txt`..
        //4. Si encuentra una línea que contiene solo `````, cambia el estado de la variable bool `bEnd`. Si `BEnd` es verdadero, 
        //las líneas se escriben en `prueba_ws.cpp`, si es falso, las líneas se escriben al final del archivo `prueba_ws.bito.txt`..
        //5 - Al final, cierra todos los archivos abiertos.
        sPathFileBitoTxt = " ";
        quitarComentariosBito(sNombrePathArchivo.c_str(), sPathFileBitoTxt);

        sComentariosBito = "";
        std::ifstream input_file_txt(sPathFileBitoTxt);
        if (input_file_txt)
        {
            while (std::getline(input_file_txt, sLinea))
            {
                // Elimina los saltos de línea y las comas
                sLinea.erase(std::remove(sLinea.begin(), sLinea.end(), '\n'), sLinea.end());
                sLinea.erase(std::remove(sLinea.begin(), sLinea.end(), ','), sLinea.end());
                sComentariosBito += sLinea;
            }
            input_file_txt.close();
        }
    }

    return 1;
}


//int CIA::procesarArchivo(const std::string& sNombreArchivo, std::ofstream& csv_file, const std::string& sRespuestaSystemLinterOriginal)
//{
//    char cPathFilePrompt[300] = { 0 };
//    char cFileBito[600] = { 0 };
//    char cFileLintPhp[600] = { 0 };
//    char cBufferIniBito[26] = { 0 };
//    char cBufferFinBito[26] = { 0 };
//    char cPathFileNoBito[MAX_PATH] = { 0 };
//    char cStemBito[150] = { 0 };
//    char cStemLint[150] = { 0 };
//    int  iRespuestaSystem = 0;
//
//    std::string sPathFileBitoTxt;
//    std::string sContenidoTxtLint;
//    std::string sRespuestaSystemLinter;
//
//    std::stringstream buffer_file;
//    std::stringstream buffer_file_txt;
//
//    std::string sContenido;
//    std::string sLinea;
//
//    double dExecutionTimeBito = 0.0;
//    double dExecutionTimeInMinutes = 0.0;
//
//    // "C:\temp\root\procesar\Pruebas\factura\factura\buscafact.php"
//    std::string sNombrePathArchivo = sNombreArchivo;
//    //Obtener el nombre del archivo sin la extensión.
//    std::string sNombreArchivoSinExtension = getFileNameWithoutExtension(sNombreArchivo);
//    //Obtener la ruta del archivo.
//    std::string sObtenerRutaArchivo = sNombrePathArchivo.substr(0, sNombrePathArchivo.find_last_of("\\"));
//    //Crear un archivo con con el nombre del archivo con la ruta raíz y con la extensión .bito.
//    std::string sNombreArchivoBito = sNombreArchivoSinExtension + ".bito";
//
//    // Leer el archivo prompt para la toma de regla BITO.
//    sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimization.pmt"); //cStem
//
//    std::cout << "Procesando archivo: " << sNombreArchivo << std::endl;
//
//    memset(cFileBito, ' ', sizeof(cFileBito));
//
//    strcpy_s(cFileBito, "type ");
//    strcat_s(cFileBito, sNombrePathArchivo.c_str());
//    strcat_s(cFileBito, " | bito.exe");
//    strcat_s(cFileBito, cPathFilePrompt);
//    strcat_s(cFileBito, " > ");
//    strcat_s(cFileBito, sNombreArchivoBito.c_str());
//
//    //std::cout << cFileBito << std::endl;
//
//    //Iniciamos el reloj
//    std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
//    startBito = std::chrono::system_clock::now();
//    std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);
//
//    ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);
//
//    // Eliminar el salto de línea
//    cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;
//
//    std::cout << "Inicia proceso de conversión con IA, " << cBufferIniBito << "." << std::endl;
//
//    int iResBito = system(cFileBito);
//
//    sprintf_s(cPathFileNoBito, sizeof(cPathFileNoBito), "%s\\NoConvertBito.csv", sObtenerRutaArchivo.c_str());
//
//    if (validarArchivoBito(sNombreArchivoBito.c_str(), cPathFileNoBito) == false)
//    {
//        std::cout << "El archivo " << sNombreArchivoBito.c_str() << " no se convirtió con BITO." << std::endl;
//    }
//    else
//    {
//        //1 - Abres y lees el archivo original 'prueba_ws.php'.
//        //2 - Renombras el archivo 'prueba_ws.php' como 'ori_prueba_ws.php'.
//        //3 - Lees el archivo 'prueba_ws.bito.php', si encuentra una línea que contiene ````php`, cambia el estado de la variable bool `bCopy`. Si `bCopy` es verdadero, 
//        //las líneas se escriben en `prueba_ws.php`, si es falso, las líneas se escriben en `prueba_ws.bito.txt`..
//        //4. Si encuentra una línea que contiene solo `````, cambia el estado de la variable bool `bEnd`. Si `BEnd` es verdadero, 
//        //las líneas se escriben en `prueba_ws.php`, si es falso, las líneas se escriben al final del archivo `prueba_ws.bito.txt`..
//        //5 - Al final, cierra todos los archivos abiertos.
//        sPathFileBitoTxt = " ";
//        quitarComentariosBito(sNombrePathArchivo.c_str(), sPathFileBitoTxt);
//
//        memset(cStemLint, ' ', sizeof(cStemLint));
//        sprintf_s(cStemLint, sizeof(cStemLint), "%s.lin", sNombreArchivoSinExtension.c_str());
//
//        memset(cFileLintPhp, ' ', sizeof(cFileLintPhp));
//        //Ejecutar php -l para validar la sintaxis del archivo.
//        sprintf_s(cFileLintPhp, sizeof(cFileLintPhp), "php -l %s > %s", sNombrePathArchivo.c_str(), cStemLint);
//
//        // Ejecutar el comando
//        iRespuestaSystem = system(cFileLintPhp);
//        if (iRespuestaSystem == 0)
//        {
//            std::cout << "No se encontraron errores de sintaxis.\n";
//            sRespuestaSystemLinter = "CORRECTO";
//        }
//        else
//        {
//            std::cout << "Se encontraron errores de sintaxis.\n";
//            sRespuestaSystemLinter = "INCORRECTO";
//            createCSV("c:\\sys\\mem\\parse\\bito\\", sNombrePathArchivo.c_str());
//
//            return -1;
//        }
//
//        // Leer el archivo de salida y obtener el resultado.
//        std::ifstream input_file(cStemLint);
//        if (input_file)
//        {
//            buffer_file << input_file.rdbuf();
//            input_file.close();
//
//            sContenidoTxtLint = buffer_file.str();
//            // Elimina todos los caracteres de salto de línea
//            sContenidoTxtLint.erase(std::remove(sContenidoTxtLint.begin(), sContenidoTxtLint.end(), '\n'), sContenidoTxtLint.end());
//        }
//        else
//        {
//            std::cerr << "No se pudo abrir el archivo: " << cStemBito << std::endl;
//        }
//
//        sContenido = "";
//        std::ifstream input_file_txt(sPathFileBitoTxt);
//        if (input_file_txt)
//        {
//            while (std::getline(input_file_txt, sLinea))
//            {
//                // Elimina los saltos de línea y las comas
//                sLinea.erase(std::remove(sLinea.begin(), sLinea.end(), '\n'), sLinea.end());
//                sLinea.erase(std::remove(sLinea.begin(), sLinea.end(), ','), sLinea.end());
//                sContenido += sLinea;
//            }
//            input_file_txt.close();
//        }
//    }
//
//    endBito = std::chrono::system_clock::now();
//    std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);
//
//    ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);
//
//    // Eliminar el salto de línea
//    cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;
//
//    // Calcula la duración
//    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
//    std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
//    dExecutionTimeBito = elapsed_seconds_bito.count();
//    dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;
//
//    csv_file << sNombrePathArchivo.c_str() << "|" << sRespuestaSystemLinterOriginal << "|" << cBufferIniBito << "|" << cBufferFinBito << "|" << dExecutionTimeBito << "|" << dExecutionTimeInMinutes << "|" << sRespuestaSystemLinter << "|" << sContenidoTxtLint << "|" << sContenido << std::endl;
//    buffer_file.str("");
//    buffer_file_txt.str("");
//    sContenido = "";
//
//    std::cout << "Finaliza proceso de conversión con IA, " << cBufferFinBito << "." << std::endl;
//    // Imprime la duración en segundos
//    std::cout << "Tiempo transcurrido: " << dExecutionTimeBito << " segundos" << std::endl;
//    // Imprime la duración en minutos
//    std::cout << "Tiempo transcurrido: " << dExecutionTimeInMinutes << " minutos" << std::endl;
//
//    std::cout << "" << std::endl;
//
//    return 1;
//}

int CIA::ejecutaProcesoIA(const std::string& sRuta, const long lIdProyecto, const int iDatabase)
{
    char cBufferIniBito[26]             = { 0 };
    char cBufferFinBito[26]             = { 0 };
    double execution_time_in_minutes    = 0.0;
    double dExecutionTimeBito           = 0.0;
    double dExecutionTimeInMinutes      = 0.0;

    std::string sRespuesta;
    std::string sRespuestaSystemLinterOriginal;
    std::string sRespuestaSystemLinterNvo;
    std::string sContenidoTxtLint;
    std::string sComentariosBito;

    std::stringstream buffer_file;
    std::stringstream buffer_file_txt;

    // Siempre agregamos la fecha y hora de inicio del proceso en formato de dd/mm/yyyy hh:mm:ss de 24 horas México.
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    // Cambiamos start_time a formato de México
    ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time);

    // Eliminar el salto de línea
    cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

    std::cout << "INICIA PROCESO DE CONVERSION DE ARCHIVOS CON IA, " << cBufferIniBito << "." << std::endl;
    std::string sRutaCompletaArchivosProcesados = sRuta + "\\archivos_procesados_bito.txt";

    // Cargar los archivos que ya fueron procesados
    std::set<std::string> archivosProcesados = cargarArchivosProcesados(sRutaCompletaArchivosProcesados);

    // Aquí se procesan todos los archivos que se encuentran en la ruta especificada.
    // Procesar los archivos que no han sido procesados aún y guardarlos en el set de archivos procesados para no volverlos a procesar
    for (const auto& entry : std::filesystem::recursive_directory_iterator(sRuta))
    {
        // Si es un archivo regular y la extensión es .php
        if (entry.is_regular_file() && ( entry.path().extension() == ".php" || entry.path().extension() == ".PHP" ) )
        {
            // Obtener el nombre del archivo PHP
            std::string sNombreArchivoPhp = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoPhp) == archivosProcesados.end())
            {
                // Validar la sintaxis del archivo PHP antes de procesarlo con IA y BITO
                if (lintPHPFile(sNombreArchivoPhp, sContenidoTxtLint) == 0)
                {
                    std::cout << "No se encontraron errores de sintaxis en el archivo original.\n";
                    sRespuestaSystemLinterOriginal = "CORRECTO";
                }
                else
                {
                    std::cout << "Se encontraron errores de sintaxis en el archivo original.\n";
                    sRespuestaSystemLinterOriginal = "INCORRECTO";
                }

                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS PHP, " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo PHP con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoPhp, (char*)"php", sComentariosBito);

                // Validar la sintaxis del archivo PHP que se generó con IA y BITO
                if (lintPHPFile(sNombreArchivoPhp, sContenidoTxtLint) == 0)
                {
                    std::cout << "No se encontraron errores de sintaxis en el archivo original.\n";
                    sRespuestaSystemLinterNvo = "CORRECTO";
                }
                else
                {
                    std::cout << "Se encontraron errores de sintaxis en el archivo original.\n";
                    sRespuestaSystemLinterNvo = "INCORRECTO";
                    continue;
                }

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                std::string sExecutionTimeBito;
                //Convertir el tiempo de ejecución a string
                sExecutionTimeBito = std::to_string(dExecutionTimeBito);
                std::string sExecutionTimeInMinutes;
                //Convertir el tiempo de ejecución a string
                sExecutionTimeInMinutes = std::to_string(dExecutionTimeInMinutes);

                std::string sComentariosBitoSan = sanitizarCadenas(sComentariosBito);

                registrarComentariosProyectoIA(lIdProyecto, sNomProyecto, sNombreArchivoPhp, sRespuestaSystemLinterOriginal, cBufferIniBito, cBufferFinBito, sExecutionTimeBito, sExecutionTimeInMinutes, sRespuestaSystemLinterNvo, sContenidoTxtLint, sComentariosBitoSan, iDatabase);
                    
                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoPhp);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        // Si es un archivo regular y la extensión es .js que puede ser JAVASCRIPT o ANGULAR 1
        if (entry.is_regular_file() && (entry.path().extension() == ".js" || entry.path().extension() == ".JS"))
        {
            // Obtener el nombre del archivo JAVASCRIPT o ANGULAR 1
            std::string sNombreArchivoJS = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoJS) == archivosProcesados.end())
            {   //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS JAVASCRIPT, " << " ARCHIVO [" << sNombreArchivoJS << "]" << cBufferIniBito << "." << std::endl;

                // Procesar el archivo JS con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoJS, (char*)"js", sComentariosBito);

                // Validar la sintaxis del archivo Javascripts que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoJS);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        // Si es un archivo regular y la extensión es .ts que puede ser TYPESCRIPT
        if (entry.is_regular_file() && (entry.path().extension() == ".ts" || entry.path().extension() == ".TS"))
        {
            // Obtener el nombre del archivo JAVASCRIPT o ANGULAR 1
            std::string sNombreArchivoTS = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoTS) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS TYPESCRIPT, " << " ARCHIVO [" << sNombreArchivoTS << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo TYPESCRIPT con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoTS, (char*)"ts", sComentariosBito);

                // Validar la sintaxis del archivo TYPESCRIPT que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoTS);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".java" || entry.path().extension() == ".JAVA"))
        {
            // Obtener el nombre del archivo JAVA.
            std::string sNombreArchivoJAVA = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoJAVA) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS JAVA, " << " ARCHIVO [" << sNombreArchivoJAVA << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo JAVA con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoJAVA, (char*)"java", sComentariosBito);

                // Validar la sintaxis del archivo JAVA que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoJAVA);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".dart" || entry.path().extension() == ".DART"))
        {
            // Obtener el nombre del archivo DART.
            std::string sNombreArchivoDART = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoDART) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS DART, " << " ARCHIVO [" << sNombreArchivoDART << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo DART con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoDART, (char*)"dart", sComentariosBito);

                // Validar la sintaxis del archivo DART que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoDART);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".cpp" || entry.path().extension() == ".CPP"))
        {
            // Obtener el nombre del archivo CPP.
            std::string sNombreArchivoCPP = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoCPP) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS CPP, " << " ARCHIVO [" << sNombreArchivoCPP << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo CPP con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoCPP, (char*)"cpp", sComentariosBito);

                // Validar la sintaxis del archivo CPP que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoCPP);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".hpp" || entry.path().extension() == ".HPP"))
        {
            // Obtener el nombre del archivo HPP
            std::string sNombreArchivoHPP = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoHPP) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS CABECERA HPP, " << " ARCHIVO [" << sNombreArchivoHPP << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo HPP con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoHPP, (char*)"hpp", sComentariosBito);

                // Validar la sintaxis del archivo HPP que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoHPP);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".h" || entry.path().extension() == ".H"))
        {
            // Obtener el nombre del archivo de cabeceras H.
            std::string sNombreArchivoH = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoH) == archivosProcesados.end())
            {
                // Validar la sintaxis del archivo H antes de procesarlo con IA y BITO

                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS CABECERA H, " << " ARCHIVO [" << sNombreArchivoH << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo H con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoH, (char*)"h", sComentariosBito);

                // Validar la sintaxis del archivo H que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoH);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".cs" || entry.path().extension() == ".CS"))
        {
            // Obtener el nombre del archivo CS.
            std::string sNombreArchivoCS = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoCS) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS CSHARP, " << " ARCHIVO [" << sNombreArchivoCS << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo CSHARP con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoCS, (char*)"cs", sComentariosBito);

                // Validar la sintaxis del archivo CSHARP que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoCS);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".py" || entry.path().extension() == ".PY"))
        {
            // Obtener el nombre del archivo PYTHON
            std::string sNombreArchivoPY = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoPY) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS PYTHON, " << " ARCHIVO [" << sNombreArchivoPY << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo PYTHON con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoPY, (char*)"py", sComentariosBito);

                // Validar la sintaxis del archivo PYTHON que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoPY);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".vb" || entry.path().extension() == ".VB"))
        {
            // Obtener el nombre del archivo VISUAL BASIC
            std::string sNombreArchivoVB = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoVB) == archivosProcesados.end())
            {
                // Validar la sintaxis del archivo Visual Basic antes de procesarlo con IA y BITO

                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS VISUAL BASIC 6, " << " ARCHIVO [" << sNombreArchivoVB << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo VISUAL BASIC 6 con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoVB, (char*)"vb", sComentariosBito);

                // Validar la sintaxis del archivo VISUAL BASIC 6 que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, ARCHIVO EN VISUAL BASIC 6, " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoVB);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }

        if (entry.is_regular_file() && (entry.path().extension() == ".bas" || entry.path().extension() == ".BAS"))
        {
            // Obtener el nombre del archivo VISUAL BASIC .NET.
            std::string sNombreArchivoVBN = entry.path().string();

            // Si el archivo no ha sido procesado aún entonces lo procesamos y lo agregamos al set de archivos procesados
            if (archivosProcesados.find(sNombreArchivoVBN) == archivosProcesados.end())
            {
                //Iniciamos el reloj
                std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
                startBito = std::chrono::system_clock::now();
                std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

                ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

                // Eliminar el salto de línea
                cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

                std::cout << "INICIA PROCESO DE CONVERSION CON IA ARCHIVOS VISUAL BASIC .NET, " << " ARCHIVO [" << sNombreArchivoVBN << "] " << cBufferIniBito << "." << std::endl;

                // Procesar el archivo VISUAL BASIC .NET con IA y BITO y guardar el resultado en el archivo bito.csv
                procesarArchivo(sNombreArchivoVBN, (char*)"bas", sComentariosBito);

                // Validar la sintaxis del archivo VISUAL BASIC .NET que se generó con IA y BITO

                endBito = std::chrono::system_clock::now();
                std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

                ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

                // Eliminar el salto de línea
                cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

                // Calcula la duración
                //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
                std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
                dExecutionTimeBito = elapsed_seconds_bito.count();
                dExecutionTimeInMinutes = elapsed_seconds_bito.count() / 60;

                buffer_file.str("");
                buffer_file_txt.str("");

                std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, ARCHIVO EN VISUAL BASIC .NET " << cBufferFinBito << "." << std::endl;
                // Imprime la duración en segundos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeBito << " SEGUNDOS." << std::endl;
                // Imprime la duración en minutos
                std::cout << "TIEMPO TRANSCURRIDO: " << dExecutionTimeInMinutes << " MINUTOS." << std::endl;

                // Agregar el archivo al set de archivos procesados para no volverlo a procesar en el futuro.
                archivosProcesados.insert(sNombreArchivoVBN);

                // Guardar el set de archivos procesados en el archivo archivos_procesados_bito.csv para no volverlos a procesar en el futuro.
                guardarArchivosProcesados(sRutaCompletaArchivosProcesados, archivosProcesados);
            }
        }
        
        // Siempre agregamos la fecha y hora de fin del proceso en formato de dd/mm/yyyy hh:mm:ss de 24 horas México.
        end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time);

        // Eliminar el salto de línea
        cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

        std::cout << "FINALIZA PROCESO DE CONVERSION DE TODOS LOS ARCHIVOS CON IA, " << cBufferFinBito << "." << std::endl;

        // Calcula la duración
        //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
        std::chrono::duration<double> elapsed_seconds = end - start;
        double execution_time = elapsed_seconds.count();
        execution_time_in_minutes = elapsed_seconds.count() / 60;

        // Imprime la duración
        std::cout << "Tiempo transcurrido: " << execution_time << " segundos." << std::endl;
        std::cout << "Tiempo transcurrido: " << execution_time_in_minutes << " minutos." << std::endl;
	}

    return 1;
}

int CIA::procesarConBITO(char* cRootPath, char* cBito)
{
    char cPath[MAX_PATH] = { 0 };
    char cFile[MAX_PATH] = { 0 };
    char cFileBito[600] = { 0 };
    char cPathFileBito[300] = { 0 };
    char cPathFilePrompt[300] = { 0 };
    char cStemBito[150] = { 0 };
    char cBufferIniBito[26] = { 0 };
    char cBufferFinBito[26] = { 0 };
    char cPathFileNoBito[MAX_PATH] = { 0 };

    double execution_time_bito = 0.0;
    double execution_time_in_minutes = 0.0;

    std::ofstream csv_file_bito(cBito);

    csv_file_bito << "ARCHIVO|HORA_INICIO|HORA_FIN|TIEMPO_EN_SEGUNDOS|TIEMPO_EN_MINUTOS|PHP_LINT_CHECK|COMENTARIOS_BITO" << std::endl;

    if (!std::filesystem::exists(cRootPath))
    {
        std::cerr << "El directorio no existe: " << cRootPath << std::endl;
        return 0;
    }

    std::string strStemBito;
    std::string sPathFileBitoTxt;
    std::string sContenidoTxtLint;

    std::string linea;
    std::string contenido;

    std::stringstream buffer_file;
    std::stringstream buffer_file_txt;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time);

    // Eliminar el salto de línea
    cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

    std::cout << "INICIA PROCESO DE CONVERSION DE ARCHIVOS CON IA, " << cBufferIniBito << "." << std::endl;
    csv_file_bito << "INICIA PROCESO DE CONVERSION DE ARCHIVOS CON IA| | | | | |" << cBufferIniBito << std::endl;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(cRootPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".php")
        {
            sprintf_s(cPath, sizeof(cPath), "%S", entry.path().parent_path().c_str());
            sprintf_s(cFile, sizeof(cFile), "%S", entry.path().filename().c_str());
            sprintf_s(cPathFileBito, sizeof(cPathFileBito), "%s\\%s", cPath, cFile);
            sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimization.pmt"); //cStem

            strStemBito = cFile;

            sprintf_s(cStemBito, sizeof(cStemBito), "%s", strStemBito.substr(0, strStemBito.find_last_of(".")).c_str());

            memset(cFileBito, ' ', sizeof(cFileBito));

            strcpy_s(cFileBito, "type ");
            strcat_s(cFileBito, cPathFileBito);
            strcat_s(cFileBito, " | bito.exe");
            strcat_s(cFileBito, cPathFilePrompt);
            strcat_s(cFileBito, " > ");
            strcat_s(cFileBito, cPath);
            strcat_s(cFileBito, "\\");
            strcat_s(cFileBito, cStemBito);
            strcat_s(cFileBito, ".bito");

            std::cout << cPathFileBito << std::endl;

            //Iniciamos el reloj
            std::chrono::time_point<std::chrono::system_clock> startBito, endBito;
            startBito = std::chrono::system_clock::now();
            std::time_t start_time_bito = std::chrono::system_clock::to_time_t(startBito);

            ctime_s(cBufferIniBito, sizeof cBufferIniBito, &start_time_bito);

            // Eliminar el salto de línea
            cBufferIniBito[strcspn(cBufferIniBito, "\n")] = 0;

            std::cout << "INICIA PROCESO DE CONVERSION CON IA, " << cBufferIniBito << "." << std::endl;

            system(cFileBito);

            memset(cStemBito, ' ', sizeof(cStemBito));
            sprintf_s(cStemBito, sizeof(cStemBito), "%s\\%s.bito", cPath, strStemBito.substr(0, strStemBito.find_last_of(".")).c_str());

            sprintf_s(cPathFileNoBito, sizeof(cPathFileNoBito), "%s\\NoConvertBito.csv", cPath);

            if (validarArchivoBito(cStemBito, cPathFileNoBito) == false)
            {
                std::cout << "El archivo: " << cStemBito << " NO SE CONVIRTIO CON BITO." << std::endl;
            }
            else
            {
                //1 - Abres y lees el archivo original 'prueba_ws.php'.
                //2 - Renombras el archivo 'prueba_ws.php' como 'ori_prueba_ws.php'.
                //3 - Lees el archivo 'prueba_ws.bito.php', si encuentra una línea que contiene ````php`, cambia el estado de la variable bool `bCopy`. Si `bCopy` es verdadero, 
                //las líneas se escriben en `prueba_ws.php`, si es falso, las líneas se escriben en `prueba_ws.bito.txt`..
                //4. Si encuentra una línea que contiene solo `````, cambia el estado de la variable bool `bEnd`. Si `BEnd` es verdadero, 
                //las líneas se escriben en `prueba_ws.php`, si es falso, las líneas se escriben al final del archivo `prueba_ws.bito.txt`..
                //5 - Al final, cierra todos los archivos abiertos.
                sPathFileBitoTxt = " ";
                quitarComentariosBito(cPathFileBito, sPathFileBitoTxt);

                memset(cStemBito, ' ', sizeof(cStemBito));
                sprintf_s(cStemBito, sizeof(cStemBito), "%s\\%s.lin", cPath, strStemBito.substr(0, strStemBito.find_last_of(".")).c_str());

                // Ejecutar php -l para validar la sintaxis del archivo.
                sprintf_s(cFileBito, sizeof(cFileBito), "php -l %s > %s", cPathFileBito, cStemBito);

                // Ejecutar el comando
                system(cFileBito);

                // Leer el archivo de salida y obtener el resultado.
                std::ifstream input_file(cStemBito);
                if (input_file)
                {
                    buffer_file << input_file.rdbuf();
                    input_file.close();

                    sContenidoTxtLint = buffer_file.str();
                    // Elimina todos los caracteres de salto de línea
                    sContenidoTxtLint.erase(std::remove(sContenidoTxtLint.begin(), sContenidoTxtLint.end(), '\n'), sContenidoTxtLint.end());
                }
                else
                {
                    std::cerr << "NO SE PUDO ABRIR EL ARCHIVO: " << cStemBito << std::endl;
                }

                contenido = "";
                std::ifstream input_file_txt(sPathFileBitoTxt);
                if (input_file_txt)
                {
                    while (std::getline(input_file_txt, linea))
                    {
                        // Elimina los saltos de línea y las comas
                        linea.erase(std::remove(linea.begin(), linea.end(), '\n'), linea.end());
                        linea.erase(std::remove(linea.begin(), linea.end(), ','), linea.end());
                        contenido += linea;
                    }
                    input_file_txt.close();
                }


                //std::ifstream input_file_txt(sPathFileBitoTxt);
                //if (input_file_txt) 
                //{
                //    buffer_file_txt << input_file_txt.rdbuf();
                //    input_file_txt.close();
                //}
                //else 
                //{
                //    std::cerr << "No se pudo abrir el archivo: " << sPathFileBitoTxt << std::endl;
                //}

                //sContenidoTxtBito = buffer_file_txt.str();

                //// Elimina los saltos de línea y las comas
                //for (size_t pos = sContenidoTxtBito.find("\n"); pos != std::string::npos; pos = sContenidoTxtBito.find("\n", pos)) 
                //{
                //    sContenidoTxtBito.erase(pos, 1);
                //}
                //for (size_t pos = sContenidoTxtBito.find(","); pos != std::string::npos; pos = sContenidoTxtBito.find(",", pos)) 
                //{
                //    sContenidoTxtBito.erase(pos, 1);
                //}

                //for (size_t pos = sContenidoTxtBito.find(","); pos != std::string::npos; pos = sContenidoTxtBito.find(",", pos)) 
                //{
                //    sContenidoTxtBito.replace(pos, 1, " ");
                //}
            }

            endBito = std::chrono::system_clock::now();
            std::time_t end_time_bito = std::chrono::system_clock::to_time_t(endBito);

            ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time_bito);

            // Eliminar el salto de línea
            cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

            // Calcula la duración
            //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
            std::chrono::duration<double> elapsed_seconds_bito = endBito - startBito;
            execution_time_bito = elapsed_seconds_bito.count();
            execution_time_in_minutes = elapsed_seconds_bito.count() / 60;

            csv_file_bito << cPathFileBito << "|" << cBufferIniBito << "|" << cBufferFinBito << "|" << execution_time_bito << "|" << execution_time_in_minutes << "|" << sContenidoTxtLint << "|" << contenido << std::endl;
            buffer_file.str("");
            buffer_file_txt.str("");
            contenido = "";

            std::cout << "FINALIZA PROCESO DE CONVERSION CON IA, " << cBufferFinBito << "." << std::endl;
            // Imprime la duración en segundos
            std::cout << "TIEMPO TRANSCURRIDO: " << execution_time_bito << " SEGUNDOS." << std::endl;
            // Imprime la duración en minutos
            std::cout << "TIEMPO TRANSCURRIDO: " << execution_time_in_minutes << " MINUTOS." << std::endl;

            std::cout << "" << std::endl;
        }
    }

    end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    ctime_s(cBufferFinBito, sizeof cBufferFinBito, &end_time);

    // Eliminar el salto de línea
    cBufferFinBito[strcspn(cBufferFinBito, "\n")] = 0;

    std::cout << "FINALIZA PROCESO DE CONVERSION DE TODOS LOS ARCHIVOS CON IA, " << cBufferFinBito << "." << std::endl;
    csv_file_bito << "FINALIZA PROCESO DE CONVERSION DE TODOS LOS ARCHIVOS CON IA| | | | | |" << cBufferFinBito << std::endl;

    // Calcula la duración
    //Si prefieres la duración en milisegundos, puedes usar std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().
    std::chrono::duration<double> elapsed_seconds = end - start;
    double execution_time = elapsed_seconds.count();
    execution_time_in_minutes = elapsed_seconds.count() / 60;

    csv_file_bito << "Tiempo transcurrido|" << execution_time << " segundos| | | | | " << std::endl;
    csv_file_bito << "Tiempo transcurrido|" << execution_time_in_minutes << " minutos| | | | | | " << std::endl;

    // Imprime la duración
    std::cout << "TIEMPO TRANSCURRIDO: " << execution_time << " SEGUNDOS." << std::endl;
    std::cout << "TIEMPO TRANSCURRIDO: " << execution_time_in_minutes << " MINUTOS." << std::endl;

    csv_file_bito.close();

    std::cout << "" << std::endl;
    std::cout << "PROCESO FINALIZADO..." << std::endl;
    std::cout << "PRESIONA UNA TECLA PARA CONTINUAR..." << std::endl;
    int iTecla = 0;
    iTecla = _getch();
    menu();

    return 0;
}


int CIA::calcularFechaFinProyectoCaptura(char* cRootPath, std::string sLenguaje, int &iTotalDeOcurrencias, int &iNumColaboradores, int &iOcurrenciasPorLenguaje, int &iTotalArchivos)
{ 
    calcular(cRootPath, iTotalArchivos, iTotalDeOcurrencias, iOcurrenciasPorLenguaje, iNumColaboradores, sLenguaje);

    return 0;
}

// Función para calcular la fecha final
std::chrono::year_month_day CIA::get_end_date(std::chrono::year_month_day start, days length) 
{
    --length;
    auto w = weeks{ length / days{5} };
    length %= 5;
    auto end = sys_days{ start } + w + length;
    auto wd = std::chrono::weekday{ end };
    if (wd == std::chrono::Saturday) end += days{ 2 };
    else if (wd == std::chrono::Sunday) end += days{ 1 };
    return end;
}

// Función para calcular la fecha final
int CIA::calcularFechaFinal(int iBusiness_days, const std::string sFechaArg, std::string &sFechaInicial, std::string &sFechaFinal, int &iTotalDias, int &iTtotalDiasInhabiles, std::string &sFechaFinalLunVie)
{
    std::locale::global(std::locale("es_MX.UTF8"));
    setlocale(LC_ALL, "es_MX.UTF8");

    // Fecha de inicio
    int iYear   = 0;
    int iMonth  = 0;
    int iDay    = 0;

    iYear   = std::stoi(sFechaArg.substr(0, 4));
    iMonth  = std::stoi(sFechaArg.substr(5, 2));
    iDay    = std::stoi(sFechaArg.substr(8, 2));

    //std::cout << "" << std::endl;
    //std::cout << "INTRODUCE EL ANIO (AAAA): ";
    //while (!(std::cin >> iYear))
    //{
    //    std::cout << "POR FAVOR, INTRODUCE UN NUMERO VALIDO PARA EL ANIO: ";
    //    std::cin.clear();
    //    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //}

    //std::cout << "INTRODUCE EL MES(MM): ";
    //while (!(std::cin >> iMonth))
    //{
    //    std::cout << "POR FAVOR, INTRODUCE UN NUMERO VALIDO PARA EL MES: ";
    //    std::cin.clear();
    //    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //}
    //std::cout << "INTRODUCE EL DIA(DD): ";
    //while (!(std::cin >> iDay)) 
    //{
    //    std::cout << "POR FAVOR, INTRODUCE UN NUMERO VALIDO PARA EL DIA: ";
    //    std::cin.clear();
    //    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //}
    //std::cout << "" << std::endl;

    sys_days start = std::chrono::year{ iYear } / std::chrono::month{ static_cast<unsigned int>(iMonth) } / std::chrono::day{ static_cast<unsigned int>(iDay) };

    // Imprime la fecha inicial.
    /*std::cout << "LA FECHA INICIAL ES: " << std::chrono::year_month_day{ start } << std::endl;*/
    // Convierte start a std::string
    std::ostringstream os;
    os << std::chrono::year_month_day{ start };
    sFechaInicial = os.str();
    //std::cout << "LA FECHA INICIAL ES: " << sFechaInicial << std::endl;
    
    // Contador de días totales
    int total_days = 0;
    int total_days_inhabil = 0;

    while (iBusiness_days > 0) // 133
    {
        // Avanza un día
        start += days{ 1 }; //2024-01-09 + 133 = 2024-05-20
        total_days++; // incrementando el contador de días totales

        // Verifica si el día es fin de semana
        if (std::chrono::weekday{ start } != std::chrono::Saturday && std::chrono::weekday{ start } != std::chrono::Sunday)
        {
            total_days_inhabil++;
        }
        iBusiness_days--;
    }

    // Calcula la fecha final
    std::chrono::year_month_day end_date = get_end_date(std::chrono::year{ iYear } / std::chrono::month{ static_cast<unsigned int>(iMonth) } / std::chrono::day{ static_cast<unsigned int>(iDay) }, std::chrono::days{ total_days });

    // Convierte end_date a std::string
    std::ostringstream osi;
    osi << end_date;
    std::string str_end_date = osi.str();
    sFechaFinal = str_end_date;
    //std::cout << "Fecha Final.... : " << sFechaFinal << std::endl;
    //std::cout << "LA FECHA FINAL ES: " << end_date << std::endl;
    //std::cout << "LA FECHA FINAL ES: " << sFechaFinal << std::endl;
    
    std::cout << "TOTAL DE DIAS  ES: " << total_days << std::endl;;
    std::cout << std::endl;

    auto start_duration = start.time_since_epoch();
    long start_long = start_duration.count();
    start_long = start_long + 86400; // Agrega un día a la fecha inicial

    auto end_date_sys_days = std::chrono::sys_days{ end_date };
    auto end_date_duration = end_date_sys_days.time_since_epoch();
    //long end_date_long = end_date_duration.count();

    iTotalDias = total_days;
    iTtotalDiasInhabiles = total_days_inhabil;

    std::cout << "LA FECHA INICIAL ES: " << sFechaInicial << std::endl;

    //lFechaFinal = end_date_long;
    //// Imprime la fecha final
    std::cout << "TOTAL DE DIAS ES : " << iTotalDias << std::endl;
    std::cout << "TOTAL DE DIAS (excluyendo fines de semana) es : " << iTtotalDiasInhabiles << std::endl;

    std::ostringstream oslv;
    oslv << std::chrono::year_month_day{ start };
    sFechaFinalLunVie = oslv.str();
    //std::cout << "LA FECHA FINAL (excluyendo fines de semana) es: " << std::chrono::year_month_day{ start } << '\n' << std::endl;
    std::cout << "LA FECHA FINAL (excluyendo fines de semana) es: " << sFechaFinalLunVie << std::endl;

    return iTtotalDiasInhabiles;
}

/*
Tot Meta = 176
Tot Rec  = 3
Tot Sem = Tot Meta * Tot Rec;
Duración = Tot Ocu / Tot Sem.
Duración Días = (Tot Ocu / Tot Sem.) / 5
*/
int CIA::calcular(std::string sRootPath, int &iTotalArchivos, int &iTotalOcurrencias, int &iOcurrenciasPorSemanaPorColaborador, int &iNumeroDeColaboradores, const std::string sLenguaje)
{
    //Generar la ruta del archivo de salida
    std::string sFinDeProyecto = sRootPath + "\\finProyecto.csv";
    
    std::ofstream csv_file;

    csv_file.open(sFinDeProyecto, std::ios::out | std::ios::app);
    if(!csv_file)
	{
		std::cerr << "NO SE PUDO ABRIR EL ARCHIVO: " << sFinDeProyecto << std::endl;
		return 1;
	}

    //escribir la cabecera en el archivo CSV
    csv_file << "LENGUAJE,OCURRENCIAS,X SEMANA,CANT_COLAB,TOT_SEM,TOT_DIAS,TOT_HORAS,FECHA_INI,FECHA_FIN,TOT_DIAS_LUN_A_VIE,FECHA_FIN_LUN_A_VIE" << std::endl;

    int iTotSem = iOcurrenciasPorSemanaPorColaborador * iNumeroDeColaboradores;
    int iDuracion = iTotalOcurrencias / iTotSem;
    int iDuracionDías = iDuracion * 7;
    int iDuracionHoras = iDuracionDías * 9; // Calcula el total en horas

    std::cout << "" << std::endl;
    std::cout << "TOTAL DE OCURRENCIAS ENCONTRADAS: " << iTotalOcurrencias << " EN EL TOTAL DE " << iTotalArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
    std::cout << "TOTAL DE OCURRENCIAS POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
    std::cout << "DURACION TOTAL DE SEMANAS: " << iDuracion << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << sLenguaje << "." << std::endl;
    std::cout << "TOTAL DE DIAS: " << iDuracionDías << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << sLenguaje << "." << std::endl;
    std::cout << "TOTAL DE HORAS: " << iDuracionHoras << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << sLenguaje << "." << std::endl; // Muestra el total en horas

    long lFechaInicial          = 0L;
    long lFechaFinal            = 0L;
    int  iTotalDias             = 0;
    int  iTotalDiasInhabiles    = 0;

    std::string sFechaInicial; 
    std::string sFechaFinal;
    std::string sFechaFinalLunVie;
    std::string sFechaArg;

    calcularFechaFinal((int)iDuracionDías, sFechaArg, sFechaInicial, sFechaFinal, iTotalDias, iTotalDiasInhabiles, sFechaFinalLunVie);

    csv_file << sLenguaje << "," << iTotalOcurrencias << "," << iOcurrenciasPorSemanaPorColaborador << "," << iNumeroDeColaboradores << "," << iTotSem << "," << iDuracionDías << "," << iDuracionHoras << "," << lFechaInicial << "," << lFechaFinal << "," << iTotalDiasInhabiles << std::endl;
    
    csv_file.close();

    return 0;
}

/*
Tot Meta = 176
Tot Rec  = 3
Tot Sem = Tot Meta * Tot Rec;
Duración = Tot Ocu / Tot Sem.
Duración Días = (Tot Ocu / Tot Sem.) / 5
*/
int CIA::calcularFinDeProyectoMap(const std::map<std::string, int>& mapMetaSemanal, const std::map<std::string, int>& mapSentencias, const std::map<std::string, int>& mapDeprecated, std::string sRootPath, int& iTotalArchivos, int& iNumeroDeColaboradores, const int iHigh, const int iMedium, const int iLow, std::string sNombreProyecto, const long lIdProyecto, const int iDataBase)
{
    //Generar la ruta del archivo de salida
    std::string sFinDeProyecto = sRootPath + "\\finProyecto.csv";

    std::ofstream csv_file;

    csv_file.open(sFinDeProyecto, std::ios::out | std::ios::app);
    if (!csv_file)
    {
        std::cerr << "NO SE PUDO ABRIR EL ARCHIVO: " << sFinDeProyecto << std::endl;
        return ERROR_ACCESS_DENIED;
    }

    //escribir la cabecera en el archivo CSV
    //csv_file << "LENGUAJE|OCURRENCIAS|X_SEMANA|CANT_COLAB|TOT_SEM|TOT_DIAS|TOT_HORAS|FECHA_INI|FECHA_FIN|" << std::endl;
    csv_file << "LENGUAJE,OCURRENCIAS,X SEMANA,CANT_COLAB,TOT_SEM,TOT_DIAS,TOT_HORAS,FECHA_INI,FECHA_FIN,TOT_DIAS_LUN_A_VIE,FECHA_FIN_LUN_A_VIE" << std::endl;

    int  iTotSem = 0;
    int  iDuracion = 0;
    int  iDuracionDias = 0;
    int  iDuracionHoras = 0;
    int  iTotalDias = 0;
    int  iTotalDiasInhabiles = 0;
    int  iTotalSenObsCheckmarx = 0;
    int  iTotalCheckmarx = 0;

    int iOcurrenciasPorSemanaPorColaborador = 0;
    int iTotalSentencias = 0;
    int iTotalDeprecated = 0;
    std::string sLenguaje = "";

    //int iTotSem = iOcurrenciasPorSemanaPorColaborador * iNumeroDeColaboradores;
    //int iDuracion = iTotalOcurrencias / iTotSem;
    //int iDuracionDías = iDuracion * 7;
    //int iDuracionHoras = iDuracionDías * 9;

    for (const auto& parMeta : mapMetaSemanal)
    {
        iOcurrenciasPorSemanaPorColaborador += parMeta.second;
        sLenguaje.append(parMeta.first);
    }
    
    iTotSem = iOcurrenciasPorSemanaPorColaborador * iNumeroDeColaboradores;

    for (const auto& parSen : mapSentencias)
    {
        iTotalSentencias += parSen.second;
        sLenguaje.append(parSen.first);
    }

    for (const auto& parDep : mapDeprecated)
    {
        iTotalDeprecated += parDep.second;
		sLenguaje.append(parDep.first);
    }

    iTotalCheckmarx = iHigh + iMedium + iLow;
    iTotalSenObsCheckmarx   = iTotalSentencias + iTotalDeprecated + iTotalCheckmarx;
    iDuracion      = iTotalSenObsCheckmarx / iTotSem;
    iDuracionDias  = iDuracion * 7;
    iDuracionHoras = iDuracionDias * 9; // Calcula el total en horas

    //std::cout << "Lenguaje de programación: " << par.first << ", Número de ocurrencias: " << par.second << std::endl;

    //iTotSem = par.second * iNumeroDeColaboradores;
    //iDuracion = iTotalSenObs / iTotSem;
    //iDuracionDías = iDuracion * 7;
    //iDuracionHoras = iDuracionDías * 9; // Calcula el total en horas

    std::cout << std::endl;
    std::cout << "TOTAL DE OCURRENCIAS ENCONTRADAS: " << iTotalSenObsCheckmarx << " EN EL TOTAL DE " << iTotalArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
    std::cout << "TOTAL DE OCURRENCIAS POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
    //std::cout << "DURACION TOTAL DE SEMANAS: " << iDuracion << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << par.first << "." << std::endl;
    //std::cout << "TOTAL DE DIAS: " << iDuracionDías << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << par.first << "." << std::endl;
    //std::cout << "TOTAL DE HORAS: " << iDuracionHoras << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << par.first << "." << std::endl; // Muestra el total en horas
    //std::cout << std::endl;

    std::string sFechaInicial;
    std::string sFechaFinal;
    std::string sFechaFinalLunVie;
    std::string sFechaArg;

    calcularFechaFinal(iDuracionDias, sFechaArg, sFechaInicial, sFechaFinal, iTotalDias, iTotalDiasInhabiles, sFechaFinalLunVie);

    csv_file << sLenguaje << "," << iTotalSenObsCheckmarx << "," << iOcurrenciasPorSemanaPorColaborador << "," << iNumeroDeColaboradores << "," << iTotSem << "," << iDuracionDias << "," << iDuracionHoras << "," << sFechaInicial << "," << sFechaFinal << "," << iTotalDiasInhabiles << "," << sFechaFinalLunVie << "," << std::endl;
    //csv_file << par.first << "|" << iTotalSenObs << "|" << par.second << "|" << iNumeroDeColaboradores << "|" << iTotSem << "|" << iDuracionDías << "|" << iDuracionHoras << "|" << lFechaInicial << "|" << lFechaFinal << "|" << std::endl;
    csv_file.close();
    
    if ( registrarFechasDeProyecto(lIdProyecto, sNombreProyecto, sLenguaje, iTotalSenObsCheckmarx, iOcurrenciasPorSemanaPorColaborador, iNumeroDeColaboradores, iTotSem,
            iDuracionDias, iDuracionHoras , sFechaInicial ,sFechaFinal, iTotalDiasInhabiles, sFechaFinalLunVie, iDataBase ) )
    {

    }

    return 0;
}


/*
Tot Meta = 176
Tot Rec  = 3
Tot Sem = Tot Meta * Tot Rec;
Duración = Tot Ocu / Tot Sem.
Duración Días = (Tot Ocu / Tot Sem.) / 5
*/
int CIA::calcularFinDeProyectoVecMap(const std::vector<Metricas>& vecMetaSemanal, const std::map<std::string, int>& mapSentencias, const std::map<std::string, int>& mapDeprecated, const std::vector<Programa> vcProgramas, std::string sRootPath, int& iNumeroDeColaboradores, const int iHigh, const int iMedium, const int iLow, std::string sNombreProyecto, const long lIdProyecto, const std::string sTipoDeMigracion, const int iDataBase)
{
    int  iTotSem = 0;
    int  iDuracion = 0;
    int  iDuracionDías = 0;
    int  iTotalSenObsCheckmarx = 0;
    int  iTotalCheckmarx = 0;

    int iTotalSentencias = 0;
    int iTotalDeprecated = 0;
    std::string sLenguajeSQL = "";
    std::string sObsoleto = "";

    // Recorrer el vector vecMetaSemanal
    std::vector<Metricas>::const_iterator it;
    for (it = vecMetaSemanal.begin(); it != vecMetaSemanal.end(); ++it)
    {
        if (sTipoDeMigracion.compare("mig") == 0)
        {
            iTotSem = it->iMigracion * iNumeroDeColaboradores;
            std::cout << std::endl;
            std::cout << "TOTAL DE MIGRACIONES POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
        }
        else if (sTipoDeMigracion.compare("vul") == 0)
        {
            iTotSem = it->iVulnerabilidad * iNumeroDeColaboradores;
            std::cout << std::endl;
            std::cout << "TOTAL DE VULNERABILIDADES POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
        }

        for (const auto& parSen : mapSentencias)
        {
            sLenguajeSQL.append(parSen.first);
            iTotalSentencias += parSen.second;
        }

        for (const auto& parDep : mapDeprecated)
        {
            sObsoleto.append(parDep.first);
            iTotalDeprecated += parDep.second;
        }

        iTotalCheckmarx = iHigh + iMedium + iLow;
        iTotalSenObsCheckmarx = iTotalSentencias + iTotalDeprecated + iTotalCheckmarx;
        
        if (iTotSem != 0) 
        {
            iDuracion = iTotalSenObsCheckmarx / iTotSem;
        }
        else 
        {
            std::cout << "Error: iTotSem es cero, no se puede dividir por cero." << std::endl;
            return -1;
        }

        iDuracionDías = iDuracion * 7;

        // Iterar vcProgramas
        std::vector<Programa>::const_iterator itP;
        for (itP = vcProgramas.begin(); itP != vcProgramas.end(); ++itP)
        {
            std::cout << std::endl;
            std::cout << "TOTAL DE SENTENCIAS ENCONTRADAS     : " << iTotalSentencias << " EN EL TOTAL DE " << itP->iArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
            std::cout << "TOTAL DE FUNCIONES OBSOLETAS        : " << iTotalDeprecated << " EN EL TOTAL DE " << itP->iArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
            std::cout << "TOTAL DE VULNERABILIDADES CHECKMARX : " << iTotalCheckmarx << " EN EL TOTAL DE " << itP->iArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
        }
    }

    std::cout << "TOTAL DE OCURRENCIAS ENCONTRADAS: " << iTotalSenObsCheckmarx << " EN EL TOTAL DE " << /*iTotalArchivos*/ 0 << " ARCHIVOS RECORRIDOS." << std::endl;
    std::cout << "TOTAL DE OCURRENCIAS POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;

    return 0;
}

//int CIA::calcularFinDeProyectoVecMap(const std::vector<Metricas>& vecMetaSemanal, const std::map<std::string, int>& mapSentencias, const std::map<std::string, int>& mapDeprecated, const std::vector<Programa> vcProgramas, std::string sRootPath, int& iNumeroDeColaboradores, const int iHigh, const int iMedium, const int iLow, std::string sNombreProyecto, const long lIdProyecto, const std::string sTipoDeMigracion, const int iDataBase)
//{
//    int  iTotSem                            = 0;
//    int  iDuracion                          = 0;
//    int  iDuracionDías                      = 0;
//    int  iDuracionHoras                     = 0;
//    int  iTotalDias                         = 0;
//    int  iTotalDiasInhabiles                = 0;
//    int  iTotalSenObsCheckmarx              = 0;
//    int  iTotalCheckmarx                    = 0;
//
//    int iOcurrenciasPorSemanaPorColaborador = 0;
//    int iMigPorSemanaPorColaborador = 0;
//    int iVulPorSemanaPorColaborador = 0;
//    int iTotalSentencias            = 0;
//    int iTotalDeprecated            = 0;
//    std::string sLenguajeSQL        = "";
//    std::string sObsoleto           = "";
//    std::string sMetrica            = "";
//
//    //int iTotSem = iOcurrenciasPorSemanaPorColaborador * iNumeroDeColaboradores;
//    //int iDuracion = iTotalOcurrencias / iTotSem;
//    //int iDuracionDías = iDuracion * 7;
//    //int iDuracionHoras = iDuracionDías * 9;
//
//    // Recorrer el vector vecMetaSemanal
//
//    std::vector<Metricas>::const_iterator it;
//    for (it = vecMetaSemanal.begin(); it != vecMetaSemanal.end(); ++it)
//    {
//  //      sMetrica.append(it->sLenguaje);
//		//iMigPorSemanaPorColaborador = it->iMigracion;
//  //      iVulPorSemanaPorColaborador = it->iVulnerabilidad;
//
//        if (sTipoDeMigracion.compare("mig") == 0)
//        {
//            iTotSem = it->iMigracion * iNumeroDeColaboradores;
//            std::cout << std::endl;
//            std::cout << "TOTAL DE MIGRACIONES POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
//        }
//        else if (sTipoDeMigracion.compare("vul") == 0)
//        {
//            iTotSem = it->iVulnerabilidad * iNumeroDeColaboradores;
//            std::cout << std::endl;
//            std::cout << "TOTAL DE VULNERABILIDADES POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
//        }
//
//        for (const auto& parSen : mapSentencias)
//        {
//            iTotalSentencias += parSen.second;
//            sLenguajeSQL.append(parSen.first);
//        }
//
//        for (const auto& parDep : mapDeprecated)
//        {
//            iTotalDeprecated += parDep.second;
//            sObsoleto.append(parDep.first);
//        }
//
//        iTotalCheckmarx         = iHigh + iMedium + iLow;
//        iTotalSenObsCheckmarx   = iTotalSentencias + iTotalDeprecated + iTotalCheckmarx;
//        iDuracion               = iTotalSenObsCheckmarx / iTotSem;
//        iDuracionDías           = iDuracion * 7;
//        iDuracionHoras          = iDuracionDías * 9; // Calcula el total en horas
//        
//        // Iterar vcProgramas
//        std::vector<Programa>::const_iterator itP;
//        for (itP = vcProgramas.begin(); itP != vcProgramas.end(); ++itP)
//		{
//            std::cout << std::endl;
//            std::cout << "TOTAL DE SENTENCIAS ENCONTRADAS     : " << iTotalSentencias << " EN EL TOTAL DE " << itP->iArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
//            std::cout << "TOTAL DE FUNCIONES OBSOLETAS        : " << iTotalDeprecated << " EN EL TOTAL DE " << itP->iArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
//            std::cout << "TOTAL DE VULNERABILIDADES CHECKMARX : " << iTotalCheckmarx  << " EN EL TOTAL DE " << itP->iArchivos << " ARCHIVOS RECORRIDOS." << std::endl;
//		}
//	}
//
//    //for (const auto& vecMeta : vecMetaSemanal)
//    //{
//    //    iOcurrenciasPorSemanaPorColaborador += parMeta.second;
//    //    sLenguaje.append(parMeta.first);
//    //}
//
// //   if (sTipoDeMigracion.compare("mig") == 0)
// //   {
//	//	iOcurrenciasPorSemanaPorColaborador = iMigPorSemanaPorColaborador;
//	//}
// //   else if (sTipoDeMigracion.compare("vul") == 0)
// //   {
//	//	iOcurrenciasPorSemanaPorColaborador = iVulPorSemanaPorColaborador;
//	//}
// //   else
// //   {
// //       iOcurrenciasPorSemanaPorColaborador = 50;
// //   }
//
// //   iTotSem = iOcurrenciasPorSemanaPorColaborador * iNumeroDeColaboradores;
//
//    //for (const auto& parSen : mapSentencias)
//    //{
//    //    iTotalSentencias += parSen.second;
//    //    sLenguajeSQL.append(parSen.first);
//    //}
//
//    //for (const auto& parDep : mapDeprecated)
//    //{
//    //    iTotalDeprecated += parDep.second;
//    //    sObsoleto.append(parDep.first);
//    //}
//
//    //iTotalCheckmarx = iHigh + iMedium + iLow;
//    //iTotalSenObsCheckmarx = iTotalSentencias + iTotalDeprecated + iTotalCheckmarx;
//    //iDuracion = iTotalSenObsCheckmarx / iTotSem;
//    //iDuracionDías = iDuracion * 7;
//    //iDuracionHoras = iDuracionDías * 9; // Calcula el total en horas
//
//    //std::cout << "Lenguaje de programación: " << par.first << ", Número de ocurrencias: " << par.second << std::endl;
//
//    //iTotSem = par.second * iNumeroDeColaboradores;
//    //iDuracion = iTotalSenObs / iTotSem;
//    //iDuracionDías = iDuracion * 7;
//    //iDuracionHoras = iDuracionDías * 9; // Calcula el total en horas
//
//    std::cout << std::endl;
//    std::cout << "TOTAL DE OCURRENCIAS ENCONTRADAS: " << iTotalSenObsCheckmarx << " EN EL TOTAL DE " << /*iTotalArchivos*/ 0 << " ARCHIVOS RECORRIDOS." << std::endl;
//    std::cout << "TOTAL DE OCURRENCIAS POR SEMANA: " << iTotSem << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;
//    //std::cout << "DURACION TOTAL DE SEMANAS: " << iDuracion << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << par.first << "." << std::endl;
//    //std::cout << "TOTAL DE DIAS: " << iDuracionDías << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << par.first << "." << std::endl;
//    //std::cout << "TOTAL DE HORAS: " << iDuracionHoras << " QUE SE LLEVARA EN DESARROLLO DEL LENGUAJE " << par.first << "." << std::endl; // Muestra el total en horas
//    //std::cout << std::endl;
//
//    std::string sFechaInicial;
//    std::string sFechaFinal;
//    std::string sFechaFinalLunVie;
//
//    //calcularFechaFinal((int)iDuracionDías, sFechaInicial, sFechaFinal, iTotalDias, iTotalDiasInhabiles, sFechaFinalLunVie);
//
//    //if (registrarFechasDeProyecto(lIdProyecto, sNombreProyecto, sLenguajeSQL, iTotalSenObsCheckmarx, iOcurrenciasPorSemanaPorColaborador, iNumeroDeColaboradores, iTotSem,
//    //    iDuracionDías, iDuracionHoras, sFechaInicial, sFechaFinal, iTotalDiasInhabiles, sFechaFinalLunVie, iDataBase))
//    //{
//
//    //}
//
//    return 0;
//}

int CIA::crearConteoPorCoincidencia()
{
    std::ifstream file(R"(C:\temp\intranet\ConteoPorCoincidenciaIntranet.csv)");
    std::ofstream output(R"(C:\temp\intranet\resultadoCoindicencia.csv)");
    std::string line;
    std::map<std::string, int> conteo;

    /// Saltar la primera línea (cabecera)
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::string archivo = line.substr(0, line.find(','));
        conteo[archivo]++;
    }

    // Escribir la cabecera en el archivo CSV
    output << "Ruta archivo,Total\n";

    // Escribir los resultados en el archivo CSV
    for (const auto& par : conteo)
    {
        output << par.first << "," << par.second << '\n';
    }

    std::cout << "Los resultados se han guardado en 'resultadoCoindicencia.csv'.\n";

    return 0;
}

int CIA::crearConteoPorCoincidenciaObsoleto()
{
    std::ifstream file("C:\\temp\\intranet\\ConteoPorObsoletoIntranet.csv");
    std::ofstream output("C:\\temp\\intranet\\resultadoObsoleto.csv");
    std::string line;
    std::map<std::string, int> conteo;

    /// Saltar la primera línea (cabecera)
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::string archivo = line.substr(0, line.find(','));
        conteo[archivo]++;
    }

    // Escribir la cabecera en el archivo CSV
    output << "Ruta archivo,Total\n";

    // Escribir los resultados en el archivo CSV
    for (const auto& par : conteo)
    {
        output << par.first << "," << par.second << '\n';
    }

    std::cout << "Los resultados se han guardado en 'resultadoObsoleto.csv'.\n";

    return 0;
}


// Función para buscar sentencias SQL en un archivo
//void CIA::search_sql_in_file(const std::string& file_path, std::ofstream& csv_file, std::map<std::string, int>& mapSentencias, long lIdProyecto, const int iDataBase)
void CIA::search_sql_in_file(const std::string& file_path, std::map<std::string, int>& mapSentencias, const long lIdProyecto, const int iDataBase)
{
    std::ifstream file(file_path);
    std::string line;
    std::string sCadena;
    int line_number = 0;
    std::wstring wstr; // Convierte a wstring para poder escribir en el archivo CSV

    while (std::getline(file, line))
    {
        line_number++;
        if (std::regex_search(line, matchesSql, patternSql))
        {
            //std::string str(matchesSql[0]);
            //sCadena = file_path + "|" + std::to_string(line_number) + "|" + str + "|";
            //wstr = convertStringToWString(sCadena);

            std::string str(matchesSql[0]);
            // Se verifica si la sentencia SQL encontrada es un SELECT
            // Si es un SELECT, no se registra la sentencia.
            if (str.find("<select") != std::string::npos || str.find("<SELECT") != std::string::npos)
            {
                continue; // No continuar con el registro de la sentencia encontrada
            }

            std::string extension = file_path.substr(file_path.find_last_of(".") + 1);
			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

            //std::cout << "EXTENSION: " << extension << std::endl;
            mapSentencias[extension]++;

            //csv_file << wstr << std::endl;
            //csv_file << file_path << "|" << line_number << "|" << matchesSql[0] << "|" << std::endl;

            registrarSentencias(file_path, line_number, matchesSql[0], lIdProyecto, iDataBase);
            
            //std::cout << "Sentencia SQL encontrada en el archivo " << file_path << ", línea " << line_number << ": " << matchesSql[0] << std::endl;
        }
    }
}

// Función para buscar funciones obsoletas en un archivo
//int CIA::search_deprecated_in_file(const std::string& file_path, std::ofstream& csv_file, std::map<std::string, int> &mapDeprecated, long lIdProyecto, const int iDataBase)
int CIA::search_deprecated_in_file(const std::string& file_path, std::map<std::string, int>& mapDeprecated, const long lIdProyecto, const int iDataBase)
{
    std::ifstream file(file_path);
    std::string line;
    int line_number             = 0;
    int iFileCountDeprecated    = 0;

    while (std::getline(file, line))
    {
        line_number++;
        if (std::regex_search(line, matchesObs, patternObs))
        {

            std::string extension = file_path.substr(file_path.find_last_of(".") + 1);
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

            //std::cout << "EXTENSION: " << extension << std::endl;
            mapDeprecated[extension]++;

            //csv_file << file_path << "|" << line_number << "|" << matchesObs[0] << "|" << std::endl;
            //std::cout << "FUNCION DEPRECADA ENCONTRADA EN EL ARCHIVO " << file_path << ", LINEA " << line_number << ": " << matchesObs[0] << std::endl;
            
            //iFileCountDeprecated++;

            registrarObsoletos(file_path, line_number, matchesObs[0], lIdProyecto, iDataBase);
        }
    }

    return iFileCountDeprecated;
}


void CIA::execute_bito_in_file(const std::string& file_path)
{
    std::ifstream file(file_path);
    std::string line;
    int line_number = 0;

    while (std::getline(file, line))
    {
        line_number++;
        if (std::regex_search(line, matchesSql, patternSql))
        {
            std::cout << "SENTENCIA SQL ENCONTRADA EN EL ARCHIVO " << file_path << ", LINEA " << line_number << ": " << matchesSql[0] << std::endl;
        }
    }
}

// Función para buscar archivos recursivamente en un directorio
int CIA::search_files_Sql_in_directory(const std::filesystem::path& directory, std::map<std::string, int>& mapSentencias, const long lIdProyecto, const int iDataBase)
{
    if (!std::filesystem::exists(directory))
    {
        std::cerr << "EL DIRECTORIO NO EXISTE: " << directory << std::endl;
        return 0;
    }

    std::string strStemBito;

    int iFileCount      = 0;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".php" ||
            entry.is_regular_file() && entry.path().extension() == ".cpp" ||
            entry.is_regular_file() && entry.path().extension() == ".ts" ||
            entry.is_regular_file() && entry.path().extension() == ".js" ||
            entry.is_regular_file() && entry.path().extension() == ".dart" ||
            entry.is_regular_file() && entry.path().extension() == ".cs" ||
            entry.is_regular_file() && entry.path().extension() == ".java" ||
            entry.is_regular_file() && entry.path().extension() == ".vb" ||
            entry.is_regular_file() && entry.path().extension() == ".go" ||
            entry.is_regular_file() && entry.path().extension() == ".py")
        {
            std::string fileName = entry.path().filename().string();
            if (fileName.find("jquery") != std::string::npos 
                || fileName.find(".min.js") != std::string::npos
                || fileName.find("bootstrap") != std::string::npos )
            {
                continue; // Skip the file if it contains 'jquery' or '.min.js' in its name
            }

            //search_sql_in_file(entry.path().string(), csv_file, mapSentencias, lIdProyecto, iDataBase);
            search_sql_in_file(entry.path().string(), mapSentencias, lIdProyecto, iDataBase);

            iFileCount++;
        }
    }

    return iFileCount;
}

//int CIA::search_files_php_deprecated_in_directory(const std::filesystem::path& directory, std::ofstream& csv_file)
//{
//    if (!std::filesystem::exists(directory))
//    {
//        std::cerr << "EL DIRECTORIO NO EXISTE: " << directory << std::endl;
//        return 0;
//    }
//
//    std::map<std::string, int> mapDeprecated;
//
//    std::string strStemBito;
//
//    int php_file_count = 0;
//    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
//    {
//        if (entry.is_regular_file() && entry.path().extension() == ".php")
//        {
//            search_deprecated_in_file(entry.path().string(), csv_file, mapDeprecated);
//
//            php_file_count++;
//        }
//    }
//
//    return php_file_count;
//}

int CIA::search_files_deprecated_in_directory(const std::filesystem::path& directory, std::map<std::string, int>& mapDeprecated, const long lIdProyecto, const int iDataBase)
{
    if (!std::filesystem::exists(directory))
    {
        std::cerr << "EL DIRECTORIO NO EXISTE: " << directory << std::endl;
        return 0;
    }

    std::string strStemBito;

    int iFileCount = 0;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".php" ||
            entry.is_regular_file() && entry.path().extension() == ".cpp" ||
            entry.is_regular_file() && entry.path().extension() == ".ts"  ||
            entry.is_regular_file() && entry.path().extension() == ".js"  ||
            entry.is_regular_file() && entry.path().extension() == ".dart" ||
            entry.is_regular_file() && entry.path().extension() == ".cs"   ||
            entry.is_regular_file() && entry.path().extension() == ".java" ||
            entry.is_regular_file() && entry.path().extension() == ".vb"   ||
            entry.is_regular_file() && entry.path().extension() == ".go"   ||
            entry.is_regular_file() && entry.path().extension() == ".py" )
        {
            std::string fileName = entry.path().filename().string();
            if (fileName.find("jquery") != std::string::npos
                || fileName.find(".min.js") != std::string::npos
                || fileName.find("bootstrap") != std::string::npos)
            {
                continue; // Skip the file if it contains 'jquery' or '.min.js' in its name
            }

            //search_deprecated_in_file(entry.path().string(), csv_file, mapDeprecated, lIdProyecto, iDataBase);
            search_deprecated_in_file(entry.path().string(), mapDeprecated, lIdProyecto, iDataBase);
            iFileCount++;
        }
    }

    return iFileCount;
}


//int CIA::contarArchivosEnVector(const std::filesystem::path& directory, const std::vector<std::string>& vcLenguajes)
//{
//    int iFileCount = 0;
//
//    if (!std::filesystem::exists(directory))
//    {
//        std::cerr << "EL DIRECTORIO NO EXISTE: " << directory << std::endl;
//        return 0;
//    }
//
//    std::string strStemBito;
//
//    
//    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
//    {
//        //std::cout << "El directorio es : " << directory << std::endl;
//        //std::cout << entry.path().extension() << std::endl;
//
//        if (entry.is_regular_file() && entry.path().extension() == sLenguaje)
//        {
//            iFileCount++;
//        }
//    }
//
//    return iFileCount;
//}


int CIA::contarArchivosEnVector(const std::filesystem::path& directory, const std::vector<std::string>& vcLenguajes)
{
    int iFileCount = 0;

    if (!std::filesystem::exists(directory))
    {
        std::cerr << "EL DIRECTORIO NO EXISTE: " << directory << std::endl;
        return 0;
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        std::string fileExt = entry.path().extension().string();

        //std::cout << "EXTENSION: " << fileExt << " ext [ " << entry.path().extension() << " ] " << std::endl;

        // Elimina el punto de la extensión
        fileExt.erase(0, 1);

        // Convertir a mayúsculas
        std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::toupper);

        if ((entry.is_regular_file() && fileExt == "PHP") ||
            (entry.is_regular_file() && fileExt == "CPP") ||
            (entry.is_regular_file() && fileExt == "TS") ||
            (entry.is_regular_file() && fileExt == "JS") ||
            (entry.is_regular_file() && fileExt == "DART") ||
            (entry.is_regular_file() && fileExt == "CS") ||
            (entry.is_regular_file() && fileExt == "JAVA") ||
            (entry.is_regular_file() && fileExt == "VB") ||
            (entry.is_regular_file() && fileExt == "GO") ||
            (entry.is_regular_file() && fileExt == "PY"))
        {
            //std::string fileExtension = entry.path().extension().string();
            //std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), [](unsigned char c) { return std::tolower(c); });

            if (fileExt.compare("PY") == 0 )
            {
                fileExt = "PYTHON";
            }

            if (std::find(vcLenguajes.begin(), vcLenguajes.end(), fileExt) != vcLenguajes.end())
            {
                iFileCount++;
            }
        }
    }

    return iFileCount;
}
int CIA::contarArchivos(const std::filesystem::path& directory, const std::string &sLenguaje)
{
    if (!std::filesystem::exists(directory))
    {
        std::cerr << "EL DIRECTORIO NO EXISTE: " << directory << std::endl;
        return 0;
    }

    std::string strStemBito;

    int php_file_count = 0;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        //std::cout << "El directorio es : " << directory << std::endl;
        //std::cout << entry.path().extension() << std::endl;

        if (entry.is_regular_file() && entry.path().extension() == sLenguaje)
        {
            php_file_count++;
        }
    }

    return php_file_count;
}

double CIA::calcularFechaFinProyecto(int& iTotalOcurrencias, int& iOcurrenciasPorSemanaPorColaborador, int& iNumeroDeColaboradores)
{
    // Ajustar las ocurrencias por semana para tener en cuenta solo 5 días hábiles
    int iTotalOcurrenciasPorSemana = (iOcurrenciasPorSemanaPorColaborador * iNumeroDeColaboradores * 5) / 7;
    double dSemanasNecesarias = static_cast<double>(iTotalOcurrencias) / iTotalOcurrenciasPorSemana;

    // Redondear hacia arriba
    dSemanasNecesarias = std::ceil(dSemanasNecesarias);

    double dDiasNecesarios = dSemanasNecesarias * 7;
    double dMesesNecesarios = dSemanasNecesarias / 4.34524;
    double dAniosNecesarios = dSemanasNecesarias / 52.1775;

    std::cout << "SE NECESITARAN APROXIMADAMENTE " << dSemanasNecesarias << " SEMANAS, O " << dDiasNecesarios << " DIAS, O " << dMesesNecesarios << " MESES, O " << dAniosNecesarios << " AÑOS PARA ATENDER LAS " << iTotalOcurrencias << " OCURRENCIAS.\n";
    std::cout << "¡GRACIAS POR USAR ESTE PROGRAMA! ¡HASTA LA PROXIMA!\n";

    return dSemanasNecesarias;
}

int CIA::quitarComentariosBito(std::string sPathFile, std::string & sPathFileBitoTxt)
{
    //Ruta y archivo que llegó por parámetros. "C:\temp\marcarcomentario\prueba_ws.php"
    std::string sFileArg = sPathFile;
    //std::cout << "File Arg: " << sFileArg << "\n";

    //Validar si existe el archivo bito.
    if (!std::filesystem::exists(sFileArg))
    {
        std::cout << "El archivo " << sFileArg << " no existe.\n";
        return 1;
    }

    std::filesystem::path pathFile(sFileArg);

    //Ruta
    std::string sPath = pathFile.parent_path().string(); //"C:\temp\marcarcomentario"
    //std::cout << "Path: " << sPath << "\n";

    //Nombre del archivo
    std::string sArc = pathFile.filename().string(); //"prueba_ws.php"
    //std::cout << "File: " << sArc << "\n";

    //Extensión
    std::string sExt = pathFile.extension().string(); //".php"
    //std::cout << "Ext: " << sExt << "\n";

    //Nombre sin extensión
    std::string sName = pathFile.stem().string(); //"prueba_ws"
    //std::cout << "Nombre: " << sName << "\n";

    // Se arma el nuevo archivo y se concatena con la ruta.
    std::string sNewName = sArc + ".ori";    //"prueba_ws.php.ori"
    std::string sPathNewName = sPath + "\\" + sNewName;  //"C:\temp\marcarcomentario\ori_prueba_ws.php"

    std::filesystem::rename(sFileArg, sPathNewName); // "C:\temp\marcarcomentario\prueba_ws.php" to "C:\temp\marcarcomentario\ori_prueba_ws.php"

    //Se arma el archivo bito.
    std::string sPathFileBito = sPath + "\\" + sName + ".bito"; //"C:\temp\marcarcomentario\prueba_ws.bito"

    //Validar si existe el archivo bito.
    if (!std::filesystem::exists(sPathFileBito))
    {
        std::cout << "El archivo " << sPathFileBito << " no existe.\n";
        return 1;
    }

    //Se arma el archivo bito.
    //std::string sPathFileBitoTxt = sPath + "\\" + sName + ".bito.txt";    //"C:\temp\marcarcomentario\prueba_ws.php"
    sPathFileBitoTxt = sPath + "\\" + sName + ".bito.txt";    //"C:\temp\marcarcomentario\prueba_ws.php"

    std::ifstream input(sPathFileBito);
    std::ofstream output_php(sFileArg);
    std::ofstream output_txt(sPathFileBitoTxt);

    bool bCopy = false;
    bool bEnd = false;

    for (std::string line; std::getline(input, line); ) 
    {
        if (line.find("```PHP") != std::string::npos) 
        {
            bCopy = true;
            continue;
        }

        if (line.find("```JAVASCRIPT") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```TYPESCRIPT") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```CPP") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```CSHARP") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```JAVA") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```GOLANG") != std::string::npos)
        {
            bCopy = true;
            continue;
        }


        if (line.find("```PYTHON") != std::string::npos)
        {
			bCopy = true;
			continue;
		}

        if (line.find("```DART") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```VISUALBASIC") != std::string::npos)
        {
            bCopy = true;
            continue;
        }

        if (line.find("```") != std::string::npos) 
        {
            bEnd = !bEnd;
            continue;
        }

        if (bCopy && !bEnd) 
        {
            output_php << line << '\n';
        }
        else 
        {
            output_txt << line << '\n';
        }
    }

    input.close();
    output_php.close();
    output_txt.close();

    return 0;
}

bool CIA::validarArchivoBito(const std::string& sRutaArchivo, const std::string& sRutaArchivoCSV)
{
    std::ifstream archivo(sRutaArchivo);
    std::string linea;
    bool encontrado = false;

    if (archivo.is_open()) 
    {
        while (getline(archivo, linea)) 
        {
            if (linea.find("```PHP") != std::string::npos)
            {
                encontrado = true;
                break;
            }

            if (linea.find("```PYTHON") != std::string::npos) 
            {
                encontrado = true;
                break;
            }

            if (linea.find("```JAVASCRIPT") != std::string::npos)
            {
                encontrado = true;
                break;
            }

            if (linea.find("```JAVA") != std::string::npos)
            {
                encontrado = true;
                break;
            }

            if (linea.find("```GO") != std::string::npos)
            {
                encontrado = true;
                break;
            }

            if (linea.find("```TYPESCRIPT") != std::string::npos)
            {
                encontrado = true;
                break;
            }

            if (linea.find("```CSHARP") != std::string::npos)
            {
                encontrado = true;
                break;
            }

            if (linea.find("```CPP") != std::string::npos)
            {
				encontrado = true;
				break;
			}
        }
        archivo.close();
    }

    if (encontrado == false) 
    {
        // Crear un archivo CSV con la ruta del archivo que no se pudo convertir pero no elimines el archivo original.
        std::ofstream csv(sRutaArchivoCSV, std::ios::app);
        if (csv.is_open())
        {
            csv << "Ruta Archivo Sin Convertir|\n";
            csv << sRutaArchivo << "\n";
            csv.close();
        }
    }

    return encontrado;
}

void CIA::createCSV(const std::string& path, const std::string& filename) 
{
    // Obtén la fecha y hora actuales
    std::time_t now = std::time(0);
    std::tm localTime;
    localtime_s(&localTime, &now);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);

    // Crea un nuevo archivo CSV en la ruta especificada
    std::ofstream file(path + "lintphp.csv", std::ios::app);
    file << filename << "|" << timeStr << std::endl;
}


int CIA::lintPHPFile(const std::string& sNombreArchivo, std::string & sContenidoTxtLint)
{
    int  iResultadoLint     = -1;
    char cStemLint[512]     = { 0 };
    char cFileLintPhp[512]  = { 0 };
    std::stringstream       buffer_file;

    //Pasamos por el linter el archivo original de PHP
    sprintf_s(cStemLint, sizeof(cStemLint), "%s.lin", sNombreArchivo.c_str());

    //Ejecutar php -l para validar la sintaxis del archivo.    
    sprintf_s(cFileLintPhp, sizeof(cFileLintPhp), "php -l %s > %s", sNombreArchivo.c_str(), cStemLint);

    iResultadoLint = system(cFileLintPhp);

    if (iResultadoLint == 0)
    {
        // Leer el archivo de salida y obtener el resultado.
        std::ifstream input_file(cStemLint);
        if (input_file)
        {
            buffer_file << input_file.rdbuf();
            input_file.close();

            sContenidoTxtLint = buffer_file.str();
            // Elimina todos los caracteres de salto de línea
            sContenidoTxtLint.erase(std::remove(sContenidoTxtLint.begin(), sContenidoTxtLint.end(), '\n'), sContenidoTxtLint.end());
        }
        else
        {
            iResultadoLint = -1;
            std::cerr << "No se pudo abrir el archivo: " << cStemLint << std::endl;
        }
    }
    else
    {
		std::cout << "Error en el archivo: " << sNombreArchivo << std::endl;
		iResultadoLint = -1;
	}

    return iResultadoLint;
}

#include <chrono>

std::string CIA::obtenerFechaArchivos(std::string sNombreArchivo)
{
    std::string sFechaArchivoPrompt = "";
    //char cBuffer[80] = { 0 };

    //std::filesystem::path pathFile(sNombreArchivo);

    //if (std::filesystem::exists(pathFile))
    //{
    //    auto lastWriteTime = std::filesystem::last_write_time(pathFile);
    //    auto lastWriteTimeTm = std::chrono::system_clock::to_time_t(lastWriteTime);
    //    std::tm lastWriteTimeStruct = {};

    //    if (localtime_s(&lastWriteTimeStruct, &lastWriteTimeTm) == 0)
    //    {
    //        std::strftime(cBuffer, 80, "%Y-%m-%d %H:%M:%S", &lastWriteTimeStruct);
    //        sFechaArchivoPrompt = cBuffer;
    //    }
    //}

    // Ruta del archivo que deseas consultar
    //std::filesystem::path filePath(sNombreArchivo);

    //// Obtiene la hora de creación del archivo
    //try 
    //{
    //    auto creationTime = std::filesystem::last_write_time(filePath);

    //    // Convierte el tiempo en un formato legible
    //    std::time_t creationTimeT = std::chrono::system_clock::to_time_t(std::chrono::time_point_cast<std::chrono::system_clock::duration>(creationTime));
    //    //std::time_t creationTimeT = decltype(creationTime)::clock::to_time_t(creationTime);
    //    std::tm creationTimeTM;
    //    localtime_s(&creationTimeTM, &creationTimeT);

    //    // Imprime la fecha de creación
    //    std::cout << "Fecha de creación del archivo: "
    //        << creationTimeTM.tm_mday << "/" << (creationTimeTM.tm_mon + 1) << "/"
    //        << (creationTimeTM.tm_year + 1900) << std::endl;
    //}
    //catch (const std::filesystem::filesystem_error& e)
    //{
    //    std::cerr << "Error al obtener la hora de creación: " << e.what() << std::endl;
    //}

    return sFechaArchivoPrompt;
}

std::string CIA::generarArchivoBito(const std::string& sNombreArchivo, const std::string& sLenguaje)
{
    char cPathFilePrompt[300]               = { 0 };
    char cFileBito[600]                     = { 0 };
    
    std::string sNombrePathArchivo          = sNombreArchivo;
    std::string sNombreArchivoSinExtension  = getFileNameWithoutExtension(sNombreArchivo);
    std::string sObtenerRutaArchivo         = sNombrePathArchivo.substr(0, sNombrePathArchivo.find_last_of("\\"));
    std::string sNombreArchivoBito          = sNombreArchivoSinExtension + ".bito";

    //Arturo: Se arma el archivo bito.
    if (sLenguaje.compare("php") == 0 || sLenguaje.compare("PHP") == 0) // Php
    {
        sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationPHP.pmt");
    }
    else if (sLenguaje.compare("js") == 0 || sLenguaje.compare("JS") == 0 ) // Javascript
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationJS.pmt");
	}
    else if (sLenguaje.compare("ts") == 0 || sLenguaje.compare("TS") == 0) //TypeScript
	{
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationTS.pmt");
	}
    else if (sLenguaje.compare("java") == 0 || sLenguaje.compare("JAVA") == 0) // Java
    {
        sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationJAVA.pmt");
    }
    else if (sLenguaje.compare("c") == 0 || sLenguaje.compare("C") == 0 ||
             sLenguaje.compare("h") == 0 || sLenguaje.compare("H") == 0) //C o H
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationC.pmt");
	}
    else if (sLenguaje.compare("cpp") == 0 || sLenguaje.compare("CPP") == 0 ||
             sLenguaje.compare("hpp") == 0 || sLenguaje.compare("HPP") == 0) //C++ o H++
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationCPP.pmt");
	}
    else if (sLenguaje.compare("cs") == 0 || sLenguaje.compare("CS") == 0) //C#
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationCS.pmt");
	}
    else if (sLenguaje.compare("vb")  == 0 || sLenguaje.compare("VB")  == 0 || //Visual Basic .NET
             sLenguaje.compare("bas") == 0 || sLenguaje.compare("BAS") == 0)   //Visual Basic 6
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationVB.pmt");
	}
    else if (sLenguaje.compare("py") == 0 || sLenguaje.compare("PY") == 0) //Python
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationPY.pmt");
	}
    else if (sLenguaje.compare("rb") == 0 || sLenguaje.compare("RB") == 0) //Ruby
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationRB.pmt");
	}
    else if (sLenguaje.compare("go") == 0 || sLenguaje.compare("GO") == 0) //Go
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationGO.pmt");
	}
    else if (sLenguaje.compare("pl") == 0 || sLenguaje.compare("PL") == 0) //Perl
    {
        sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationPL.pmt");
    }
    else if (sLenguaje.compare("swift") == 0 || sLenguaje.compare("SWIFT") == 0) //Swift
    {
        sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationSWIFT.pmt");
    }
    else if (sLenguaje.compare("dart") == 0 || sLenguaje.compare("DART") == 0) //Dart
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationDART.pmt");
	}
    else if (sLenguaje.compare("vue") == 0 || sLenguaje.compare("VUE") == 0) // VUE
    {
	    sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationVUE.pmt");
	}
    else if (sLenguaje.compare("jsx") == 0 || sLenguaje.compare("JSX") == 0) // React
    {
		sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationREACT.pmt");
	}
    else
    {
		std::cout << "El lenguaje " << sLenguaje << " no está soportado." << std::endl;
		return "";
	}
 //   else if (sLenguaje.compare("html") || sLenguaje.compare("HTML"))
 //   {
	//	sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\HTML.pmt");
	//}
 //   else if (sLenguaje.compare("css") || sLenguaje.compare("CSS"))
 //   {
	//	sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\CSS.pmt");
	//}
 //   else if (sLenguaje.compare("xml") || sLenguaje.compare("XML"))
 //   {
	//	sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\XML.pmt");
	//}
 //   else if (sLenguaje.compare("json") || sLenguaje.compare("JSON"))
 //   {
	//	sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\JSON.pmt");
	//}
 //   else if (sLenguaje.compare("sql") || sLenguaje.compare("SQL"))
 //   {
	//	sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\SQL.pmt");
	//}
	//else if (sLenguaje.compare("yaml") || sLenguaje.compare("YAML"))
 //   {
 //       sprintf_s(cPathFilePrompt, sizeof(cPathFilePrompt), " -p C:\\sys\\progs\\parse\\Bito\\SQL.pmt");
 //   }

    std::cout << "Procesando archivo: " << sNombreArchivo << std::endl;

    memset(cFileBito, ' ', sizeof(cFileBito));
    strcpy_s(cFileBito, "type ");
    strcat_s(cFileBito, sNombrePathArchivo.c_str());
    strcat_s(cFileBito, " | bito.exe");
    strcat_s(cFileBito, cPathFilePrompt);
    strcat_s(cFileBito, " > ");
    strcat_s(cFileBito, sNombreArchivoBito.c_str());

    return std::string(cFileBito);
}

int CIA::validarExisteBito(const std::string& sRuta) 
{
    std::string sRutaCompletaBito = sRuta + "\\IA_bito.csv";
    std::ifstream archivoEntrada;
    std::string sRespuesta;

    try
    {
        archivoEntrada.open(sRutaCompletaBito);

        if (archivoEntrada.is_open())
        {
            std::cout << "El archivo [IA_bito.csv] ya existe." << std::endl;
            std::cout << "Deseas borrarlo? (Si/No) : ";
            std::cin >> sRespuesta;

            archivoEntrada.close();

            if (sRespuesta == "Si" || sRespuesta == "si")
            {
                if (remove(sRutaCompletaBito.c_str()) != 0)
                {
                    std::cerr << "Error al eliminar el archivo.\n";
                    return 0;
                }
                else
                {
                    std::cout << "El archivo 'IA_bito.csv' se ha eliminado correctamente.\n";
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Excepción capturada: " << e.what() << '\n';
        return 0;
    }

    return 1;
}

bool CIA::validarExisteEmpleadoTB(long &lNumColaborador, long& lRespuesta, const int iDataBase)
{
	bool bReturn        = false;
	lRespuesta          = -1;
	std::string  sSQL   = STRING_EMPTY;
	std::string  sResp  = STRING_EMPTY;

	std::vector<ES_Records> vcstRecords;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp     = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort   = STRING_EMPTY;
    std::string sUser   = STRING_EMPTY;
    std::string sPass   = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    //if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))	
	{
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
		bReturn = false;
	}
	else
	{
		bReturn = false;

		sSQL.append(objUtils.stringFormat("SELECT fun_validar_si_existe_colaborador( '%ld'::BIGINT );", lNumColaborador));

		if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
		{
			std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
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
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);                    
					lRespuesta = std::stol(sResp);
				}
			}
		}

		sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
	}

	return bReturn;
}

bool CIA::registrarSentencias(std::string sArchivo, int iLinea, std::string sSentencia, const long lIdProyecto, const int iDataBase)
{
    bool bReturn        = false;
    std::string sSQL    = STRING_EMPTY;
    std::string sResp   = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "EXCEPCION CAPTURADA: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;

        std::string sSent = objPSQL.C_PostgreSQL::sanitize(sSentencia);
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_sentencias( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%.299s'::VARCHAR, '%d'::INTEGER, '%.999s'::VARCHAR );",
            lColaborador, lIdProyecto, sNomProyecto.c_str(), sArchivo.c_str(), iLinea, sSent.c_str()));
        //std::cout << "SQL: " << sSQL << std::endl;

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "EXCEPCION CAPTURADA: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            std::cout << "*";
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
                    //iRespuesta = _ttoi(csResp);
                    bReturn = true;
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

bool CIA::registrarObsoletos(std::string sArchivo, int iLinea, std::string sObsoleto, const long lIdProyecto, const int iDataBase)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()) )
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_obsoletos( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%.299s'::VARCHAR, '%d'::INTEGER, '%.999s'::VARCHAR );",
            lColaborador, lIdProyecto, sNomProyecto.c_str(), sArchivo.c_str(), iLinea, sObsoleto.c_str()));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
                    //iRespuesta = _ttoi(csResp);
                    bReturn = true;
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

std::string CIA::obtenerTokenDB(const long lEmpleado, std::string sToken, std::string& sTokenDB, std::string& sExpiraDB, const int iDataBase)
{
    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
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

                    for (size_t k = 0; k < sToken.size(); ++k)
                    {
                        size_t pos = acentos.find(sToken[k]);
                        if (pos != std::string::npos) 
                        {
                            sToken[k] = sin_acentos[pos];
                        }
                    }

                    char* next_token1 = NULL;
                    char* prtTok = NULL;
                    char cTok[10000] = { 0 };

                    memcpy_s(cTok, sizeof(cTok), sToken.c_str(), sToken.length());
                    prtTok = strtok_s(cTok, ",", &next_token1);

                    //std::cout << "Token " << sToken << std::endl;

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

//out1 << "\"1\",\"" << projectName << "\",\"" << severityCount["High"] << "\",\"" << severityCount["Medium"] << "\",\"" << severityCount["Low"] << "\",\"" << sFecha << "\"\n";
bool CIA::registrarTotalesCheckmarx(const long lIdProyecto, const std::string sProjectName, int iHigh, int iMedium, int iLow, const int iDataBase)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;
    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_totales_checkmarx( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER );",
            lColaborador, lIdProyecto, sProjectName.c_str(), iHigh, iMedium, iLow));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
                    //iRespuesta = _ttoi(csResp);
                    bReturn = true;
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

bool CIA::registrarItemsCheckmarx(const long lIdProyecto, const std::string sProjectName, int iId, std::string dDetectionDate, std::string sDirectLink, std::string sQueryName,
    std::string sSourceFolder, std::string sSourceFilename, std::string sSourceLine, std::string sSourceObject, std::string sDestinationFolder, 
    std::string sDestinationFilename, std::string sDestinationLine, std::string sDestinationObject, std::string sResultState, std::string sSeverity,
    std::string sResultSeverity, const int iDataBase)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_items_checkmarx( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%d'::INTEGER, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR, '%s'::VARCHAR );",
            lColaborador, lIdProyecto, sProjectName.c_str(), iId, dDetectionDate.c_str(), sDirectLink.c_str(), sQueryName.c_str(),
            sSourceFolder.c_str(), sSourceFilename.c_str(), sSourceLine.c_str(), sSourceObject.c_str(), sDestinationFolder.c_str(),
            sDestinationFilename.c_str(), sDestinationLine.c_str(), sDestinationObject.c_str(), sResultState.c_str(), sSeverity.c_str(),
            sResultSeverity.c_str() ));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
                    //iRespuesta = _ttoi(csResp);
                    bReturn = true;
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

//LENGUAJE | OCURRENCIAS | X_SEMANA | CANT_COLAB | TOT_SEM | TOT_DIAS | TOT_HORAS | FECHA_INI | FECHA_FIN
bool CIA::registrarFechasDeProyecto(const long lIdProyecto, const std::string sProjectName, std::string sLanguageName, 
    int iOcurrencias, int iXSemana, int iCantColab, int iTotSem, int iTotDias, int iTotHoras, std::string sFechaIni, 
    std::string sFechaFin, int iDiasLunVie, std::string sFechaLunVie, const int iDataBase)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_fecha_proyecto( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%s'::VARCHAR, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER, '%s'::VARCHAR, '%s'::VARCHAR, '%d'::INTEGER, '%s'::VARCHAR );",
            lColaborador, lIdProyecto, sProjectName.c_str(), sLanguageName.c_str(), iOcurrencias, iXSemana, iCantColab, iTotSem, iTotDias, iTotHoras, sFechaIni.c_str(), sFechaFin.c_str(), iDiasLunVie, sFechaLunVie.c_str() ));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
                    //iRespuesta = _ttoi(csResp);
                    bReturn = true;
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

bool CIA::registrarTotalesProyectos(const long lIdProyecto, const std::string sProjectName, std::string sLenguaje, const int iArchivos, const int iLineasBlanco, const int iComentarios, const int iLineasCodigo, const int iDataBase)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;
    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_totales_proyecto( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%s'::VARCHAR, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER, '%d'::INTEGER );",
            lColaborador, lIdProyecto, sProjectName.c_str(), sLenguaje.c_str(), iArchivos, iLineasBlanco, iComentarios, iLineasCodigo));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
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
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

bool CIA::registrarControlDeProyectos(const long lIdProyecto, const std::string sProjectName, const int iFlagConIA, const int iDataBase)
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;
    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_control_proyectos( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::VARCHAR, '%d'::INTEGER );",
            lColaborador, lIdProyecto, sProjectName.c_str(), iFlagConIA));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
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
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}

bool CIA::generarArchivosPrompt(const std::string sPrompt, const std::string sLenguaje)
{
    bool bReturn = false;
    ofstream archivo;

    if (sLenguaje.compare("php") == 0 || sLenguaje.compare("PHP") == 0)
    {
       archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationPHP.pmt");
       archivo << sPrompt;
       archivo.close();
       bReturn = true;
	}
	else if (sLenguaje.compare("js") == 0 || sLenguaje.compare("JS") == 0 || sLenguaje.compare("JAVASCRIPT") == 0)
	{
		archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationJS.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
	}
	else if (sLenguaje.compare("ts") == 0 || sLenguaje.compare("TS") == 0 || sLenguaje.compare("TYPESCRIPT") == 0)
	{
		archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationTS.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
	}
	else if (sLenguaje.compare("java") == 0 || sLenguaje.compare("JAVA") == 0)
	{
		archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationJAVA.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
	}
	else if (sLenguaje.compare("c") == 0 || sLenguaje.compare("C") == 0 ||
        	 sLenguaje.compare("h") == 0 || sLenguaje.compare("H") == 0)
	{
		archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationC.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
	}
	else if (sLenguaje.compare("cpp") == 0 || sLenguaje.compare("CPP") == 0 || 
             sLenguaje.compare("C++") == 0 || sLenguaje.compare("c++") == 0 ||
             sLenguaje.compare("hpp") == 0 || sLenguaje.compare("HPP") == 0)
	{
		archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationCPP.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
	}
	else if (sLenguaje.compare("cs") == 0 || sLenguaje.compare("CS") == 0)
	{
		archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationCS.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
	}
	else if (sLenguaje.compare("vb") == 0 || sLenguaje.compare("VB") == 0 ||
        	 sLenguaje.compare("bas") == 0 || sLenguaje.compare("BAS") == 0)
	{
        archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationVB.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
    }
    else if (sLenguaje.compare("py") == 0 || sLenguaje.compare("PY") == 0 ||
             sLenguaje.compare("pyw") == 0 || sLenguaje.compare("PYW") == 0)
    {
        archivo.open("C:\\sys\\progs\\parse\\Bito\\CodeRefactoringAndOptimizationPY.pmt");
        archivo << sPrompt;
        archivo.close();
        bReturn = true;
    }

    return bReturn;
}

// Función para desencriptar los datos
std::string CIA::decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv)
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

bool CIA::getDataFileINI(std::string &decrypted_ipname, std::string &decrypted_dbname, std::string &decrypted_dbport, std::string &decrypted_dbuser,
    std::string &decrypted_dbpass, const int iDataBase)
{
    // Leer los datos encriptados del archivo rvia.ini
    std::string line                    = STRING_EMPTY;
    std::string encrypted_ipname_read   = STRING_EMPTY;
    std::string encrypted_dbname_read   = STRING_EMPTY;
    std::string encrypted_dbport_read   = STRING_EMPTY;
    std::string encrypted_dbuser_read   = STRING_EMPTY;
    std::string encrypted_dbpass_read   = STRING_EMPTY;
    std::string sFileINI                = STRING_EMPTY;

    // iDataBase = 1 -> Producción
    // iDataBase = 2 -> Desarrollo
    if (iDataBase == 1)
    {
        sFileINI = "C:\\sys\\progs\\parse\\prorvia.ini";
    }
    else if (iDataBase == 2)
    {
        sFileINI = "C:\\sys\\progs\\parse\\devrvia.ini";
    }
    else
    {
        std::cerr << "No se pudo obtener los datos de conexión." << std::endl;
		return false;
    }

    //validar si existe el archivo.
    std::ifstream in(sFileINI);
    if (!in)
    {
		std::cerr << "NO SE PUDIERON OBTENER LOS DATOS DE CONEXION." << std::endl;
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
    
    // iDataBase = 1 -> Producción
    // iDataBase = 2 -> Desarrollo
    //// Si es producción, se elimina el último caracter
    //if (iDataBase == 1)
    //{
    //    decrypted_dbname = decrypted_dbname.substr(0, decrypted_dbname.length() - 1);
    //}

    decrypted_dbport = decrypt(encrypted_dbport_read, key, iv);
    decrypted_dbuser = decrypt(encrypted_dbuser_read, key, iv);
    decrypted_dbpass = decrypt(encrypted_dbpass_read, key, iv);

    return true;
}

// Función para dividir una línea en tokens
std::vector<std::string> CIA::split(const std::string& s) 
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    bool inQuotes = false;

    for (char c : s) {
        if (c == '\"') {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes) {
            tokens.push_back(token);
            token = "";
        }
        else {
            token += c;
        }
    }
    tokens.push_back(token); // Añadir el último token

    return tokens;
}

std::string CIA::getFilenameSinCheckmarx(const std::string& filePath)
{
    std::filesystem::path path(filePath);
    return path.stem().string();
}

bool CIA::getDataFromCheckmarx(const long lIdProyecto, std::string sFileX, int &iHigh, int &iMedium, int &iLow, int &iDataBase)
{
    if (!std::filesystem::exists(sFileX))
    {
        std::cout << "El archivo " << sFileX << " no existe.\n";
        return false;
    }

    std::string filePath = sFileX; // "C:\\Temp\\Bito\\checkmarx_cobrosproveedorintranet.csv";
    
    //Obtener la ruta del archivo.
    std::string sRutaFileCheckmarx = filePath.substr(0, filePath.find_last_of("\\"));

    //Obtener el nombre del archivo sin extensión.
    std::string sProjectName = getFilenameSinCheckmarx(filePath);
    sProjectName.erase(0, 10); // Remove "checkmarx_"

    //std::cout << "File name without extension: " << sProjectName << std::endl;

    std::ifstream file(filePath);
    std::string line;
    std::getline(file, line); // Leer la primera línea (cabecera)

    std::map<std::string, int> severityCount;
    std::vector<std::vector<std::string>> items;
    std::string sFecha;

    while (std::getline(file, line))
    {
        auto tokens = split(line);
        sFecha = tokens[1]; // Fecha de detección
        severityCount[tokens[14]]++; // Contar severidades
        //Eliminar las comillas dobles de los campos del tokens[7] y guardar en otro archivo con el nombre de proyecto_items.csv y repetando la cabecera original.
        // Eliminar las comillas dobles de los campos del tokens[7]
        std::string field7 = tokens[7];
        field7.erase(std::remove(field7.begin(), field7.end(), '\"'), field7.end());
        tokens[7] = field7;
        items.push_back(tokens); // Guardar los items
    }

    // Generar el archivo proyecto_cabecera.csv
    std::string fileDest = sRutaFileCheckmarx + "\\checkmarx_" + sProjectName + "_tot.csv";
    std::ofstream out1(fileDest);
    out1 << "\"ID Proyecto\",\"Nombre Proyecto\",\"High\",\"Medium\",\"Low\",\"Detection Date\"\n";
    out1 << "\"1\",\"" << sProjectName << "\",\"" << severityCount["High"] << "\",\"" << severityCount["Medium"] << "\",\"" << severityCount["Low"] << "\",\"" << sFecha << "\"\n";
    // Cerrar el archivo
    out1.close();
    //Asignar los valores a las variables de salida.
    iLow = severityCount["Low"];
    iMedium = severityCount["Medium"];
    iHigh = severityCount["High"];

    if (registrarTotalesCheckmarx(lIdProyecto, sProjectName, iHigh, iMedium, iLow, iDataBase))
    {
		std::cout << "Se registraron los totales de Checkmarx correctamente." << std::endl;
	}
    else
    {
		std::cerr << "No se pudieron registrar los totales de Checkmarx." << std::endl;
        return false;
	}

    // Guardar en otro archivo con el nombre de proyecto_items.csv y respetando la cabecera original
    std::string fileDest2 = sRutaFileCheckmarx + "\\checkmarx_" + sProjectName + "_items.csv";
    std::ofstream out2(fileDest2, std::ios::app);
    if (out2.tellp() == 0)
    {
        out2 << "\"Project\",\"Id\",\"Detection Date\",\"Direct Link\",\"Query Name\",\"Source Folder\",\"Source Filename\",\"Source Line\",\"Source Object\",\"Destination Folder\",\"Destination Filename\",\"Destination Line\",\"Destination Object\",\"Result State\",\"Severity\",\"Result Severity\",\n";
    }

    setColor(7); // Blanco
    std::cout << "Espere, se registraran los items de Checkmarx..." << std::endl;
    for (const auto& item : items)
    {
        setColor(2);
        std::cout << ".";

        setColor(7); // Blanco
        if (!registrarItemsCheckmarx(lIdProyecto, sProjectName, std::stoi(item[0]), item[1], item[2], item[3], item[4], item[5], item[6], item[7], 
            item[8], item[9], item[10], item[11], item[12], item[13], item[14], iDataBase))
        {
            std::cerr << "No se pudieron registrar los items de Checkmarx." << std::endl;
            return false;
        }
    }
    // Cerrar el archivo
    out2.close();

    std::cout << std::endl;

    return true;
}


std::string CIA::obtenerPrompt(const std::string sNomCliente, std::string sLenguaje, std::string sModelo, const int iDataBase)
{
    std::string sPrompt = STRING_EMPTY;
    std::string sIp     = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort   = STRING_EMPTY;
    std::string sUser   = STRING_EMPTY;
    std::string sPass   = STRING_EMPTY;

    if (getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase) == false)
    {
		std::cerr << "No se pudo obtener los datos de conexión." << std::endl;
		return "";
	}

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "EXCEPCION CAPTURADA CONNECT TOKEN: " << objPSQL.getLastError() << '\n';
    }
    else
    {
        std::string  sSQL = STRING_EMPTY;

        if (sLenguaje.compare("JAVASCRIPT") == 0 )
        {
            sLenguaje = "JS";
        }
        else if (sLenguaje.compare("TYPESCRIPT") == 0)
        {
			sLenguaje = "TS";
		}
        else if (sLenguaje.compare("C#") == 0)
        {
			sLenguaje = "CS";
		}
        else if (sLenguaje.compare("VISUAL BASIC") == 0)
        {
			sLenguaje = "VB";
		}
        else if (sLenguaje.compare("C++") == 0)
        {
			sLenguaje = "CPP";
		}
        else if (sLenguaje.compare("C") == 0)
        {
			sLenguaje = "C";
		}
        else if (sLenguaje.compare("PYTHON") == 0)
        {
			sLenguaje = "PY";
		}
        else if (sLenguaje.compare("PHP") == 0)
        {
			sLenguaje = "PHP";
		}   

        sSQL.append(objUtils.stringFormat("SELECT fun_obtener_prompt('%s', '%s', '%s');", sNomCliente.c_str(), sLenguaje.c_str(), sModelo.c_str()));
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
                    sPrompt = STRING_EMPTY;

                    sPrompt.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);

                    sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), '('), sPrompt.end());
                    sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), ')'), sPrompt.end());
                    //sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), '\"'), sPrompt.end());
                    //sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), '"'), sPrompt.end());

                    //// Cambia las letras con acentos por letras sin acentos
                    //std::string acentos = "áéíóúÁÉÍÓÚ";
                    //std::string sin_acentos = "aeiouAEIOU";

                    //for (size_t k = 0; k < sPrompt.size(); ++k)
                    //{
                    //    size_t pos = acentos.find(sPrompt[k]);
                    //    if (pos != std::string::npos)
                    //    {
                    //        sPrompt[k] = sin_acentos[pos];
                    //    }
                    //}

                    //char* next_token1 = NULL;
                    //char* prtTok = NULL;
                    //char cTok[10000] = { 0 };

                    //memcpy_s(cTok, sizeof(cTok), sPrompt.c_str(), sPrompt.length());
                    //prtTok = strtok_s(cTok, ",", &next_token1);

                    ////std::cout << "Token " << sToken << std::endl;

                    //int iCont = 0;
                    //while (prtTok != NULL)
                    //{
                    //    iCont++;

                    //    switch (iCont)
                    //    {
                    //    case 1:
                    //        /*sPrompt = STRING_EMPTY;*/
                    //        sPrompt.append(prtTok);
                    //        break;
                    //    case 2:
                    //        /*sPrompt = STRING_EMPTY;*/
                    //        sPrompt.append(prtTok);
                    //        break;
                    //    case 3:
                    //        /*sPrompt = STRING_EMPTY;*/
                    //        sPrompt.append(prtTok);
                    //        break;
                    //    default:
                    //        break;
                    //    }

                    //    prtTok = strtok_s(NULL, ",", &next_token1);
                    //}
                    //prtTok = NULL;
                    //next_token1 = NULL;
                }
            }

            vcstRecords.clear();
        }

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return sPrompt;
}

// "C:\\Temp\\Bito\\test\\cobrosproveedorintranet\\totales.txt"
std::vector<Programa> CIA::getFileTotals(const std::string sFile)
{
    std::string linea;
    std::vector<Programa> programas;

    if (!std::filesystem::exists(sFile))
    {
        std::cout << "EL ARCHIVO " << sFile << " NO EXISTE.\n";
        //return 
    }
    else
    {
        std::ifstream archivo(sFile);       

        if (archivo.is_open())
        {
            while (getline(archivo, linea))
            {
                if (linea.find("github.com") != std::string::npos)
                {
                    continue;
                }

                if (linea.find("-") != std::string::npos)
                {
                    continue;
                }

                while (getline(archivo, linea))
                {
                    if (linea.find("-") != std::string::npos)
                    {
                        continue;
                    }

                    if (linea.find("Language ") != std::string::npos)
                    {
                        continue;
                    }

                    if (linea.find("SUM:") != std::string::npos)
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
                            p.sLenguaje += match_str + " ";
                        }
                        else if (std::all_of(match_str.begin(), match_str.end(), ::isdigit))
                        {
                            numbers.push_back(std::stoi(match_str));
                        }
                    }

                    p.sLenguaje.erase(p.sLenguaje.end() - 1); // Elimina el último espacio
                    std::transform(p.sLenguaje.begin(), p.sLenguaje.end(), p.sLenguaje.begin(), ::toupper);

                    // Asigna los números a las variables de la estructura
                    if (numbers.size() >= 4)
                    {
                        p.iArchivos     = numbers[0];
                        p.iLineasBlanco = numbers[1];
                        p.iComentarios  = numbers[2];
                        p.iLineasCodigo = numbers[3];
                    }

                    programas.push_back(p);
                }
                break;
            }
            archivo.close();
        }
        else
        {
            std::cout << "No se pudo abrir el archivo";
        }
    }

    return programas;
}

std::vector<Metricas> CIA::getMetricas(const std::vector<std::string>& vcLenguajes, std::string sTipo, const int iDataBase)
{
    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    std::vector<Metricas> metricas;

    if (getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase) == false)
    {
        std::cerr << "No se pudo obtener los datos de conexión." << std::endl;
        return metricas;
    }

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "EXCEPCION CAPTURADA CONNECT TOKEN: " << objPSQL.getLastError() << '\n';
    }
    else
    {
        // Recorremos el vector de lenguajes
        for (const auto& sLenguaje : vcLenguajes)
        {
            std::cout << "*";

			std::string  sSQL = STRING_EMPTY;

			sSQL.append(objUtils.stringFormat("SELECT fun_obtener_metricas_por_lenguaje('%s', '%s');", sLenguaje.c_str(), sTipo.c_str()));
            if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
            {
				std::cerr << "EXCEPCION CAPTURADA QUERY: " << objPSQL.getLastError() << '\n';
			}
            else
            {
				std::vector<ES_Records> vcstRecords;

				objPSQL.getRecords(vcstRecords);

				Metricas m; // Nueva instancia de Metricas
				m.sLenguaje = STRING_EMPTY;
				m.sLenguaje = sLenguaje;

                for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
                {
                    for (int j = 0; j < vcstRecords.size(); j++)
                    {
						sPrompt = STRING_EMPTY;

						sPrompt.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);

						sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), '('), sPrompt.end());
						sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), ')'), sPrompt.end());

						char* next_token1 = NULL;
						char* prtTok = NULL;
						char cTok[10000] = { 0 };

						memcpy_s(cTok, sizeof(cTok), sPrompt.c_str(), sPrompt.length());
						prtTok = strtok_s(cTok, ",", &next_token1);

						int iCont = 0;
                        while (prtTok != NULL)
                        {
							iCont++;

                            switch (iCont)
                            {
							case 1:
								m.iMigracion = atoi(prtTok);
								break;
							case 2:
								m.iVulnerabilidad = atoi(prtTok);
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

				metricas.push_back(m);

				vcstRecords.clear();
			}
        }

     //   std::string  sSQL = STRING_EMPTY;

     //   sSQL.append(objUtils.stringFormat("SELECT fun_obtener_metricas_por_lenguaje('%s', '%s');", sLenguaje.c_str(), sTipo.c_str()));
     //   if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
     //   {
     //       std::cerr << "EXCEPCION CAPTURADA QUERY: " << objPSQL.getLastError() << '\n';
     //   }
     //   else
     //   {
     //       std::vector<ES_Records> vcstRecords;

     //       objPSQL.getRecords(vcstRecords);

     //       Metricas m; // Nueva instancia de Metricas
     //       m.sLenguaje = STRING_EMPTY;
     //       m.sLenguaje = sLenguaje;

     //       for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
     //       {
     //           for (int j = 0; j < vcstRecords.size(); j++)
     //           {
     //               sPrompt = STRING_EMPTY;

     //               sPrompt.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);

     //               sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), '('), sPrompt.end());
     //               sPrompt.erase(std::remove(sPrompt.begin(), sPrompt.end(), ')'), sPrompt.end());

     //               char* next_token1 = NULL;
     //               char* prtTok = NULL;
     //               char cTok[10000] = { 0 };

     //               memcpy_s(cTok, sizeof(cTok), sPrompt.c_str(), sPrompt.length());
     //               prtTok = strtok_s(cTok, ",", &next_token1);

     //               int iCont = 0;
     //               
     //               while (prtTok != NULL)
     //               {
					//	iCont++;

     //                   switch (iCont)
     //                   {
					//	case 1:
					//		m.iMigracion = atoi(prtTok);
					//		break;
					//	case 3:
     //                       m.iVulnerabilidad = atoi(prtTok);
					//		break;
					//	default:
					//		break;
					//	}

					//	prtTok = strtok_s(NULL, ",", &next_token1);
					//}
     //               prtTok = NULL;
     //               next_token1 = NULL;

     //           }
     //       }

     //       vcstRecords.clear();
     //   }

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return metricas;
}

//std::string CIA::obtenerTokenDB(const long lEmpleado)
//{
//    bool bReturn = false;
//    std::string sToken = STRING_EMPTY;
//
//    if (!objPSQL.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
//    {
//        std::cerr << "EXCEPCION CAPTURADA CONNECT TOKEN: " << objPSQL.getLastError() << '\n';
//        bReturn = "";
//    }
//    else
//    {
//        std::string  sSQL = STRING_EMPTY;
//
//        sSQL.append(objUtils.stringFormat("SELECT fun_obtener_token('%ld'::integer);", lEmpleado));
//
//        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
//        {
//            std::cerr << "EXCEPCION CAPTURADA QUERY: " << objPSQL.getLastError() << '\n';
//            bReturn = "";
//        }
//        else
//        {
//            std::vector<ES_Records> vcstRecords;
//
//            objPSQL.getRecords(vcstRecords);
//
//            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
//            {
//                for (int j = 0; j < vcstRecords.size(); j++)
//                {
//                    sToken.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
//                }
//            }
//
//            vcstRecords.clear();
//        }
//
//        objPSQL.clearRecords();
//        objPSQL.closeConnection();
//    }
//
//    return sToken;
//}

bool CIA::registrarComentariosProyectoIA(const long lIdProyecto, const std::string sProjectName, const std::string sNombreArchivoPhp, const std::string sRespuestaSystemLinterOriginal, const std::string sBufferIniBito, const std::string sBufferFinBito, const std::string sExecutionTimeBito, const std::string sExecutionTimeInMinutes, const std::string sRespuestaSystemLinterNvo, const std::string sContenidoTxtLint, const std::string sComentariosBito, const int iDataBase )
{
    bool bReturn = false;
    std::string sSQL = STRING_EMPTY;
    std::string sResp = STRING_EMPTY;

    std::vector<ES_Records> vcstRecords;

    std::string sPrompt = STRING_EMPTY;
    std::string sIp = STRING_EMPTY;
    std::string sDbName = STRING_EMPTY;
    std::string sPort = STRING_EMPTY;
    std::string sUser = STRING_EMPTY;
    std::string sPass = STRING_EMPTY;

    getDataFileINI(sIp, sDbName, sPort, sUser, sPass, iDataBase);

    if (!objPSQL.openConnection(sDbName.c_str(), sUser.c_str(), sPass.c_str(), sIp.c_str()))
    {
        std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
        bReturn = false;
    }
    else
    {
        bReturn = false;
        //-- INSERT
        //sSQL.append(utils.stringFormat("INSERT INTO test (num_proveedor, nom_proveedor) VALUES('8', 'COPPEL8');"));
        sSQL.append(objUtils.stringFormat("SELECT fun_registrar_comentarios_proyecto_ia( '%ld'::BIGINT, '%ld'::BIGINT, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying, '%s'::character varying );",
            lColaborador, lIdProyecto, sNomProyecto.c_str(), sNombreArchivoPhp.c_str(), sRespuestaSystemLinterOriginal.c_str(), sBufferIniBito.c_str(), sBufferFinBito.c_str(), sExecutionTimeBito.c_str(), sExecutionTimeInMinutes.c_str(), sRespuestaSystemLinterNvo.c_str(), sContenidoTxtLint.c_str(), sComentariosBito.c_str()));

        if (!objPSQL.queryExec(sSQL.c_str(), SELECT_QUERY))
        {
            std::cerr << "Excepción capturada: " << objPSQL.getLastError() << '\n';
            bReturn = false;
        }
        else
        {
            objPSQL.getRecords(vcstRecords);

            for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
            {
                for (int j = 0; j < vcstRecords.size(); j++)
                {
                    //csResp.AppendFormat(j != (vcstRecords.size() - 1) ? "%s|" : "%s", vcstRecords[j].vcValues[i]);
                    //iRespuesta = _ttoi(csResp);
                    bReturn = true;
                    sResp.append(j != (vcstRecords.size() - 1) ? vcstRecords[j].vcValues[i] : vcstRecords[j].vcValues[i]);
                }
            }
        }

        sSQL = STRING_EMPTY;

        objPSQL.clearRecords();
        objPSQL.closeConnection();
    }

    return bReturn;
}


// Función para escapar caracteres especiales en una cadena
std::string CIA::sanitizarCadenas(const std::string& input) 
{
    std::string sanitized = input;

    // Reemplazar comillas simples por dos comillas simples
    std::replace(sanitized.begin(), sanitized.end(), '\'', '-');
    std::replace(sanitized.begin(), sanitized.end(), '\\', '#');
    std::replace(sanitized.begin(), sanitized.end(), '\*', ' ');
    std::replace(sanitized.begin(), sanitized.end(), '\`', '@');
    // Agregar más reemplazos de caracteres especiales aquí...

    return sanitized;
}


//void CIA::search_sql_in_file(const std::string& file_path, std::map<std::string, int>& mapSentencias, const long lIdProyecto, const int iDataBase)
//{
//    std::ifstream file(file_path);
//    std::string line;
//    std::string sCadena;
//    int line_number = 0;
//    std::wstring wstr; // Convierte a wstring para poder escribir en el archivo CSV
//
//    while (std::getline(file, line))
//    {
//        line_number++;
//        if (std::regex_search(line, matchesSql, patternSql))
//        {
//            //std::string str(matchesSql[0]);
//            //sCadena = file_path + "|" + std::to_string(line_number) + "|" + str + "|";
//            //wstr = convertStringToWString(sCadena);
//
//            std::string str(matchesSql[0]);
//            // Se verifica si la sentencia SQL encontrada es un SELECT
//            // Si es un SELECT, no se registra la sentencia.
//            if (str.find("<select") != std::string::npos || str.find("<SELECT") != std::string::npos)
//            {
//                continue; // No continuar con el registro de la sentencia encontrada
//            }
//
//            std::string extension = file_path.substr(file_path.find_last_of(".") + 1);
//            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
//
//            //std::cout << "EXTENSION: " << extension << std::endl;
//            mapSentencias[extension]++;
//
//            //csv_file << wstr << std::endl;
//            //csv_file << file_path << "|" << line_number << "|" << matchesSql[0] << "|" << std::endl;
//
//            registrarSentencias(file_path, line_number, matchesSql[0], lIdProyecto, iDataBase);
//
//            //std::cout << "Sentencia SQL encontrada en el archivo " << file_path << ", línea " << line_number << ": " << matchesSql[0] << std::endl;
//        }
//    }
//}


//void CIA::search_sql_in_file(const std::string& file_path, std::map<std::string, int>& mapSentencias, const long lIdProyecto, const int iDataBase)
//{
//    std::ifstream file(file_path);
//    std::string line;
//    std::string sCadena;
//    int line_number = 0;
//    std::wstring wstr; // Convierte a wstring para poder escribir en el archivo CSV

//void CIA::patternCreate()
//{
//
//}