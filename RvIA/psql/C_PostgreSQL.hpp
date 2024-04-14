/* ----------------------------------------------------------------------------------------------------------------
	Empresa:		Coppel S.A de C.V.
	Archivos:		C_PSQL.h y C_PSQL.cpp
	Autor:			Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06
	Versi�n:		1.0.0.0

	Descripci�n:	C_PostgreSQL contiene m�todos para establecer conexiones a servidores con SGBD PostgreSQL,
	ejecutar consultas y obtener los resultados de la consulta en un vector.
	La descripci�n de cada m�todo se describe previo a la declaraci�n del mismo en este archivo.
 ---------------------------------------------------------------------------------------------------------------- */
#pragma once

#ifndef C_POSTGRESQL_HPP
#define C_POSTGRESQL_HPP

#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "C_Utils.h"
#include "libpq-fe.h"

#define STRING_EMPTY ""

enum ETypeQuery
{
	SELECT_QUERY,
	INSERT_QUERY,
	UPDATE_QUERY,
	DELETE_QUERY
};

struct ES_PostgresConnection
{
	char IPAddress[20];
	char database[1024];
	char user[1024];
	char password[1024];

	ES_PostgresConnection()
	{
		memset(IPAddress, ' ', sizeof(IPAddress));
		memset(database, ' ', sizeof(database));
		memset(user, ' ', sizeof(user));
		memset(password, ' ', sizeof(password));
	}
};

struct ES_Records {
	int				idColumn = 0;
	char* columnName = NULL;
	std::vector<char*>	vcValues;
};

struct ST_COLUMNS
{
	int		iColumnId;
	string	sNameColumn;

	ST_COLUMNS()
	{
		iColumnId = 0;
		sNameColumn = STRING_EMPTY;
	}
};

struct ST_RECORDS_V2
{
	int		iRow;
	int		iColumn;
	string	sCellValue;

	ST_RECORDS_V2()
	{
		iRow = 0;
		iColumn = 0;
		sCellValue = STRING_EMPTY;
	}
};


class C_PostgreSQL
{
public:
	C_PostgreSQL();
	~C_PostgreSQL();
	/**
	M�todo:			openConnection
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que abre la conexi�n a un servidor con SGBD PostgreSQL.
	Retorna 'true' si la conexi�n se estableci� con �xito, de lo
	contrario el retorno es 'false'.
	Para obtener m�s detalles sobre errores en caso de que la conexi�n
	falle, es necesario llamar el m�todo 'getLastError', el cual retorna
	los detalles del �ltimo error.
*/
	bool openConnection(const char* nameBD, const char* user, const char* pass, const char* IP);

	/**
	M�todo:			openConnection
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que abre la conexi�n a un servidor con SGBD PostgreSQL.
	Retorna 'true' si la conexi�n se estableci� con �xito, de lo
	contrario el retorno es 'false'.
	Para obtener m�s detalles sobre errores en caso de que la conexi�n
	falle, es necesario llamar el m�todo 'getLastError', el cual retorna
	los detalles del �ltimo error.
	*/
	//bool openConnectionAnsiToUTF8(const char* nameBD, const char* user, const char* pass, const char* IP);
	bool openConnection(ES_PostgresConnection stPostgresConnection);

	/**
	M�todo:			queryExec
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2017/09/27

	Descripci�n:	M�todo que ejecuta un query en la base de datos que se defini� en el m�todo
	'openConnection', retorna 'true' si el query se ejecut� con �xito, de lo
	contrario retorna false. Si el retorno es 'false' el m�todo 'getLastError'
	contiene los detalles del �ltimo error.
	El tipo de query es importante para el m�todo getRecords, debido a que si el tipo no es
	SELECT entonces no aplica el llamado posterior de este m�todo, por ello existe un segundo
	par�metro (opcional) del tipo ETypeQuery.
	*/
	bool queryExec(const char* query, ETypeQuery type_query = SELECT_QUERY);

	/**
	M�todo:			getColumns
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que almacena en un std::vector (primer par�metro por referencia) el nombre
	y ID de las columnas correspondientes a la ejecuci�n de la �ltima consulta.
	El segundo par�metro (tambi�n por referencia) contiene el total de columnas.
	*/
	void getColumns(std::vector<ES_Records>& vcstColumns, int& iTotalColums);

	/**
	M�todo:			getRecords
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que almacena en un std::vector (par�metro por referencia) el nombre de las
	columnas y los registros obtenidos del �ltimo query que se ejecut�.
	*/
	void getRecords(std::vector<ES_Records>& vcstRecords);

	/**
		M�todo:			getRecordsV2
		Modific�:		Jes�s Enrique Arce
		Modific�:		Jos� Arturo Sol�s Ram�rez
		Solicit�:		Jos� Arturo Sol�s Ram�rez
		Correo:			asolis@coppel.com
		Fecha:			2023/01/06

		Descripci�n:	M�todo que almacena en un vector (par�metro por referencia) los registros obtenidos
						del �ltimo query que se ejecut�.
	*/
	bool getRecordsV2(vector<ST_RECORDS_V2>& vcstRecordsV2, int& iTotalRows, int& iTotalColumns);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		M�todo:			getColumnsV2
		Modific�:		Jos� Arturo Sol�s Ram�rez
		Solicit�:		Jos� Arturo Sol�s Ram�rez
		Correo:			asolis@coppel.com
		Fecha:			2023/01/06

		Descripci�n:	M�todo que almacena en un vector (primer par�metro por referencia) el nombre
						y ID de las columnas correspondientes a la ejecuci�n de la �ltima consulta.
						El segundo par�metro (tambi�n por referencia) contiene el total de columnas.
	*/
	void getColumnsV2(vector<ST_COLUMNS>& vcstColumns, int& iTotalColums);

	/**
		M�todo:			getRecordsV2
		Modific�:		Jos� Arturo Sol�s Ram�rez
		Solicit�:		Jos� Arturo Sol�s Ram�rez
		Correo:			asolis@coppel.com
		Fecha:			2023/01/06

		Descripci�n:	M�todo que almacena en un vector (par�metro por referencia) los registros obtenidos
						del �ltimo query que se ejecut�.
	*/
	void getRecordsV2(vector<ST_RECORDS_V2>& vcstRecordsV2, vector<ST_COLUMNS>& vcstColumns, int& iTotalRows, int& iTotalColumns);
	//////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	M�todo:			clearRecords
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que limpia los registros del �ltimo query que se ejecut�.
	Pero no limpia el std::vector con los datos que retorn� el m�todo 'getRecords'.
	*/
	void clearRecords();

	/**
	M�todo:			closeConnection
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que cierra la conexi�n que se estableci� en el m�todo 'openConnection'.
	*/
	void closeConnection();


	/**
	M�todo:			closeConnection
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2024/03/09

	Descripci�n:	Esta funci�n duplica el tama�o de la cadena de entrada para asegurarse de que hay suficiente espacio para la cadena sanitizada, 
					y luego llama a PQescapeStringConn para escapar de los caracteres especiales. Por �ltimo, 
					convierte la cadena sanitizada en un std::string y la devuelve.
	*/

	std::string sanitize(const std::string& input);

	/**
	M�todo:			getLastError
	Modific�:		Jos� Arturo Sol�s Ram�rez
	Solicit�:		Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripci�n:	M�todo que obtiene los detalles del �ltimo error que se present�.
	*/
	char* getLastError();

	std::string stringFormat(const char* fmt, ...);

	bool saveRecordsCSV(const char* path);

private:
	PGconn* pgConnection;
	PGresult* pgResult;
	string		sLastError;

	//int convertAnsiToUTF8(char* szSrc, char* strDest, int destSize);
};

#endif //C_POSTGRESQL_HPP
