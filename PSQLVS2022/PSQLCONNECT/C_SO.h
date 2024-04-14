/**
	Empresa:		Coppel SA
	Archivos:		C_SO.h y C_SO.cpp
	Autor:			Jes�s Enrique Arce P�rez
	Correo:			jesus.arce@coppel.com
	Fecha:			2017/06/22
	Versi�n:		1.0.0.0

	Descripci�n:	C_SO contiene m�todos relacionados con funciones del sistema operativo.
*/

#ifndef C_SO_H
#define C_SO_H

#include <stdio.h>
#include <string>
#include <time.h>
#include <afxwin.h>
#include "C_Utils.h"

#define STRING_EMPTY						""

#define ESO_VERSION_WINDOWS_UNKNOW			-1
#define ESO_VERSION_WINDOWS_SERVER			0
#define ESO_VERSION_WINDOWS_XP				1
#define ESO_VERSION_WINDOWS_VISTA			2
#define ESO_VERSION_WINDOWS_7				3
#define ESO_VERSION_WINDOWS_8				4
#define ESO_VERSION_WINDOWS_81				5

#define ESO_DATETIME_DDMMYYYY_SL			0
#define ESO_DATETIME_DDMMYYYY_SC			1
#define ESO_DATETIME_DDMMMMYYYY_SL			2
#define ESO_DATETIME_DDMMMMYYYY_SC			3
#define ESO_DATETIME_YYYYMMMMDD_SL			4
#define ESO_DATETIME_YYYYMMMMDD_SC			5
#define ESO_DATETIME_YYYYMMDD_SL			6
#define ESO_DATETIME_YYYYMMDD_SC			7
#define ESO_DATETIME_HHMMSS					8
#define ESO_DATETIME_DDMMYYYY_HHMMSS_SL		9
#define ESO_DATETIME_DDMMYYYY_HHMMSS_SC		10
#define ESO_DATETIME_YYYYMMDD_HHMMSS_SL		11
#define ESO_DATETIME_YYYYMMDD_HHMMSS_SC		12
#define ESO_DATETIME_DDMMMMYYYY_HHMMSS_SL	13
#define ESO_DATETIME_DDMMMMYYYY_HHMMSS_SC	14
#define ESO_DATETIME_YYYYMMMMDD_HHMMSS_SL	15
#define ESO_DATETIME_YYYYMMMMDD_HHMMSS_SC	16
#define ESO_DATETIME_DAY					17
#define ESO_DATETIME_MONTH					18
#define ESO_DATETIME_SHORT_MONTH			19
#define ESO_DATETIME_LARGE_MONTH			20
#define ESO_DATETIME_YEAR					21
#define ESO_DATETIME_HOUR					22
#define ESO_DATETIME_MINUTE					23
#define ESO_DATETIME_SECONDS				24

using namespace std;

class C_SO
{
public:
	C_SO();
	~C_SO();

	/*
	====================================================================================================================================
	M�todo:			getCurrentSO()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/22
	Descripci�n:	M�todo que retorna la versi�n del Sistema Operativo actual.

	Los retornos posibles son:
		* SO_VERSION_WINDOWS_SERVER			- Servidor de Windows.
		* SO_VERSION_WINDOWS_XP				- Windows XP.
		* SO_VERSION_WINDOWS_VISTA			- Windows Vista.
		* SO_VERSION_WINDOWS_7				- Windows 7.
		* SO_VERSION_WINDOWS_8				- Windows 8.
		* SO_VERSION_WINDOWS_81				- Windows 8.1.
		* SO_VERSION_WINDOWS_UNKNOW			- Sistema Operativo de Windows desconocido.
	====================================================================================================================================
	*/
	/* Funci�n deshabilitada en Versi�n B15 */
	//short getCurrentSO();

	/*
	====================================================================================================================================
	M�todo:			getCurrentHourInSeconds()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/22
	Descripci�n:	M�todo que retorna hora actual del sistema en segundos.
	====================================================================================================================================
	*/
	int getCurrentHourInSeconds();

	/*
	====================================================================================================================================
	M�todo:			calculateProcessingTime()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/22
	Descripci�n:	M�todo que retorna la diferencia en minutos desde una hora inicial (en segundos)
					hasta la hora actual.

	Par�metros:
		* iHourInitInSeconds				- Hora inicial en segundos.

	Retorno:
		* La variable de retorno es de tipo FLOAT y representa los minutos transcurridos desde la hora inicial
		  a la actual. Ejemplo:	12.0352 minutos
	====================================================================================================================================
	*/
	float calculateProcessingTime(int iHourInitInSeconds);

	/*
	====================================================================================================================================
	M�todo:			getCurrentDateTime()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/26
	Descripci�n:	M�todo que retorna en formato de texto la fecha y hora actual del sistema.

	Par�metros:
		* shFormat							- Determina el formato de salida de la Fecha/Hora.

	Retorno:
		* Cadena de texto con la fecha actual del sistema. El formato depende del par�metro de entrada [shFormat].

	Los retornos posibles son:
		* ESO_DATETIME_DDMMYYYY_SL			- Ejemplo: 26/06/2017
		* ESO_DATETIME_DDMMYYYY_SC			- Ejemplo: 26-06-2017
		* ESO_DATETIME_DDMMMMYYYY_SL		- Ejemplo: 26/JUN/2017
		* ESO_DATETIME_DDMMMMYYYY_SC		- Ejemplo: 26-JUN-2017
		* ESO_DATETIME_YYYYMMMMDD_SL		- Ejemplo: 2017/JUN/26
		* ESO_DATETIME_YYYYMMMMDD_SC		- Ejemplo: 2017-JUN-26
		* ESO_DATETIME_YYYYMMDD_SL			- Ejemplo: 2017/06/26
		* ESO_DATETIME_YYYYMMDD_SC			- Ejemplo: 2017-06-26
		* ESO_DATETIME_HHMMSS				- Ejemplo: 11:45:50
		* ESO_DATETIME_DDMMYYYY_HHMMSS_SL	- Ejemplo: 26/06/2017 11:45:50
		* ESO_DATETIME_DDMMYYYY_HHMMSS_SC	- Ejemplo: 26-06-2017 11:45:50
		* ESO_DATETIME_YYYYMMDD_HHMMSS_SL	- Ejemplo: 2017/06/26 11:45:50
		* ESO_DATETIME_YYYYMMDD_HHMMSS_SC	- Ejemplo: 2017-06-26 11:45:50
		* ESO_DATETIME_DDMMMMYYYY_HHMMSS_SL	- Ejemplo: 26/JUN/2017 11:45:50
		* ESO_DATETIME_DDMMMMYYYY_HHMMSS_SC	- Ejemplo: 26-JUN-2017 11:45:50
		* ESO_DATETIME_YYYYMMMMDD_HHMMSS_SL	- Ejemplo: 2017/JUN/26 11:45:50
		* ESO_DATETIME_YYYYMMMMDD_HHMMSS_SC	- Ejemplo: 2017-JUN-26 11:45:50
		* ESO_DATETIME_DAY					- Ejemplo: 26
		* ESO_DATETIME_MONTH				- Ejemplo: 06
		* ESO_DATETIME_SHORT_MONTH			- Ejemplo: JUN
		* ESO_DATETIME_LARGE_MONTH			- Ejemplo: JUNIO
		* ESO_DATETIME_YEAR					- Ejemplo: 2017
		* ESO_DATETIME_HOUR					- Ejemplo: 11
		* ESO_DATETIME_MINUTE				- Ejemplo: 45
		* ESO_DATETIME_SECONDS				- Ejemplo: 50
	====================================================================================================================================
	*/
	string getCurrentDateTime(const short shFormat = ESO_DATETIME_DDMMYYYY_HHMMSS_SL);

	/*
	====================================================================================================================================
	M�todo:			getNameMonth()
	Autor:			Enrique Arce - Desarrollo de Sistemas Especiales II
	Fecha:			2017/06/22
	Descripci�n:	M�todo que retorna el mes especificado en el primer par�metro en formato largo o corto,
					dependiendo del segundo par�metro.

	Par�metros:
		* iMonth							- N�mero del mes (1-12).
		* bLargeName						- Determina si el formato de retorno ser� el mes en formato largo o corto.

	Retorno:
		* Un ejemplo de retorno ser�a el mes 6. El m�todo retornar� JUN o JUNIO dependiendo del par�metro [bLargeName].
	====================================================================================================================================
	*/
	string getNameMonth(const short iMonth, bool bLargeName);
};

#endif //C_SO_H