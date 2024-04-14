/**
	Empresa:		Coppel SA
	Archivos:		C_File.h y C_File.cpp
	Autor:			Jes�s Enrique Arce P�rez
	Correo:			jesus.arce@coppel.com
	Fecha:			2017/06/23
	Versi�n:		1.0.0.0

	Descripci�n:	C_File contiene m�todos relacionados con la generaci�n de archivos.
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
	M�todo:			saveLog()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/23
	Descripci�n:	M�todo que graba en Log los caracteres especificados en el par�metro [cTextLog].

	Par�metros:
		* cPathLog							- Ruta completa del archivo donde se guardar� el Log.
		* cTextLog							- Variable con el texto a guardar.
		* bWithDateLeft						- Determina si se guardar� la fecha en la parte izquierda del texto.

	Los retornos posibles son:
		* EFILE_INVALID_PATH				- La longitud de la ruta es inv�lida, Windows soporta solo rutas de 260 caracteres.
		* EFILE_SIZETEXTLOGOVERFLOW			- El texto sobrepasa el l�mite permitido, la definicion EFILE_SIZETEXTLOG indica el l�mite.
		* EFILE_WRITELOGSUCCESS				- El log se escribi� con �xito.
	====================================================================================================================================
	*/
	short saveLog(char *cPathLog, char *cTextLog, bool bWithDateLeft = false);

	/*
	====================================================================================================================================
	M�todo:			saveLog() -- Sobrecarga
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/23
	Descripci�n:	M�todo que graba en Log los caracteres especificados en el par�metro [sTextLog].

	Par�metros:
	* cPathLog								- Ruta completa del archivo donde se guardar� el Log.
	* sTextLog								- Variable con el texto a guardar.
	* bWithDateLeft							- Determina si se guardar� la fecha en la parte izquierda del texto.

	Los retornos posibles son:
	* EFILE_INVALID_PATH					- La longitud de la ruta es inv�lida, Windows soporta solo rutas de 260 caracteres.
	* EFILE_SIZETEXTLOGOVERFLOW				- El texto sobrepasa el l�mite permitido, la definicion EFILE_SIZETEXTLOG indica el l�mite.
	* EFILE_WRITELOGSUCCESS					- El log se escribi� con �xito.
	====================================================================================================================================
	*/
	short saveLog(char *cPathLog, CString sTextLog, bool bWithDateLeft = false);

	/*
	====================================================================================================================================
	M�todo:			saveTextInFile()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/09/01
	Descripci�n:	M�todo que graba en un archivo plano los caracteres especificados en el par�metro [sText].

	Par�metros:
	* cPathFile								- Ruta completa del archivo donde se guardar� el archivo.
	* sText									- Variable con el texto a guardar.
	* bWithDateLeft							- Determina si se guardar� la fecha en la parte izquierda del texto.

	Los retornos posibles son:
	* EFILE_INVALID_PATH					- La longitud de la ruta es inv�lida, Windows soporta solo rutas de 260 caracteres.
	* EFILE_WRITELOGSUCCESS					- El texto se escribi� con �xito.
	====================================================================================================================================
	*/
	short saveTextInFile(const char *cPathFile, string sText, bool bWithDateLeft);
};

#endif //C_FILE_H