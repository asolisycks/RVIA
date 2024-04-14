#include "C_PostgreSQL.hpp"

C_PostgreSQL::C_PostgreSQL()
	: pgConnection(NULL)
	, pgResult(NULL)
	, sLastError(STRING_EMPTY)
{
}

C_PostgreSQL::~C_PostgreSQL()
{
}

//int C_PostgreSQL::convertAnsiToUTF8(char* szSrc, char* strDest, int destSize)
//{
//	WCHAR szUnicode[255];
//	char szUTF8code[255];
//	int nUnicodeSize = MultiByteToWideChar(CP_ACP, 0, szSrc, (int)strlen(szSrc), szUnicode, sizeof(szUnicode));
//	int nUTF8codeSize = WideCharToMultiByte(CP_UTF8, 0, szUnicode, nUnicodeSize, szUTF8code, sizeof(szUTF8code), NULL, NULL);
//
//	//assert(destSize > nUTF8codeSize);
//
//	memcpy(strDest, szUTF8code, nUTF8codeSize);
//
//	strDest[nUTF8codeSize] = 0;
//
//	return nUTF8codeSize;
//}

bool C_PostgreSQL::openConnection(const char* nameBD, const char* user, const char* pass, const char* IP)
{
	C_Utils utils;
	string sConn = STRING_EMPTY;

	sConn = utils.stringFormat("dbname=%s user=%s password=%s hostaddr=%s port=5432 client_encoding=LATIN1", nameBD, user, pass, IP);

	pgConnection = PQconnectdb(sConn.c_str());

	if (PQstatus(pgConnection) != CONNECTION_OK)
	{
		sLastError = utils.stringFormat("%s", PQerrorMessage(pgConnection));
		closeConnection();
		return false;
	}

	return true;
}



//bool C_PostgreSQL::openConnectionAnsiToUTF8(const char* nameBD, const char* user, const char* pass, const char* IP)
//{
//	C_Utils utils;
//	string sConn = STRING_EMPTY;
//
//	sConn = utils.stringFormat("dbname=%s user=%s password=%s hostaddr=%s port=5432", nameBD, user, pass, IP);
//
//	pgConnection = PQconnectdb(sConn.c_str());
//
//	if (PQstatus(pgConnection) != CONNECTION_OK)
//	{
//		sLastError = utils.stringFormat("%s", PQerrorMessage(pgConnection));
//		closeConnection();
//		return false;
//	}
//
//	return true;
//}

bool C_PostgreSQL::openConnection(ES_PostgresConnection pg_connection)
{
	char cStringConnection[1024] = { 0 };

	sprintf_s(cStringConnection, sizeof(cStringConnection), "dbname=%s user=%s password=%s hostaddr=%s port=5432", pg_connection.database, pg_connection.user, pg_connection.password, pg_connection.IPAddress);

	pgConnection = PQconnectdb(cStringConnection);

	if (PQstatus(pgConnection) != CONNECTION_OK)
	{
		sLastError = stringFormat("%s", PQerrorMessage(pgConnection));
		closeConnection();
		return false;
	}

	return true;
}

bool C_PostgreSQL::queryExec(const char* query, ETypeQuery type_query)
{
	C_Utils utils;
	
	pgResult = PQexec(pgConnection, query);

	switch (type_query)
	{
	case SELECT_QUERY:
		if (PQresultStatus(pgResult) != PGRES_TUPLES_OK)
		{
			sLastError = utils.stringFormat("%s", PQerrorMessage(pgConnection));
			PQclear(pgResult);
			closeConnection();
			return false;
		}
		break;
	case INSERT_QUERY:
		if (PQresultStatus(pgResult) != PGRES_COMMAND_OK)
		{
			sLastError = utils.stringFormat("%s", PQerrorMessage(pgConnection));
			PQclear(pgResult);
			closeConnection();
			return false;
		}
		break;
	case UPDATE_QUERY:
		if (PQresultStatus(pgResult) != PGRES_COMMAND_OK)
		{
			sLastError = utils.stringFormat("%s", PQerrorMessage(pgConnection));
			PQclear(pgResult);
			closeConnection();
			return false;
		}
		break;
	case DELETE_QUERY:
		if (PQresultStatus(pgResult) != PGRES_COMMAND_OK)
		{
			sLastError = utils.stringFormat("%s", PQerrorMessage(pgConnection));
			PQclear(pgResult);
			closeConnection();
			return false;
		}
		break;
	default:
		return false;
		break;
	}

	return true;
}

void C_PostgreSQL::getColumns(vector<ES_Records>& vcstRecords, int& iTotalColums)
{
	ES_Records stRecords;

	iTotalColums = PQnfields(pgResult);

	for (int i = 0; i < iTotalColums; i++)
	{
		stRecords.idColumn = i;
		stRecords.columnName = PQfname(pgResult, i);

		vcstRecords.push_back(stRecords);
	}
}

void C_PostgreSQL::getRecords(vector<ES_Records>& vcstRecords)
{
	int	iTotalColumns = 0;

	getColumns(vcstRecords, iTotalColumns);

	int iRows = PQntuples(pgResult);

	for (int i = 0; i < iRows; i++)
	{
		for (int j = 0; j < iTotalColumns; j++)
		{
			vcstRecords[j].vcValues.push_back(PQgetvalue(pgResult, i, vcstRecords[j].idColumn));
		}
	}
}

void C_PostgreSQL::getColumnsV2(vector<ST_COLUMNS>& vcstColumns, int& iTotalColumns)
{
	ST_COLUMNS stColumn;

	vcstColumns.clear();

	iTotalColumns = PQnfields(pgResult);

	for (int i = 0; i < iTotalColumns; i++)
	{
		stColumn.iColumnId = i;
		stColumn.sNameColumn = PQfname(pgResult, i);

		vcstColumns.push_back(stColumn);
	}
}

bool C_PostgreSQL::getRecordsV2(vector<ST_RECORDS_V2>& vcstRecordsV2, int& iTotalRows, int& iTotalColumns)
{
	ST_RECORDS_V2 stRecordsV2;

	iTotalColumns = 0;
	iTotalRows = 0;

	//getColumnsV2(vcstColumns, iTotalColumns);

	iTotalRows = PQntuples(pgResult);
	iTotalColumns = PQnfields(pgResult);

	for (int i = 0; i < iTotalRows; i++)
	{
		for (int j = 0; j < iTotalColumns; j++)
		{
			stRecordsV2.iColumn = j;
			stRecordsV2.iRow = i;
			stRecordsV2.sCellValue = stringFormat("%s", PQgetvalue(pgResult, i, j));
			//printf(" %s = %s(%d),", PQfname(pgResult, j), PQgetvalue(pgResult, i, j), PQgetlength(pgResult, i, j));

			vcstRecordsV2.push_back(stRecordsV2);
		}
	}

	return true;
}

void C_PostgreSQL::getRecordsV2(vector<ST_RECORDS_V2>& vcstRecordsV2, vector<ST_COLUMNS>& vcstColumns, int& iTotalRows, int& iTotalColumns)
{
	ST_RECORDS_V2 stRecordsV2;

	iTotalColumns = 0;
	iTotalRows = 0;

	printf("[PG] - Antes de obtener columnas.\n");

	vcstColumns.clear();

	getColumnsV2(vcstColumns, iTotalColumns);

	printf("[PG] - Después de obtener columnas.\n");

	iTotalRows = PQntuples(pgResult);

	for (int i = 0; i < iTotalRows; i++)
	{
		for (int j = 0; j < iTotalColumns; j++)
		{
			stRecordsV2.iColumn = j;
			stRecordsV2.iRow = i;
			printf("[PG] - DESDE LIB: [%s]\n", PQgetvalue(pgResult, i, j));
			stRecordsV2.sCellValue = stringFormat("%s", PQgetvalue(pgResult, i, j));
			//stRecordsV2.sCellValue	= stringFormat("%s", PQgetvalue(res, i, j));

			vcstRecordsV2.push_back(stRecordsV2);
		}
	}
}

void C_PostgreSQL::clearRecords()
{
	PQclear(pgResult);
}

char* C_PostgreSQL::getLastError()
{
	return (char*)sLastError.c_str();
}

void C_PostgreSQL::closeConnection()
{
	PQfinish(pgConnection);
}

string C_PostgreSQL::stringFormat(const char* fmt, ...)
{
	//printf("%s\n", fmt);

	int size = 512;
	char* buffer = 0;
	buffer = new char[size];

	va_list vl;
	va_start(vl, fmt);
	int nsize = vsnprintf(buffer, size, fmt, vl);

	//fail delete buffer and try again
	if (size <= nsize)
	{
		delete[] buffer;
		buffer = 0;
		buffer = new char[nsize + 1]; //+1 for /0
		nsize = vsnprintf(buffer, size, fmt, vl);
	}

	string ret(buffer);
	va_end(vl);
	delete[] buffer;

	return ret;
}

bool C_PostgreSQL::saveRecordsCSV(const char* path)
{
	vector<ES_Records> vcstRecords;

	getRecords(vcstRecords);

	fstream file(path, ios::out | ios::app | ios::binary);

	if (vcstRecords.size() == 0)
	{
		sLastError = stringFormat("El resultado del ultimo QUERY no obtuvo registros.");
		return false;
	}

	string sHeader;
	string sRecords;

	for (unsigned int i = 0; i < vcstRecords[0].vcValues.size(); i++)
	{
		for (unsigned int j = 0; j < vcstRecords.size(); j++)
		{
			if (!i)
			{
				sHeader.append(j != (vcstRecords.size()) && j ? "|" : "");
				sHeader.append(vcstRecords[j].columnName);

				if (j == vcstRecords.size() - 1)
				{
					sHeader.append("\n");
				}
			}

			sRecords.append(j != (vcstRecords.size()) && j ? "|" : "");
			sRecords.append(vcstRecords[j].vcValues[i]);
		}

		sRecords.append("\n");
	}

	if (!file.is_open())
	{
		sLastError = stringFormat("Error al intentar almacenar el archivo %s", path);
		return false;
	}

	file << sHeader.c_str();
	file << sRecords.c_str();

	file.close();

	// printf("\n\nArchivo %s guardado con éxito\n", path);

	// printf("\n\n%s\n", sHeader.c_str());
	// printf("%s\n", sRecords.c_str());

	return true;
}
