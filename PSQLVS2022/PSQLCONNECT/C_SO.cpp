#include "C_SO.h"
//#include <VersionHelpers.h>

C_SO::C_SO()
{
}

C_SO::~C_SO()
{
}

//short C_SO::getCurrentSO()
//{
//	short shWindowsVersion = ESO_VERSION_WINDOWS_UNKNOW;
//
//	if (IsWindowsXPOrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_XP;
//	}
//
//	if (IsWindowsXPSP1OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_XP;
//	}
//
//	if (IsWindowsXPSP2OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_XP;
//	}
//
//	if (IsWindowsXPSP3OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_XP;
//	}
//
//	if (IsWindowsVistaOrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_VISTA;
//	}
//
//	if (IsWindowsVistaSP1OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_VISTA;
//	}
//
//	if (IsWindowsVistaSP2OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_VISTA;
//	}
//
//	if (IsWindows7OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_7;
//	}
//
//	if (IsWindows7SP1OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_7;
//	}
//
//	if (IsWindows8OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_8;
//	}
//
//	if (IsWindows8Point1OrGreater())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_81;
//	}
//
//	if (IsWindowsServer())
//	{
//		shWindowsVersion = ESO_VERSION_WINDOWS_SERVER;
//	}
//
//	return shWindowsVersion;
//}

int C_SO::getCurrentHourInSeconds()
{
	int iHourInit	= 0;
	int iMinInit	= 0;
	int iSecInit	= 0;
	
	time_t tTiempo;
	struct tm *tHourInit;

	tTiempo		= time(NULL);
	tHourInit	= localtime(&tTiempo);

	iHourInit	= tHourInit->tm_hour;
	iMinInit	= tHourInit->tm_min;
	iSecInit	= tHourInit->tm_sec;

	return (iHourInit * 3600) + (iMinInit * 60) + iSecInit;
}

float C_SO::calculateProcessingTime(int iHourInitInSeconds)
{
	int iTotalSecondsEnd	= 0;
	int iDifTimeSeconds		= 0;
	float fDifTimeMinutes	= 0.0F;

	iTotalSecondsEnd	= getCurrentHourInSeconds();
	iDifTimeSeconds		= iTotalSecondsEnd - iHourInitInSeconds;
	fDifTimeMinutes		= ((float)iDifTimeSeconds / (float)60);

	return fDifTimeMinutes;
}

string C_SO::getCurrentDateTime(const short shFormat)
{
	//CString sDateTime = L"";
	C_Utils u;
	string	sDateTime = STRING_EMPTY;

	SYSTEMTIME timeStamp;
	GetLocalTime(&timeStamp);

	switch (shFormat)
	{
	case ESO_DATETIME_DDMMYYYY_SL:
		sDateTime.append(u.stringFormat("%02d-%02d-%04d", timeStamp.wDay, timeStamp.wMonth, timeStamp.wYear).c_str());
		break;
	case ESO_DATETIME_DDMMYYYY_SC:
		sDateTime.append(u.stringFormat("%02d-%02d-%04d", timeStamp.wDay, timeStamp.wMonth, timeStamp.wYear).c_str());
		break;
	case ESO_DATETIME_DDMMMMYYYY_SL:
		sDateTime.append(u.stringFormat("%02d/%s/%04d", timeStamp.wDay, getNameMonth(timeStamp.wMonth, false).c_str(), timeStamp.wYear).c_str());
		break;
	case ESO_DATETIME_DDMMMMYYYY_SC:
		sDateTime.append(u.stringFormat("%02d-%s-%04d", timeStamp.wDay, getNameMonth(timeStamp.wMonth, false).c_str(), timeStamp.wYear).c_str());
		break;
	case ESO_DATETIME_YYYYMMMMDD_SL:
		sDateTime.append(u.stringFormat("%02d/%s/%04d", timeStamp.wYear, getNameMonth(timeStamp.wMonth, false).c_str(), timeStamp.wDay).c_str());
		break;
	case ESO_DATETIME_YYYYMMMMDD_SC:
		sDateTime.append(u.stringFormat("%02d-%s-%04d", timeStamp.wYear, getNameMonth(timeStamp.wMonth, false).c_str(), timeStamp.wDay).c_str());
		break;
	case ESO_DATETIME_YYYYMMDD_SL:
		sDateTime.append(u.stringFormat("%02d/%02d/%04d", timeStamp.wYear, timeStamp.wMonth, timeStamp.wDay).c_str());
		break;
	case ESO_DATETIME_YYYYMMDD_SC:
		sDateTime.append(u.stringFormat("%02d-%02d-%04d", timeStamp.wYear, timeStamp.wMonth, timeStamp.wDay).c_str());
		break;
	case ESO_DATETIME_HHMMSS:
		sDateTime.append(u.stringFormat("%02d%02d%02d", timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_DDMMYYYY_HHMMSS_SL:
		sDateTime.append(u.stringFormat("%02d/%02d/%04d %02d:%02d:%02d", timeStamp.wDay, timeStamp.wMonth, timeStamp.wYear, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_DDMMYYYY_HHMMSS_SC:
		sDateTime.append(u.stringFormat("%02d-%02d-%04d %02d:%02d:%02d", timeStamp.wDay, timeStamp.wMonth, timeStamp.wYear, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_YYYYMMDD_HHMMSS_SL:
		sDateTime.append(u.stringFormat("%04d/%02d/%02d %02d:%02d:%02d", timeStamp.wYear, timeStamp.wMonth, timeStamp.wDay, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_YYYYMMDD_HHMMSS_SC:
		sDateTime.append(u.stringFormat("%04d-%02d-%02d %02d:%02d:%02d", timeStamp.wYear, timeStamp.wMonth, timeStamp.wDay, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_DDMMMMYYYY_HHMMSS_SL:
		sDateTime.append(u.stringFormat("%02d/%02d/%04d %02d:%02d:%02d", timeStamp.wDay, getNameMonth(timeStamp.wMonth, false), timeStamp.wYear, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_DDMMMMYYYY_HHMMSS_SC:
		sDateTime.append(u.stringFormat("%02d-%02d-%04d %02d:%02d:%02d", timeStamp.wDay, getNameMonth(timeStamp.wMonth, false), timeStamp.wYear, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_YYYYMMMMDD_HHMMSS_SL:
		sDateTime.append(u.stringFormat("%04d/%02d/%02d %02d:%02d:%02d", timeStamp.wYear, getNameMonth(timeStamp.wMonth, false), timeStamp.wDay, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_YYYYMMMMDD_HHMMSS_SC:
		sDateTime.append(u.stringFormat("%04d-%02d-%02d %02d:%02d:%02d", timeStamp.wYear, getNameMonth(timeStamp.wMonth, false), timeStamp.wDay, timeStamp.wHour, timeStamp.wMinute, timeStamp.wSecond).c_str());
		break;
	case ESO_DATETIME_DAY:
		sDateTime.append(u.stringFormat("%02d", timeStamp.wDay).c_str());
		break;
	case ESO_DATETIME_MONTH:
		sDateTime.append(u.stringFormat("%02d", timeStamp.wMonth).c_str());
		break;
	case ESO_DATETIME_SHORT_MONTH:
		sDateTime.append(u.stringFormat("%s", getNameMonth(timeStamp.wMonth, false).c_str()).c_str());
		break;
	case ESO_DATETIME_LARGE_MONTH:
		sDateTime.append(u.stringFormat("%s", getNameMonth(timeStamp.wMonth, true).c_str()).c_str());
		break;
	case ESO_DATETIME_YEAR:
		sDateTime.append(u.stringFormat("%04d", timeStamp.wYear).c_str());
		break;
	case ESO_DATETIME_HOUR:
		sDateTime.append(u.stringFormat("%02d", timeStamp.wHour).c_str());
		break;
	case ESO_DATETIME_MINUTE:
		sDateTime.append(u.stringFormat("%02d", timeStamp.wMinute).c_str());
		break;
	case ESO_DATETIME_SECONDS:
		sDateTime.append(u.stringFormat("%02d", timeStamp.wSecond).c_str());
		break;
	default:
		sDateTime.append(u.stringFormat("El formato de fecha [%i] no es válido.", shFormat).c_str());
		break;
	}

	return sDateTime;
}

string C_SO::getNameMonth(const short iMonth, bool bLargeName)
{
	string sLargeNameMont[12] = { "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE" };
	string sShortNameMont[12] = { "ENE", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AGO", "SEP", "OCT", "NOV", "DIC" };

	if (iMonth > 0 && iMonth < 12)
	{
		return bLargeName ? sLargeNameMont[iMonth] : sShortNameMont[iMonth];
	}
	else
	{
		return "El mes es inválido";
	}
}
