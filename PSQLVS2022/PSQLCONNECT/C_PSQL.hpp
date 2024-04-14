/* ----------------------------------------------------------------------------------------------------------------
	Empresa:		Coppel S.A de C.V.
	Archivos:		C_PSQL.hpp y C_PSQL.cpp
	Autor:			José Arturo Solís Ramírez
	Correo:			asolis@coppel.com
	Fecha:			2023/01/07
	Versión:		1.0.0.0
	Descripción:	Procedimiento que retorna la versión de la librería.
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