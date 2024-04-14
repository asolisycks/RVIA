#ifndef CRVIA_HPP
#define CRVIA_HPP

#include <node_api.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <format>  // C++20
#include <fstream>  // Para manejar archivos
#include <iostream> // Para manejar archivos

namespace rvia 
{
	class CRvia 
	{
	public:
		explicit CRvia(int64_t numemp, char* path, char* tipo, int32_t cant, int32_t amb);
		int execute() const;
	private:
		int64_t lNumEmp;
		char cPath[1024];
		char cTipo[10];
		int32_t iCant;
		int32_t iAmb;

	};

}  // namespace rvia

#endif  // CRVIA_HPP
