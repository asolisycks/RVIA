/**
	Empresa:		Coppel SA
	Archivos:		C_Utils.h y C_Utils.cpp
	Autor:			Jes�s Enrique Arce P�rez
	Correo:			jesus.arce@coppel.com
	Fecha:			2017/09/11
	Versi�n:		1.0.0.0

	Descripci�n:	C_Utils contiene m�todos generalmente �tiles para evitar la redundancia de c�digo.
*/

#ifndef C_UTILS_H
#define C_UTILS_H

#include <stdarg.h>
#include <string>

#define STRING_EMPTY			""

using namespace std;

class C_Utils
{
public:
	C_Utils();
	~C_Utils();

	/**
		M�todo:			stringFormat
		Modific�:		Jes�s Enrique Arce
		Solicit�:		Jes�s Enrique Arce
		Correo:			jesus.arce@coppel.com
		Fecha:			2017/09/11

		Descripci�n:	M�todo que da formato a una cadena de texto. Similar al m�todo 'Format' de la clase CString.

		Ejemplo de uso:
						string sMensaje = stringFormat("El tiempo transcurrido es %d minutos", 8);
	*/
	string stringFormat(const char* fmt, ...);

	/*
	base64.cpp and base64.h

	Copyright (C) 2004-2008 Ren� Nyffenegger

	This source code is provided 'as-is', without any express or implied
	warranty. In no event will the author be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this source code must not be misrepresented; you must not
	claim that you wrote the original source code. If you use this source code
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original source code.

	3. This notice may not be removed or altered from any source distribution.

	Ren� Nyffenegger rene.nyffenegger@adp-gmbh.ch

	*/
	string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	string base64_decode(string const& encoded_string);
};

#endif //C_UTILS_H