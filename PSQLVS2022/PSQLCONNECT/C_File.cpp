/**
	Empresa:		Coppel SA
	Archivos:		C_File.h y C_File.cpp
	Autor:			Jesús Enrique Arce Pérez
	Correo:			jesus.arce@coppel.com
	Fecha:			2017/06/23
	Versión:		1.0.0.0
*/

#include "C_File.h"

C_File::C_File()
{
}

C_File::~C_File()
{
}

short C_File::saveLog(char *cPathLog, char *cTextLog, bool bWithDateLeft)
{
	if (strlen(cPathLog) > _MAX_PATH)
	{
		return EFILE_INVALID_PATH;
	}

	if (strlen(cTextLog) < EFILE_SIZETEXTLOG)
	{
		char cLog[EFILE_SIZETEXTLOG] = { 0 };

		if (bWithDateLeft)
		{
			C_SO eSO;

			sprintf_s(cLog, sizeof(cLog), "[%s] - %s", eSO.getCurrentDateTime().c_str(), cTextLog);
		}
		else
		{
			sprintf_s(cLog, sizeof(cLog), "%s", cTextLog);
		}

		ofstream log(cPathLog, ios_base::app | ios_base::out);

		log << cLog;

		log.close();

		return EFILE_WRITELOGSUCCESS;
	}
	else
	{
		return EFILE_SIZETEXTLOGOVERFLOW;
	}
}

short C_File::saveLog(char *cPathLog, CString sTextLog, bool bWithDateLeft)
{
	if (strlen(cPathLog) > _MAX_PATH)
	{
		return EFILE_INVALID_PATH;
	}

	if (sTextLog.GetLength() < EFILE_SIZETEXTLOG)
	{
		char cLog[EFILE_SIZETEXTLOG] = { 0 };

		if (bWithDateLeft)
		{
			C_SO eSO;

			sprintf_s(cLog, EFILE_SIZETEXTLOG, "[%s] - %S", eSO.getCurrentDateTime().c_str(), sTextLog);
		}
		else
		{
			sprintf_s(cLog, EFILE_SIZETEXTLOG, "%S", sTextLog);
		}

		ofstream log(cPathLog, ios_base::app | ios_base::out);

		log << cLog;

		log.close();

		return EFILE_WRITELOGSUCCESS;
	}
	else
	{
		return EFILE_SIZETEXTLOGOVERFLOW;
	}
}

short C_File::saveTextInFile(const char *cPathFile, string sText, bool bWithDateLeft)
{
	ofstream file(cPathFile, ios_base::app | ios_base::out);

	if (file.good() && file.is_open())
	{
		if (bWithDateLeft)
		{
			C_SO eSO;

			file << eSO.getCurrentDateTime().c_str();
		}

		file << " - ";

		sText.append("\n");

		file << sText.c_str();

		file.close();

		return EFILE_WRITELOGSUCCESS;
	}

	return EFILE_INVALID_PATH;
}