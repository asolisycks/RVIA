/* ----------------------------------------------------------------------------------------------------------------
	Empresa:		Coppel S.A de C.V.
	Archivos:		C_PSQL.h y C_PSQL.cpp
	Autor:			José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06
	Versión:		1.0.0.0

	Descripción:	C_PostgreSQL contiene métodos para establecer conexiones a servidores con SGBD PostgreSQL,
	ejecutar consultas y obtener los resultados de la consulta en un vector.
	La descripción de cada método se describe previo a la declaración del mismo en este archivo.
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
	Método:			openConnection
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que abre la conexión a un servidor con SGBD PostgreSQL.
	Retorna 'true' si la conexión se estableció con éxito, de lo
	contrario el retorno es 'false'.
	Para obtener más detalles sobre errores en caso de que la conexión
	falle, es necesario llamar el método 'getLastError', el cual retorna
	los detalles del último error.
*/
	bool openConnection(const char* nameBD, const char* user, const char* pass, const char* IP);

	/**
	Método:			openConnection
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que abre la conexión a un servidor con SGBD PostgreSQL.
	Retorna 'true' si la conexión se estableció con éxito, de lo
	contrario el retorno es 'false'.
	Para obtener más detalles sobre errores en caso de que la conexión
	falle, es necesario llamar el método 'getLastError', el cual retorna
	los detalles del último error.
	*/
	//bool openConnectionAnsiToUTF8(const char* nameBD, const char* user, const char* pass, const char* IP);
	bool openConnection(ES_PostgresConnection stPostgresConnection);

	/**
	Método:			queryExec
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2017/09/27

	Descripción:	Método que ejecuta un query en la base de datos que se definió en el método
	'openConnection', retorna 'true' si el query se ejecutó con éxito, de lo
	contrario retorna false. Si el retorno es 'false' el método 'getLastError'
	contiene los detalles del último error.
	El tipo de query es importante para el método getRecords, debido a que si el tipo no es
	SELECT entonces no aplica el llamado posterior de este método, por ello existe un segundo
	parámetro (opcional) del tipo ETypeQuery.
	*/
	bool queryExec(const char* query, ETypeQuery type_query = SELECT_QUERY);

	/**
	Método:			getColumns
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que almacena en un std::vector (primer parámetro por referencia) el nombre
	y ID de las columnas correspondientes a la ejecución de la última consulta.
	El segundo parámetro (también por referencia) contiene el total de columnas.
	*/
	void getColumns(std::vector<ES_Records>& vcstColumns, int& iTotalColums);

	/**
	Método:			getRecords
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que almacena en un std::vector (parámetro por referencia) el nombre de las
	columnas y los registros obtenidos del último query que se ejecutó.
	*/
	void getRecords(std::vector<ES_Records>& vcstRecords);

	/**
		Método:			getRecordsV2
		Modificó:		Jesús Enrique Arce
		Modificó:		José Arturo Solís Ramírez
		Solicitó:		José Arturo Solís Ramírez
		Correo:			asolis@coppel.com
		Fecha:			2023/01/06

		Descripción:	Método que almacena en un vector (parámetro por referencia) los registros obtenidos
						del último query que se ejecutó.
	*/
	bool getRecordsV2(vector<ST_RECORDS_V2>& vcstRecordsV2, int& iTotalRows, int& iTotalColumns);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	/**
		Método:			getColumnsV2
		Modificó:		José Arturo Solís Ramírez
		Solicitó:		José Arturo Solís Ramírez
		Correo:			asolis@coppel.com
		Fecha:			2023/01/06

		Descripción:	Método que almacena en un vector (primer parámetro por referencia) el nombre
						y ID de las columnas correspondientes a la ejecución de la última consulta.
						El segundo parámetro (también por referencia) contiene el total de columnas.
	*/
	void getColumnsV2(vector<ST_COLUMNS>& vcstColumns, int& iTotalColums);

	/**
		Método:			getRecordsV2
		Modificó:		José Arturo Solís Ramírez
		Solicitó:		José Arturo Solís Ramírez
		Correo:			asolis@coppel.com
		Fecha:			2023/01/06

		Descripción:	Método que almacena en un vector (parámetro por referencia) los registros obtenidos
						del último query que se ejecutó.
	*/
	void getRecordsV2(vector<ST_RECORDS_V2>& vcstRecordsV2, vector<ST_COLUMNS>& vcstColumns, int& iTotalRows, int& iTotalColumns);
	//////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	Método:			clearRecords
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que limpia los registros del último query que se ejecutó.
	Pero no limpia el std::vector con los datos que retornó el método 'getRecords'.
	*/
	void clearRecords();

	/**
	Método:			closeConnection
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que cierra la conexión que se estableció en el método 'openConnection'.
	*/
	void closeConnection();


	/**
	Método:			closeConnection
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2024/03/09

	Descripción:	Esta función duplica el tamaño de la cadena de entrada para asegurarse de que hay suficiente espacio para la cadena sanitizada, 
					y luego llama a PQescapeStringConn para escapar de los caracteres especiales. Por último, 
					convierte la cadena sanitizada en un std::string y la devuelve.
	*/

	std::string sanitize(const std::string& input);

	/**
	Método:			getLastError
	Modificó:		José Arturo Solís Ramírez
	Solicitó:		José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/06

	Descripción:	Método que obtiene los detalles del último error que se presentó.
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
