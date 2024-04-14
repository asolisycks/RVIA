/**
	Empresa:		Coppel SA
	Archivos:		C_File.h y C_File.cpp
	Autor:			Jesús Enrique Arce Pérez
	Correo:			jesus.arce@coppel.com
	Fecha:			2017/06/23
	Versión:		1.0.0.0

	Descripción:	C_File contiene métodos relacionados con la generación de archivos.
*/

#ifndef C_FILE_H
#define C_FILE_H

#include <stdio.h>
#include <sstream>
#include <io.h>
#include <fstream>
#include <afxwin.h>

#include "C_SO.h"

using namespace std;

#define EFILE_SIZETEXTLOG			800000

#define EFILE_INVALID_PATH			400
#define EFILE_SIZETEXTLOGOVERFLOW	401
#define EFILE_WRITELOGSUCCESS		0

class C_File
{
public:
	C_File();
	~C_File();

	/*
	====================================================================================================================================
	Método:			saveLog()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/23
	Descripción:	Método que graba en Log los caracteres especificados en el parámetro [cTextLog].

	Parámetros:
		* cPathLog							- Ruta completa del archivo donde se guardará el Log.
		* cTextLog							- Variable con el texto a guardar.
		* bWithDateLeft						- Determina si se guardará la fecha en la parte izquierda del texto.

	Los retornos posibles son:
		* EFILE_INVALID_PATH				- La longitud de la ruta es inválida, Windows soporta solo rutas de 260 caracteres.
		* EFILE_SIZETEXTLOGOVERFLOW			- El texto sobrepasa el límite permitido, la definicion EFILE_SIZETEXTLOG indica el límite.
		* EFILE_WRITELOGSUCCESS				- El log se escribió con éxito.
	====================================================================================================================================
	*/
	short saveLog(char *cPathLog, char *cTextLog, bool bWithDateLeft = false);

	/*
	====================================================================================================================================
	Método:			saveLog() -- Sobrecarga
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/23
	Descripción:	Método que graba en Log los caracteres especificados en el parámetro [sTextLog].

	Parámetros:
	* cPathLog								- Ruta completa del archivo donde se guardará el Log.
	* sTextLog								- Variable con el texto a guardar.
	* bWithDateLeft							- Determina si se guardará la fecha en la parte izquierda del texto.

	Los retornos posibles son:
	* EFILE_INVALID_PATH					- La longitud de la ruta es inválida, Windows soporta solo rutas de 260 caracteres.
	* EFILE_SIZETEXTLOGOVERFLOW				- El texto sobrepasa el límite permitido, la definicion EFILE_SIZETEXTLOG indica el límite.
	* EFILE_WRITELOGSUCCESS					- El log se escribió con éxito.
	====================================================================================================================================
	*/
	short saveLog(char *cPathLog, CString sTextLog, bool bWithDateLeft = false);

	/*
	====================================================================================================================================
	Método:			saveTextInFile()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/09/01
	Descripción:	Método que graba en un archivo plano los caracteres especificados en el parámetro [sText].

	Parámetros:
	* cPathFile								- Ruta completa del archivo donde se guardará el archivo.
	* sText									- Variable con el texto a guardar.
	* bWithDateLeft							- Determina si se guardará la fecha en la parte izquierda del texto.

	Los retornos posibles son:
	* EFILE_INVALID_PATH					- La longitud de la ruta es inválida, Windows soporta solo rutas de 260 caracteres.
	* EFILE_WRITELOGSUCCESS					- El texto se escribió con éxito.
	====================================================================================================================================
	*/
	short saveTextInFile(const char *cPathFile, string sText, bool bWithDateLeft);
};

#endif //C_FILE_H