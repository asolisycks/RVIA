#include "CRvia.hpp"

namespace rvia 
{
    //CRvia::CRvia(double value) : value_(value) {}
	CRvia::CRvia(int64_t numemp, char* path, char* tipo, int32_t cant, int32_t amb)
	{
		// Print the parameters received
		std::cout << "numemp: " << numemp << std::endl;
		std::cout << "path: " << path << std::endl;
		std::cout << "tipo: " << tipo << std::endl;
		std::cout << "cant: " << cant << std::endl;
		std::cout << "amb: " << amb << std::endl;

        lNumEmp = numemp;
        strcpy_s(cPath, path);
        strcpy_s(cTipo, tipo);
        iCant = cant;
        iAmb = amb;

        execute();
	}

    int CRvia::execute() const
    {
        //STARTUPINFOA si;
        //PROCESS_INFORMATION pi;

        //ZeroMemory(&si, sizeof(si));
        //si.cb = sizeof(si);
        //si.dwFlags = STARTF_USESHOWWINDOW;
        //si.wShowWindow = SW_HIDE;

        //ZeroMemory(&pi, sizeof(pi));

        char cFileRVIA[600] = { 0 };
        memset(cFileRVIA, ' ', sizeof(cFileRVIA));

        sprintf_s(cFileRVIA, "C:\\Proyectos\\OpenAI\\RVIA\\x64\\Release\\RvIA.exe %I64d %s %s %d %d", lNumEmp, cPath, cTipo, iCant, iAmb);

        std::cout << "cFileRVIA: " << cFileRVIA << std::endl;

        int iRet = system(cFileRVIA);

        std::cout << "iRet: " << iRet << std::endl;
        
        //if (!CreateProcessA(NULL,   // No module name (use command line)
        //    cFileRVIA,       // Command line
        //    NULL,           // Process handle not inheritable
        //    NULL,           // Thread handle not inheritable
        //    FALSE,          // Set handle inheritance to FALSE
        //    CREATE_NO_WINDOW,              // No creation flags
        //    NULL,           // Use parent's environment block
        //    NULL,           // Use parent's starting directory 
        //    &si,            // Pointer to STARTUPINFO structure
        //    &pi)           // Pointer to PROCESS_INFORMATION structure
        //    )
        //{
        //    std::cout << "CREATE PROCESS FAILED." << (int)GetLastError() << " [execute] " << std::endl;
        //    return 1;
        //}

        //// Wait until child process exits.
        //WaitForSingleObject(pi.hProcess, INFINITE);

        //// Close process and thread handles. 
        //CloseHandle(pi.hProcess);
        //CloseHandle(pi.hThread);

        return iRet;
    }

}  // namespace rvia
