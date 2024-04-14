// RvIA.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#define MAIN

#include "CIA.hpp"

//static void validateParameters(std::string &sRutaProyecto, std::string &sLenguaje, std::string &sTipoMigracion, std::string &sNumColaboradores);
//static void validateParametersAll(std::string& sRutaProyecto, std::string& sTipoMigracion, std::string& sNumColaboradores);
//static int obtenerOcurrencias(const std::string& sLenguaje, const std::string& sTipoDeMigracion);
//static std::map<std::string, int> obtenerMetaSemanalMigVul(const std::vector<std::string>& vcLenguajes, const std::string& sTipoDeMigracion);
static void recorrerMapa(const std::map<std::string, int>& mapOcurrencias);
static int obtenerValorMapa(const std::map<std::string, int>& mapOcurrencias, std::string sLenguaje);


int main(int argc, char* argv[])
{
	int iTecla				= 0;
	int iDataBase			= 0;
	int iHigh				= 0;
	int iMedium				= 0;
	int iLow				= 0;
	int iConIA				= 0;
	long lEmpleado			= 0L;
	char cPath[MAX_PATH]			= { 0 };
	char cArmarTotales[MAX_PATH]	= { 0 };

	std::vector<std::string> vcLenguajes;
	vcLenguajes.clear();

	//Función para crear un archivo directorio si no existe
	std::filesystem::create_directory("c:\\sys");
	std::filesystem::create_directory("c:\\sys\\mem");
	std::filesystem::create_directory("c:\\sys\\progs");
	std::filesystem::create_directory("c:\\sys\\progs\\parse");
	std::filesystem::create_directory("c:\\sys\\progs\\parse\\bito");

	system("cls");
	//system("chcp 936");

	std::locale::global(std::locale("es_MX.UTF8"));
	setlocale(LC_ALL, "es_MX.UTF8");
	
	std::string sRutaProyecto;
	std::string sLenguaje;
	std::string sTipoDeMigracion;
	std::string sNumeroOcurrencias;
	std::string sNumeroDeColaboradores;
	std::string sFechaArg;
	std::string sFecha;
	std::string sExtension;
	int iNumeroDeColaboradores = 0;

	if (argc >= 8)
	{
		std::vector<Programa> vcProgramas;

		// Obtiene si se pasa con IA o sin IA.
		// 0 = Sin IA, 1 = Con IA
		iConIA = atoi(argv[1]);

		if(iConIA != 0 && iConIA != 1)
		{
			std::cerr << "Error: Parámetro inválido (IA)" << std::endl;
			return ERROR_INVALID_PARAMETER;
		}

		// Obtiene el número de empleado
		lEmpleado = atol(argv[2]);

		if (lEmpleado < 90000000L || lEmpleado > 99999999L)
		{
			std::cerr << "Error: Parámetro inválido (empleado)" << std::endl;
			return ERROR_INVALID_PARAMETER;
		}

		// Obtiene la ruta del proyecto
		memset(cPath, 0, sizeof(cPath));
		sprintf_s(cPath, sizeof(cPath), "%s", argv[3]);

		std::string sPath = cPath;
		std::string sNombreProyecto = sPath.substr(sPath.find_last_of("\\") + 1);

		std::cout << "Nombre del proyecto: " << sNombreProyecto << std::endl;

		std::string sFileCheckmarx = sPath + "\\checkmarx_" + sNombreProyecto + ".csv";
		//std::cout << "Nombre del archivo checkmarx: " << sFileCheckmarx << std::endl;

		//Obtiene el tipo de migración
		sTipoDeMigracion = argv[4];

		//validar que el tipo de migración sea solo mig o vul
		if (sTipoDeMigracion.compare("mig") != 0 && sTipoDeMigracion.compare("vul") != 0)
		{
			std::cerr << "Error: Por favor captura solo mig o vul. Ejemplo (mig o vul)" << std::endl;
			return ERROR_INVALID_PARAMETER;
		}

		//Obtiene el número de colaboradores que participan en el proyecto.
		iNumeroDeColaboradores = atoi(argv[5]);

		//validar que el número de colaboradores sea solo números naturales
		if (iNumeroDeColaboradores <= 0)
		{
			std::cerr << "Error: Solo se permiten números. Ejemplo (1, 2, 3, 4, 5, etc...)" << std::endl;
			return ERROR_INVALID_PARAMETER;
		}

		// Obtiene la fecha del parámetro de entrada en formato YYYY-MM-DD
		sFechaArg = argv[6];

		//validar que la fecha sea en formato YYYY-MM-DD
		if (sFechaArg.length() != 10)
		{
			std::cerr << "Error: Por favor captura la fecha en formato YYYY-MM-DD" << std::endl;
			return ERROR_INVALID_PARAMETER;
		}

		// 1 = Producción
		// 2 = Desarrollo
        if (argv[7] == nullptr || argv[7][0] == '\0' || std::string(argv[7]).empty()) 
		{
            // argv[6] is empty, blank, or null
            iDataBase = 1;
        }
		else
		{
			iDataBase = atoi(argv[7]);
		}		

		// Obtiene la ruta del archivo a generar
		memset(cArmarTotales, 0, sizeof(cArmarTotales));
		sprintf_s(cArmarTotales, sizeof(cArmarTotales), "%s\\%s", cPath, "totales.txt");
		// Elimina el archivo existente
		std::filesystem::remove(cArmarTotales);

		CIA objCIA(sNombreProyecto, lEmpleado);

		// Obtiene el ID del proyecto
		long lIdProyecto = objCIA.generarIDProyecto();

		std::cout << "ID del proyecto: " << lIdProyecto << std::endl;

		long lRespuesta = 0L;
		objCIA.validarExisteEmpleadoTB(lEmpleado, lRespuesta, iDataBase);

		if (lRespuesta != lEmpleado)
		{
			objCIA.setColor(2); // Verde
			std::cerr << "Error: El empleado no tiene permisos de ejecución" << std::endl;
			objCIA.setColor(7); // Blanco
			return ERROR_USER_PROFILE_LOAD; // 500L
		}

		std::string sTokenProporcionado = STRING_EMPTY;
		std::string sToken				= STRING_EMPTY; 

		// Leer el token y la fecha de expiración del archivo
		std::ifstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
		if (!tokenFile.is_open())
		{
			std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA LEER EL TOKEN.\n";
			return ERROR_FILE_INVALID;
		}

		std::getline(tokenFile, sTokenProporcionado);  // Leer el token proporcionado
		std::getline(tokenFile, sFecha);  // Leer la fecha de expiración
		
		tokenFile.close();

		objCIA.obtenerTokenDB(lEmpleado, sTokenProporcionado, sToken, sFecha, iDataBase);

		// Comprueba si el token proporcionado es válido
		//std::string tokenProporcionado = /* el token proporcionado por el usuario */;
		ResultadoValidacion resultado = objCIA.esTokenValidoDB(lEmpleado, sTokenProporcionado, iDataBase);
		switch (resultado)
		{
		case ResultadoValidacion::Exito:
			std::cout << "El token es válido.\n";
			break;
		case ResultadoValidacion::ErrorAperturaArchivo:
			objCIA.setColor(4); // Rojo
			std::cerr << "No se pudo abrir el archivo para leer el token.\n";
			objCIA.setColor(7); // Blanco
			return ERROR_INVALID_TOKEN;
		case ResultadoValidacion::ErrorTokenNoCoincide:
			objCIA.setColor(4); // Rojo
			std::cout << "El token proporcionado no coincide con el token guardado.\n";
			objCIA.setColor(7); // Blanco
			return ERROR_INVALID_TOKEN;
		case ResultadoValidacion::ErrorTokenExpirado:
			objCIA.setColor(4); // Rojo
			std::cout << "El token ha expirado.\n";
			objCIA.setColor(7); // Blanco
			return ERROR_INVALID_TOKEN;
		}
		
		// Inicia el reloj
		std::clock_t start_time = std::clock();

		// Verifica el token
		if (resultado == ResultadoValidacion::Exito)
		{
			std::cout << "-----------------------------------------------------" << std::endl;
			std::cout << " Herramienta de Migración y Vulnerabilidades con IA  " << std::endl;
			std::cout << "_____________________________________________________" << std::endl;
			std::cout << std::endl;
			Sleep(2000);

			objCIA.setColor(7); // Blanco
			std::cout << "INICIA LA GENERACIÓN DE TOTALES POR LENGUAJE DE PROGRAMACION.\n";
			objCIA.setColor(2); // Verde			
			
			if ( objCIA.getTotals(cPath, cArmarTotales) != 0 )
			{
				objCIA.setColor(4); // Rojo
				std::cerr << "Error al obtener totales.\nFaltan dependencias del aplicativo." << std::endl;
				objCIA.setColor(7); // Blanco
				return ERROR_FILE_NOT_FOUND;
			}
			
			vcProgramas = objCIA.getFileTotals(cArmarTotales);

			std::vector<Metricas> vecMetricas;

			if (vcProgramas.size() > 0)
			{

				if (!objCIA.registrarControlDeProyectos(lIdProyecto, sNombreProyecto, iConIA, iDataBase) )
				{
					std::cerr << "Error: No se pudo registrar el control del proyecto." << std::endl;
					return ERROR_DATABASE_FAILURE;
				}

				objCIA.setColor(7); // Blanco
				std::cout << "ESPERE, SE REGISTRAN TOTAL DEL PROYECTO.\n";
				objCIA.setColor(2); // Verde
				
				// Iterar sobre el vector de programas y llamar la función bool CIA::registrarTotalesProyectos
				for (const auto& p : vcProgramas)
				{
					//std::cout << p.sLenguaje << "," << p.iArchivos << "," << p.iLineasBlanco << "," << p.iComentarios << "," << p.iLineasCodigo << std::endl;
					std::cout << "TOTAL DE ARCHIVOS ENCONTRADOS [ " << p.iArchivos << " ] DE " << p.sLenguaje << std::endl;

					if (!objCIA.registrarTotalesProyectos(lIdProyecto, sNombreProyecto.c_str(), p.sLenguaje, p.iArchivos, p.iLineasBlanco, p.iComentarios, p.iLineasCodigo, iDataBase))
					{
						std::cerr << "Error: No se pudo registrar el lenguaje: " << p.sLenguaje << std::endl;
						return ERROR_DATABASE_FAILURE;
					}
					else
					{
						vcLenguajes.push_back(p.sLenguaje);
					}
				}

				std::cout << std::endl;
				std::cout << "FINALIZA EL REGISTRO DE TOTALES DEL PROYECTO.\n";
				std::cout << std::endl;

				objCIA.setColor(7); // Blanco
				std::cout << "FINALIZA LA GENERACIÓN DE TOTALES POR LENGUAJE DE PROGRAMACION.\n";
				std::cout << std::endl;
			
				objCIA.setColor(7); // Blanco
				std::cout << "INICIA PROCESO DE OBTENER SENTENCIAS SQL.\n";
				objCIA.setColor(BACKGROUND_RED);
				// Ya graba en la BD
				std::map<std::string, int> mapSentencias = objCIA.obtieneSentenciasSQLEnMapa(cPath, lIdProyecto, iDataBase);
				
				std::cout << std::endl;
				recorrerMapa(mapSentencias);
				std::cout << std::endl;
				
				objCIA.setColor(7); // Blanco
				std::cout << "FINALIZA EL PROCESO DE OBTENER SENTENCIAS SQL.\n";
				std::cout << std::endl;

				std::cout << "ESPERE, OBTIENE FUNCIONES OBSOLETAS.\n";
				objCIA.setColor(BACKGROUND_GREEN);
				// Ya graba en la BD
				//////std::map<std::string, int> mapDeprecated;
				std::map<std::string, int> mapDeprecated = objCIA.obtieneFuncionesObsoletasEnMapa(cPath, lIdProyecto, iDataBase);
				
				std::cout << std::endl;
				recorrerMapa(mapDeprecated);
				std::cout << std::endl;

				objCIA.setColor(7); // Blanco
				std::cout << "FINALIZA EL PROCESO DE OBTENER FUNCIONES OBSOLETAS.\n";
				std::cout << std::endl;

				// Unir los dos mapas 'mapSentencias', 'mapDeprecated' en uno solo y sumar los valores de las llaves que coincidan en ambos mapas. El valor que no coincida se agrega al mapa final.
				std::map<std::string, int> mapFinal;

                for (const auto& pair : mapSentencias) 
				{
                    const std::string& key	= pair.first;
                    int value				= pair.second;

                    if (mapDeprecated.count(key) > 0) 
					{
                        value += mapDeprecated[key];
                        mapDeprecated.erase(key);
                    }

                    mapFinal[key] = value;
                }

                // Add remaining entries from mapDeprecated to mapFinal
                for (const auto& pair : mapDeprecated) 
				{
                    const std::string& key	= pair.first;
                    int value				= pair.second;
                    mapFinal[key]			= value;
                }

				std::cout << std::endl;
				recorrerMapa(mapFinal);
				std::cout << std::endl;

				objCIA.setColor(7); // Blanco
				std::cout << "INICIA PROCESO DE OBTENER DATOS CHECKMARX.\n";

				objCIA.setColor(FOREGROUND_RED);
				
				if (!objCIA.getDataFromCheckmarx(lIdProyecto, sFileCheckmarx, iHigh, iMedium, iLow, iDataBase))
				{
					objCIA.setColor(4); // Rojo
					std::cerr << "Error: No se encontraron datos en el archivo Checkmarx." << std::endl;
					objCIA.setColor(7); // Blanco
					//return ERROR_FILE_NOT_FOUND;
				}

				objCIA.setColor(7); // Blanco
				std::cout << "FINALIZA EL PROCESO DE OBTENER DATOS CHECKMARX.\n";
				std::cout << std::endl;

				std::cout << "INICIA EL PROCESO GENERANDO ARCHIVOS PROMPT.\n";
				objCIA.setColor(BACKGROUND_INTENSITY);

				for (const auto& fileExtension : vcLenguajes)
				{
					std::cout << "*";

					sExtension = fileExtension.substr(fileExtension.find_last_of(".") + 1);
                    std::transform(sExtension.begin(), sExtension.end(), sExtension.begin(), ::toupper);

					std::string sPrompt = objCIA.obtenerPrompt("BITO", sExtension, "ADVANCED", iDataBase);
					objCIA.generarArchivosPrompt(sPrompt, sExtension);
				}

				std::cout << std::endl;
				objCIA.setColor(7); // Blanco
				std::cout << "FINALIZA EL PROCESO DE GENERACION DE ARCHIVOS PROMPT.\n";
				std::cout << std::endl;

				std::cout << "INICIA EL PROCESO DE OBTENER METRICAS.\n";
				objCIA.setColor(FOREGROUND_INTENSITY);
				
				vecMetricas = objCIA.getMetricas(vcLenguajes, "DESARROLLO", iDataBase);

				std::cout << std::endl;
				objCIA.setColor(7); // Blanco
				std::cout << "FINALIZA EL PROCESO DE OBTENER METRICAS.\n";
				std::cout << std::endl;

				if ( iConIA == 1 )
				{
					std::cout << "INICIA EL PROCESO DE IA CON BITO.\n";
					objCIA.setColor(2); // Verde

					objCIA.ejecutaProcesoIA(cPath, lIdProyecto, iDataBase);

					objCIA.setColor(7); // Blanco
					std::cout << "GRACIAS POR ESPERAR, SE FINALIZO EL PROCESO CON IA BITO.\n";
					std::cout << std::endl;
				}
				else
				{
					std::cout << "SE EJECUTO EL PROCESO SIN (IA).\n";
				}

				std::cout << "INICIA EL PROCESO DE CALCULAR FECHA FIN DEL PROYECTO.\n";
				objCIA.setColor(FOREGROUND_INTENSITY);
				
				/*
				Tot Meta = 176
				Tot Rec = 3
				Tot Sem = Tot Meta * Tot Rec;
				Duración = Tot Ocu / Tot Sem.
				Duración Días = (Tot Ocu / Tot Sem.) / 5
				*/
				int iTotSemMig			= 0;
				int iTotSemVul			= 0;
				int iTotalSentDep		= 0;
				int iTotalCheckmarx		= iHigh + iMedium + iLow;;
				int iTotal				= 0;
				int iTotalDias			= 0;
				int iTotalDiasInhabiles = 0;
				int iDuracion			= 0;
				int iDuracionDias		= 0;
				int iDuracionHoras		= 0;
				std::string sLengMap;

				// Recorrer el vector vecMetaSemanal
				std::vector<Metricas>::const_iterator it;
				for (it = vecMetricas.begin(); it != vecMetricas.end(); ++it)
				{
					if (it->sLenguaje.compare("PHP") == 0 || 
						it->sLenguaje.compare("JS") == 0 || it->sLenguaje.compare("JAVASCRIPT") == 0 ||
						it->sLenguaje.compare("TS") == 0 || it->sLenguaje.compare("TYPESCRIPT") == 0 ||
						it->sLenguaje.compare("PY") == 0 || it->sLenguaje.compare("PYTHON") == 0 ||
						it->sLenguaje.compare("CS") == 0 || it->sLenguaje.compare("CSHARP") == 0 ||
						it->sLenguaje.compare("C") == 0 || it->sLenguaje.compare("CPP") == 0 ||
						it->sLenguaje.compare("C++") == 0 ||
						it->sLenguaje.compare("VB") == 0 || it->sLenguaje.compare("BAS") == 0 ||
						it->sLenguaje.compare("VISUAL BASIC") == 0 || it->sLenguaje.compare("VISUAL BASIC .NET") == 0

						)
					{
						if (sTipoDeMigracion.compare("mig") == 0)
						{
							iTotSemMig = it->iMigracion * iNumeroDeColaboradores;
							std::cout << std::endl;
							std::cout << "TOTAL DE MIGRACIONES POR SEMANA: " << iTotSemMig << " DEL LENGUAJE [ " << it->sLenguaje << " ]" << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;

							if (it->sLenguaje.compare("JAVASCRIPT") == 0 )
							{
								sLengMap = "JS";
							}
							else if (it->sLenguaje.compare("TYPESCRIPT") == 0)
							{
								sLengMap = "TS";
							}
							else if (it->sLenguaje.compare("PYTHON") == 0)
							{
								sLengMap = "PY";
							}
							else if (it->sLenguaje.compare("CSHARP") == 0)
							{
								sLengMap = "CS";
							}
							else if (it->sLenguaje.compare("C++") == 0)
							{
								sLengMap = "CPP";
							}
							else if (it->sLenguaje.compare("VISUAL BASIC") == 0)
							{
								sLengMap = "VB";
							}
							else if (it->sLenguaje.compare("VISUAL BASIC .NET") == 0)
							{
								sLengMap = "BAS";
							}
							else
							{
								sLengMap = it->sLenguaje;
							}

							iTotalSentDep = obtenerValorMapa(mapFinal, sLengMap);
							iTotal = iTotalSentDep + iTotalCheckmarx;

							std::cout << "TOTAL DE SENTENCIAS DEPRECATED: " << iTotalSentDep << " DEL LENGUAJE [ " << sLengMap << " ]." << std::endl;
							std::cout << "TOTAL : " << iTotal << std::endl;

							if (iTotSemMig != 0)
							{
								iDuracion		= iTotal / iTotSemMig;
								iDuracionDias	= iDuracion * 7;
								iDuracionHoras	= iDuracionDias * 9; // Calcula el total en horas

								std::cout << "DURACIÓN EN SEMANAS: " << iDuracion << std::endl;
								std::cout << "DURACIÓN EN DÍAS: " << iDuracionDias << std::endl;
								std::cout << "DURACIÓN EN HORAS: " << iDuracionHoras << std::endl;
								std::cout << std::endl;

								std::string sFechaInicial;
								std::string sFechaFinal;
								std::string sFechaFinalLunVie;

								objCIA.calcularFechaFinal(iDuracionDias, sFechaArg, sFechaInicial, sFechaFinal, iTotalDias, iTotalDiasInhabiles, sFechaFinalLunVie);

								if (objCIA.registrarFechasDeProyecto(lIdProyecto, sNombreProyecto, sLenguaje, iTotal, it->iMigracion, iNumeroDeColaboradores, iTotSemMig,
									iDuracionDias, iDuracionHoras, sFechaInicial, sFechaFinal, iTotalDiasInhabiles, sFechaFinalLunVie, iDataBase) == false)
								{
									std::cerr << "ERROR: NO SE PUDO REGISTRAR LAS FECHAS DEL PROYECTO." << std::endl;
									return ERROR_DATABASE_FAILURE;
								}
							}
							else
							{
								std::cout << "ERROR: iTotSemMig ES CERO, NO SE PUEDE DIVIDIR POR CERO." << std::endl;
								return -1; //BN_R_DIV_BY_ZERO;
							}
						}
						else if (sTipoDeMigracion.compare("vul") == 0)
						{
							iTotSemVul = it->iVulnerabilidad * iNumeroDeColaboradores;
							std::cout << std::endl;
							std::cout << "TOTAL DE VULNERABILIDADES POR SEMANA: " << iTotSemVul << " DEL LENGUAJE [ " << it->sLenguaje << " ]" << " QUE DEBEN REALIZAR LOS [" << iNumeroDeColaboradores << "] COLABORADORES." << std::endl;

							if (it->sLenguaje.compare("JAVASCRIPT") == 0)
							{
								sLengMap = "JS";
							}
							else if (it->sLenguaje.compare("TYPESCRIPT") == 0)
							{
								sLengMap = "TS";
							}
							else if (it->sLenguaje.compare("PYTHON") == 0)
							{
								sLengMap = "PY";
							}
							else if (it->sLenguaje.compare("CSHARP") == 0)
							{
								sLengMap = "CS";
							}
							else if (it->sLenguaje.compare("C++") == 0)
							{
								sLengMap = "CPP";
							}
							else if (it->sLenguaje.compare("VISUAL BASIC") == 0)
							{
								sLengMap = "VB";
							}
							else if (it->sLenguaje.compare("VISUAL BASIC .NET") == 0)
							{
								sLengMap = "BAS";
							}
							else
							{
								sLengMap = it->sLenguaje;
							}

							iTotalSentDep = obtenerValorMapa(mapFinal, sLengMap);
							iTotal = iTotalSentDep + iTotalCheckmarx;

							std::cout << "TOTAL DE SENTENCIAS DEPRECATED: " << iTotalSentDep << " DEL LENGUAJE [ " << sLengMap << " ]." << std::endl;
							std::cout << "TOTAL : " << iTotal << std::endl;

							if (iTotSemVul != 0)
							{
								iDuracion = iTotal / iTotSemVul;
								iDuracionDias = iDuracion * 7;
								iDuracionHoras = iDuracionDias * 9; // Calcula el total en horas

								std::cout << "DURACIÓN EN SEMANAS: " << iDuracion << std::endl;
								std::cout << "DURACIÓN EN DÍAS: " << iDuracionDias << std::endl;
								std::cout << "DURACIÓN EN HORAS: " << iDuracionHoras << std::endl;
								std::cout << std::endl;

								std::string sFechaInicial;
								std::string sFechaFinal;
								std::string sFechaFinalLunVie;

								objCIA.calcularFechaFinal(iDuracionDias, sFechaArg, sFechaInicial, sFechaFinal, iTotalDias, iTotalDiasInhabiles, sFechaFinalLunVie);

								if (objCIA.registrarFechasDeProyecto(lIdProyecto, sNombreProyecto, sLenguaje, iTotal, it->iVulnerabilidad, iNumeroDeColaboradores, iTotSemVul,
									iDuracionDias, iDuracionHoras, sFechaInicial, sFechaFinal, iTotalDiasInhabiles, sFechaFinalLunVie, iDataBase) == false)
								{
									std::cerr << "ERROR: NO SE PUDO REGISTRAR LAS FECHAS DEL PROYECTO." << std::endl;
									return ERROR_DATABASE_FAILURE;
								}
							}
							else
							{
								std::cout << "ERROR: iTotSemVul ES CERO, NO SE PUEDE DIVIDIR POR CERO." << std::endl;
								return -1; //BN_R_DIV_BY_ZERO;
							}							
						}
					}
				}

				std::cout << std::endl;
	
				vcLenguajes.clear();
				mapFinal.clear();
				vecMetricas.clear();
				mapSentencias.clear();
				mapDeprecated.clear();
			}
			else
			{
				std::cout << "No se encontraron archivos a procesar." << std::endl;
				return ERROR_FILE_NOT_FOUND;
			}

			vcProgramas.clear();
		}

		objCIA.setColor(7); // Blanco
		std::cout << "  FAVOR DE TOMAR NOTA DE LOS DATOS DE TU PROYECTO PARA SEGUIMIENTO " << std::endl;
		std::cout << "___________________________________________________________________" << std::endl;
		std::cout << "EL PROYECTO QUE SE PROCESO ES: " << "[ " << sNombreProyecto << " ]." << std::endl;
		std::cout << "EL ID DE TU PROYECTO ES: " << "[ " << lIdProyecto << " ].          " << std::endl;
		std::cout << "___________________________________________________________________" << std::endl;
		std::cout << std::endl;
		
		std::cout << std::endl;
		double execution_time = (std::clock() - start_time) / (double)CLOCKS_PER_SEC;
		std::cout << "TIEMPO DE EJECUCIÓN, " << execution_time << " SEGUNDOS" << std::endl;

		std::cout << std::endl;
		objCIA.setColor(7); // Blanco
		std::cout << "PROCESO FINALIZADO. PRESIONA CUALQUIER TECLA PARA FINALIZAR..." << std::endl;
		iTecla = _getch();

		return 0;
	}
	else
	{
		std::cout << "-----------------------------------\n";
		//std::cout << "Ejemplo de uso A) : " << argv[0] << " -v\n";
		//std::cout << "Ejemplo de uso : " << argv[0] << " -t\n";
		std::cout << "Ejemplo de uso : " << argv[0] << " < 0 = Sin IA | 1 = Con IA > " << " <Numero de empleado> " << " <Ruta de proyecto> <mig|vul> <numeroDeColaboradores>\n";
		//std::cout << "Ejemplo : " << argv[0] << " c:\\temp\\proyecto php mig|vul 1\n";
		std::cout << "-----------------------------------\n";
		return ERROR_INVALID_PARAMETER;
	}
		
	return 0;
}

//static int obtenerOcurrencias(const std::string& sLenguaje, const std::string& sTipoDeMigracion)
//{
//	std::string sNumeroOcurrencias;
//	int iNumeroOcurrencias = 0;
//
//	//validar el tipo de lenguaje que entro por parámetro y si el tipo de migración es mig o vul.
//	if (sLenguaje.compare("php") == 0 || sLenguaje.compare("PHP") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			// convertir a entero el numero de ocurrencias
//			sNumeroOcurrencias = std::to_string(PHP_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(PHP_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("cpp") == 0 || sLenguaje.compare("CPP") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(CPP_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(CPP_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("C") == 0 || sLenguaje.compare("c") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(C_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(C_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("JAVA") == 0 || sLenguaje.compare("java") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(JAVA_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(JAVA_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("JS") == 0 || sLenguaje.compare("js") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(JAVASCRIPT_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(JAVASCRIPT_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("CS") == 0 || sLenguaje.compare("cs") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(CSHARP_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(CSHARP_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("PY") == 0 || sLenguaje.compare("py") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(PYTHON_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(PYTHON_VULNERABILIDADES_META);
//		}
//	}
//	else if (sLenguaje.compare("TS") == 0 || sLenguaje.compare("ts") == 0)
//	{
//		if (sTipoDeMigracion.compare("mig") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(TYPESCRIPT_MIGRACION_META);
//		}
//		else if (sTipoDeMigracion.compare("vul") == 0)
//		{
//			sNumeroOcurrencias = std::to_string(TYPESCRIPT_VULNERABILIDADES_META);
//		}
//	}
//	else
//	{
//		std::cout << "Error: Por favor captura solo la extensión del lenguaje. Ejemplo (PHP, CPP, TS, JS, C, JAVA, Etc...)" << std::endl;
//		return 1;
//	}
//
//	//convertir sNumeroOcurrencias a int
//	iNumeroOcurrencias = std::stoi(sNumeroOcurrencias);
//
//	return iNumeroOcurrencias;
//}


//static std::map<std::string, int> obtenerMetaSemanalMigVul(const std::vector<std::string>& vcLenguajes, const std::string& sTipoDeMigracion)
//{
//	std::map<std::string, int> mapOcurrencias;
//
//	for (const auto& sLenguaje : vcLenguajes)
//	{
//		//validar el tipo de lenguaje que entro por parámetro y si el tipo de migración es mig o vul.
//		if (sLenguaje.compare(".php") == 0 || sLenguaje.compare(".PHP") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["PHP"] += PHP_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["PHP"] += PHP_VULNERABILIDADES_META;
//			}
//		}
//		
//		if (sLenguaje.compare(".cpp") == 0 || sLenguaje.compare(".CPP") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["CPP"] += CPP_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["CPP"] += CPP_VULNERABILIDADES_META;
//			}
//		}
//
//		if (sLenguaje.compare(".C") == 0 || sLenguaje.compare(".c") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["C"] += C_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["C"] += C_VULNERABILIDADES_META;
//			}
//		}	
//
//		if (sLenguaje.compare(".JAVA") == 0 || sLenguaje.compare(".java") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["JAVA"] += JAVA_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["JAVA"] += JAVA_VULNERABILIDADES_META;
//			}
//		}
//
//		if (sLenguaje.compare(".JS") == 0 || sLenguaje.compare(".js") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["JS"] += JAVASCRIPT_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["JS"] += JAVASCRIPT_VULNERABILIDADES_META;
//			}
//		}
//
//		if (sLenguaje.compare(".CS") == 0 || sLenguaje.compare(".cs") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["CS"] += CSHARP_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["CS"] += CSHARP_VULNERABILIDADES_META;
//			}
//		}
//
//		if (sLenguaje.compare(".PY") == 0 || sLenguaje.compare(".py") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["PY"] += PYTHON_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["PY"] += PYTHON_VULNERABILIDADES_META;
//			}
//		}
//
//		if (sLenguaje.compare(".TS") == 0 || sLenguaje.compare(".ts") == 0)
//		{
//			if (sTipoDeMigracion.compare("mig") == 0)
//			{
//				// incrementar el numero de ocurrencias
//				mapOcurrencias["TS"] += TYPESCRIPT_MIGRACION_META;
//			}
//			else if (sTipoDeMigracion.compare("vul") == 0)
//			{
//				mapOcurrencias["TS"] += TYPESCRIPT_VULNERABILIDADES_META;
//			}
//		}
//	}
//
//	return mapOcurrencias;
//}

static void recorrerMapa(const std::map<std::string, int>& mapOcurrencias)
{
	for (const auto& par : mapOcurrencias)
	{
		std::cout << "Lenguaje de programación: " << par.first << ", Número de ocurrencias: " << par.second << std::endl;
	}
}

// Obtener el valor de un mapa(const std::map<std::string, int>& mapOcurrencias, const std::string sLenguaje) donde el lenguaje sea igual y devolverlo como entero.
static int obtenerValorMapa(const std::map<std::string, int>& mapOcurrencias, std::string sLenguaje)
{
	int iValor = 0;
	std::string sLenguajeMayusculas;

	for (const auto& par : mapOcurrencias)
	{
		// Convertir a mayúsculas el lenguaje que se recibe por parámetro y comparar con el mapa.
		sLenguajeMayusculas = par.first;

		std::transform(sLenguajeMayusculas.begin(), sLenguajeMayusculas.end(), sLenguajeMayusculas.begin(), ::toupper);
		std::transform(sLenguaje.begin(), sLenguaje.end(), sLenguaje.begin(), ::toupper);

		std::cout << "LENGUAJE DE PROGRAMACION MAP : " << sLenguajeMayusculas << std::endl;
		std::cout << "LENGUAJE DE PROGRAMACION PAR : " << sLenguaje << std::endl;

		if (sLenguajeMayusculas.compare(sLenguaje) == 0)
		{
			iValor = par.second;
			break;
		}
	}

	std::cout << "VALOR DE OCURRENCIAS: " << iValor << std::endl;

	return iValor;
}


//static void saveSqlMap(const std::map<std::string, int>& mapOcurrencias)
//{
//	for (const auto& par : mapOcurrencias)
//	{
//		std::cout << "Lenguaje de programación: " << par.first
//			<< ", Número de ocurrencias: " << par.second << std::endl;
//	}
//}

//void validateParameters(std::string &sRutaProyecto, std::string &sLenguaje, std::string &sTipoMigracion, std::string &sNumColaboradores) 
//{
//	bool bParametrosCorrectos = false;
//
//	while (!bParametrosCorrectos)
//	{
//		std::cout << "Ingrese la ruta del proyecto: ";
//		std::cin >> sRutaProyecto;
//
//		std::cout << "Ingrese el lenguaje: ";
//		std::cin >> sLenguaje;
//
//		std::cout << "Ingrese el tipo de migración (mig o vul): ";
//		std::cin >> sTipoMigracion;
//
//		std::cout << "Ingrese el número de colaboradores: ";
//		std::cin >> sNumColaboradores;
//
//		// Validar los parámetros de entrada
//		if (!sRutaProyecto.empty() && !sLenguaje.empty() && (sTipoMigracion == "mig" || sTipoMigracion == "vul") && atoi(sNumColaboradores.c_str()) > 0) 
//		{
//			bParametrosCorrectos = true;
//		}
//		else 
//		{
//			std::cout << "Los parámetros ingresados son incorrectos. Por favor, inténtelo nuevamente." << std::endl;
//		}
//	}
//}


//void validateParametersAll(std::string& sRutaProyecto, std::string& sTipoMigracion, std::string& sNumColaboradores)
//{
//	bool bParametrosCorrectos = false;
//
//	std::cout << "-----------------------------------------------------" << std::endl;
//	std::cout << " Herramienta de Migración y Vulnerabilidades con IA  " << std::endl;
//	std::cout << "    Favor de capturar la información solicitada.     " << std::endl;
//	std::cout << "_____________________________________________________" << std::endl;
//	std::cout << "" << std::endl;
//
//	while (!bParametrosCorrectos)
//	{
//		std::cout << "Ingrese la ruta del proyecto: ";
//		std::cin >> sRutaProyecto;
//
//		std::cout << "Ingrese el tipo de migración (mig o vul): ";
//		std::cin >> sTipoMigracion;
//
//		std::cout << "Ingrese el número de colaboradores: ";
//		std::cin >> sNumColaboradores;
//
//		// Validar los parámetros de entrada
//		if (!sRutaProyecto.empty() && (sTipoMigracion == "mig" || sTipoMigracion == "vul") && atoi(sNumColaboradores.c_str()) > 0)
//		{
//			bParametrosCorrectos = true;
//		}
//		else
//		{
//			std::cout << "Los parámetros ingresados son incorrectos. Por favor, inténtelo nuevamente." << std::endl;
//		}
//	}
//}
