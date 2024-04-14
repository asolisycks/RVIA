#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <date/date.h>
#include <errno.h>
#include <filesystem>
#include <format>  // C++20
#include <fstream>  // Para manejar archivos
#include <io.h>
#include <iomanip>
#include <iostream>
#include <locale>
#include <map>
#include <openssl/evp.h>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <Windows.h>

#include "C_PostgreSQL.hpp"

#define PHP_MIGRACION_META					96
#define PHP_VULNERABILIDADES_META			176
#define JQUERY_MIGRACION_META				57
#define SQL_VULNERABILIDADES_META			40
#define SQL_MIGRACION_META					298
#define JAVA_VULNERABILIDADES_META			279
#define JAVA_MIGRACION_META					66
#define C_MIGRACION_META					132
#define C_VULNERABILIDADES_META				224
#define CSHARP_MIGRACION_META				62
#define CSHARP_VULNERABILIDADES_META		124
#define CPP_MIGRACION_META					132
#define CPP_VULNERABILIDADES_META			224
#define PYTHON_MIGRACION_META				71
#define PYTHON_VULNERABILIDADES_META		63
#define CODEIGNITER_MIGRACION_META			260
#define CS_MIGRACION_META					62
#define ANGULAR_MIGRACION_META				120
#define COLDFUSION_VULNERABILIDADES_META	46
#define COLDFUSION_MIGRACIONES_META			43
#define JAVASCRIPT_MIGRACION_META			57
#define JAVASCRIPT_VULNERABILIDADES_META	40
#define TYPESCRIPT_MIGRACION_META			57
#define TYPESCRIPT_VULNERABILIDADES_META	40
#define VB_MIGRACION_META					132
#define VB_VULNERABILIDADES_META			224
#define RUBY_MIGRACION_META					71
#define RUBY_VULNERABILIDADES_META			63
#define SWIFT_MIGRACION_META				71
#define SWIFT_VULNERABILIDADES_META			63
#define GO_MIGRACION_META					71
#define GO_VULNERABILIDADES_META			63
#define PERL_MIGRACION_META					71
#define PERL_VULNERABILIDADES_META			63
#define RUST_MIGRACION_META					71
#define RUST_VULNERABILIDADES_META			63
#define KOTLIN_MIGRACION_META				71
#define KOTLIN_VULNERABILIDADES_META		63
#define SCALA_MIGRACION_META				71
#define SCALA_VULNERABILIDADES_META			63

/*#define ERROR_FILE_NOT_FOUND				-1
#define ERROR_PATH_NOT_FOUND				-2
#define ERROR_ACCESS_DENIED					-3
#define ERROR_INVALID_TOKEN					-4
#define ERROR_INVALID_PARAMETER				-5*/

using namespace date;
using namespace std::chrono;
using namespace std::chrono_literals;

enum ResultadoValidacion
{
	Exito,
	ErrorAperturaArchivo,
	ErrorTokenNoCoincide,
	ErrorTokenExpirado
};

struct Programa
{
	std::string sLenguaje;
	int iArchivos;
	int iLineasBlanco;
	int iComentarios;
	int iLineasCodigo;

	Programa() : sLenguaje(""), iArchivos(0), iLineasBlanco(0), iComentarios(0), iLineasCodigo(0) {}
};

struct Metricas
{
	std::string sLenguaje;
	int iMigracion;
	int iVulnerabilidad;

	Metricas() : sLenguaje(""), iMigracion(0), iVulnerabilidad(0) {}
};


#pragma once
class CIA
{
public:

	CIA(std::string sNombreProyecto, const long lNumColaborador);
	~CIA();

	C_PostgreSQL	objPSQL;
	C_Utils			objUtils;
	Programa		objPrograma;
	Metricas		objMetricas;

	long generarIDProyecto();
	ResultadoValidacion esTokenValidoDB(const long lEmpleado, std::string sTokenProporcionado, const int iDataBase);
	
	void menu();
	void printProgramInfo();
	int  pathFileCreatedCSV(std::string sPathFileCreatedCSV);

	void setColor(int color);
	int  getConsoleWidth();
	void printCentered(std::string text);
	bool esNumeroNatural(std::string str);
	bool soloCaracteres(const std::string& str);
	std::wstring convertStringToWString(const std::string& str);
	std::string convertWStringToString(const std::wstring& wstr);
	bool validateExtension(std::string extension);
	std::string getFileNameWithoutExtension(std::string fileName);
	void eliminarArchivo(const std::string& sRutaArchivo);
	int obtieneTotales(char* cPathRoot, char* cPathTotales, std::vector<std::string>& vcLenguajes);
	int getTotals(char* cPathRoot, char* cPathTotales);
	std::map<std::string, int> obtieneSentenciasSQLEnMapa(char* cRootPath, const long lIdProyecto, const int iDataBase);
	std::map<std::string, int> obtieneFuncionesObsoletasEnMapa(char* cRootPath, const long lIdProyecto, const int iDataBase);
	int obtieneBITO(char* cRootPath, char* cBito);

	std::set<std::string> cargarArchivosProcesados(std::string sRutaArchivoProcesados);
	void guardarArchivosProcesados(std::string sRutaArchivoProcesados, const std::set<std::string>& archivosProcesados);
	int procesarArchivo(const std::string& sNombreArchivo, char* cExtension, std::string& sComentariosBito);
	int ejecutaProcesoIA(const std::string& sRuta, const long lIdProyecto, const int iDatabase);
	int procesarConBITO(char* cRootPath, char* cBito);
	int calcularFechaFinProyectoCaptura(char* cRootPath, std::string sLenguaje, int& iTotalDeOcurrencias, int& iNumColaboradores, int &iOcurrenciasPorLenguaje, int& iTotalArchivos);
	std::chrono::year_month_day get_end_date(std::chrono::year_month_day start, days length);
	int calcularFechaFinal(int iBusiness_days, const std::string sFechaArg, std::string& sFechaInicial, std::string& sFechaFinal, int& iTotalDias, int& iTtotalDiasInhabiles, std::string& sFechaFinalLunVie);
	int calcular(std::string cRootPath, int& iTotalArchivos, int& iTotalOcurrencias, int& iOcurrenciasPorSemanaPorColaborador, int& iNumeroDeColaboradores, const std::string sLenguaje);
	int calcularFinDeProyectoMap(const std::map<std::string, int>& vecMetaSemanal, const std::map<std::string, int>& mapSentencias, const std::map<std::string, int>& mapDeprecated, std::string sRootPath, int& iTotalArchivos, int& iNumeroDeColaboradores, const int iHigh, const int iMedium, const int iLow, std::string sNombreProyecto, const long lIdProyecto, const int iDataBase);
	int calcularFinDeProyectoVecMap(const std::vector<Metricas>& vecMetaSemanal, const std::map<std::string, int>& mapSentencias, const std::map<std::string, int>& mapDeprecated, const std::vector<Programa> vcProgramas, std::string sRootPath, int& iNumeroDeColaboradores, const int iHigh, const int iMedium, const int iLow, std::string sNombreProyecto, const long lIdProyecto, const std::string sTipoDeMigracion, const int iDataBase);
	int crearConteoPorCoincidencia();
	int crearConteoPorCoincidenciaObsoleto();
	void search_sql_in_file(const std::string& file_path, std::map<std::string, int>& mapSentencias, const long lIdProyecto, const int iDataBase);
	int search_deprecated_in_file(const std::string& file_path, std::map<std::string, int>& mapDeprecated, const long lIdProyecto, const int iDataBase);	
	void execute_bito_in_file(const std::string& file_path);
	int search_files_Sql_in_directory(const std::filesystem::path& directory, std::map<std::string, int>& mapSentencias, const long lIdProyecto, const int iDataBase);
	int search_files_deprecated_in_directory(const std::filesystem::path& directory, std::map<std::string, int>& mapDeprecated, const long lIdProyecto, const int iDataBase);
	double calcularFechaFinProyecto(int& iTotalOcurrencias, int& iOcurrenciasPorSemanaPorColaborador, int& iNumeroDeColaboradores);
	int quitarComentariosBito(std::string sFile, std::string& sPathFileBitoTxt);
	bool validarArchivoBito(const std::string& sRutaArchivo, const std::string& sRutaArchivoCSV);
	int contarArchivosEnVector(const std::filesystem::path& directory, const std::vector<std::string>& vcLenguajes);
	int contarArchivos(const std::filesystem::path& directory, const std::string& sLenguaje);
	void createCSV(const std::string& path, const std::string& filename);
	int lintPHPFile(const std::string& sNombreArchivo, std::string& sContenidoTxtLint);
	std::string obtenerFechaArchivos(std::string sNombreArchivo);
	std::string generarArchivoBito(const std::string& sNombreArchivo, const std::string& sLenguaje);
	int validarExisteBito(const std::string& sRuta);
	bool validarExisteEmpleadoTB(long &lNumColaborador, long& lRespuesta, const int iDataBase);
	bool registrarSentencias(std::string sArchivo, int iLinea, std::string sSentencia, const long lIdProyecto, const int iDataBase);
	bool registrarObsoletos(std::string sArchivo, int iLinea, std::string sObsoleto, const long lIdProyecto, const int iDataBase);
	std::string obtenerTokenDB(const long lEmpleado, std::string sToken, std::string& sTokenDB, std::string& sExpiraDB, const int iDataBase);
	bool registrarTotalesCheckmarx(const long lIdProyecto, const std::string sProjectName, int iHigh, int iMedium, int iLow, const int iDataBase);
	bool registrarItemsCheckmarx(const long lIdProyecto, const std::string sProjectName, int iId, std::string dDetectionDate, std::string sDirectLink, std::string sQueryName, std::string sSourceFolder, std::string sSourceFilename, std::string sSourceLine, std::string sSourceObject, std::string sDestinationFolder, std::string sDestinationFilename, std::string sDestinationLine, std::string sDestinationObject, std::string sResultState, std::string sSeverity, std::string sResultSeverity, const int iDataBase);
	bool registrarFechasDeProyecto(const long lIdProyecto, const std::string sProjectName, std::string sLanguageName, int iOcurrencias, int iXSemana, int iCantColab, int iTotSem, int iTotDias, int iTotHoras, std::string sFechaIni, std::string sFechaFin, int iDiasLunVie, std::string sFechaLunVie, const int iDataBase);
	bool registrarTotalesProyectos(const long lIdProyecto, const std::string sProjectName, std::string sLenguaje, const int iArchivos, const int iLineasBlanco, const int iComentarios, const int iLineasCodigo, const int iDataBase);
	bool registrarControlDeProyectos(const long lIdProyecto, const std::string sProjectName, const int iFlagConIA, const int iDataBase);
	bool generarArchivosPrompt(std::string sPrompt, std::string sLenguaje);
	std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv);
	bool getDataFileINI(std::string& decrypted_ipname, std::string& decrypted_dbname, std::string& decrypted_dbport, std::string& decrypted_dbuser, std::string& decrypted_dbpass, const int iDataBase);
	std::vector<std::string> split(const std::string& s);
	std::string getFilenameSinCheckmarx(const std::string& filePath);
	bool getDataFromCheckmarx(const long lIdProyecto, std::string sFileX, int& iHigh, int& iMedium, int& iLow, int& iDataBase);
	std::string obtenerPrompt(const std::string sNomCliente, std::string sLenguaje, std::string sModelo, const int iDataBase);
	std::vector<Programa> getFileTotals(const std::string sFile);
	std::vector<Metricas> getMetricas(const std::vector<std::string>& vcLenguajes, std::string sTipo, const int iDataBase);

	bool registrarComentariosProyectoIA(const long lIdProyecto, const std::string sProjectName, const std::string sNombreArchivoPhp, const std::string sRespuestaSystemLinterOriginal, const std::string sBufferIniBito, const std::string sBufferFinBito, const std::string sExecutionTimeBito, const std::string sExecutionTimeInMinutes, const std::string sRespuestaSystemLinterNvo, const std::string sContenidoTxtLint, const std::string sComentariosBito, const int iDataBase);

	std::string sanitizarCadenas(const std::string& input);

protected:
	std::string sNomProyecto;
	// Generar una clave e IV aleatorios
	std::string key = "jasrkey";  // Reemplazar con la generación de clave real
	std::string iv = "jasriv";   // Reemplazar con la generación de IV real

	long		lColaborador;

};
