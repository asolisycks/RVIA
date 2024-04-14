/* ----------------------------------------------------------------------------------------------------------------
	Empresa:		Coppel S.A de C.V.
	Archivos:		C_PSQL.hpp y C_PSQL.cpp
	Autor:			Jos� Arturo Sol�s Ram�rez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/07
	Versi�n:		1.0.0.0
	Descripci�n:	Procedimiento que retorna la versi�n de la librer�a.
 ---------------------------------------------------------------------------------------------------------------- */

#ifndef C_PSQL_HPP
#define C_PSQL_HPP

#include <string>

#include "C_Utils.h"
#include "C_SO.h"
#include "C_File.h"
#include "C_PostgreSQL.hpp"

#pragma once

class C_PSQL
{
public:
	C_PSQL();
	~C_PSQL();

	std::string getVersion();
};

#endif //C_PSQL_HPP