#define NAPI_VERSION 3
#include <node_api.h>
#include "CRvia.hpp"
#include <iostream>

namespace rvia 
{
	//napi_value Method(napi_env env, napi_callback_info info) 
	//{
	//	CRvia rv(9032.9121);
	//	napi_status status;
	//	napi_value iNum;
	//	//napi_value world;
	//	//status = napi_create_string_utf8(env, "¡Hola Mundo!", NAPI_AUTO_LENGTH, &world);
	//	//return world;

	//	status = napi_create_double(env, rv.value(), &iNum);
	//	return iNum;
	//}

    napi_value RunExe(napi_env env, napi_callback_info info) 
    {
        size_t argc = 5;

        napi_value args[1];

        char str[512] = { 0 };
        size_t str_len;

        napi_get_cb_info(env, info, &argc, args, NULL, NULL);
        napi_get_value_string_utf8(env, args[0], str, 512, &str_len);

        std::string command = "start ";
        command += str;

        std::cout << "command: " << command << std::endl;

        int iResult = system(command.c_str());

		std::cout << "iResult: " << iResult << std::endl;

        napi_value result;
        napi_create_int32(env, iResult, &result);

        return result;
    }

	napi_value Method(napi_env env, napi_callback_info info)
	{
		size_t argc = 5;
		napi_value args[5];
		napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

		int64_t numemp;
		napi_get_value_int64(env, args[0], &numemp);

		char path[1024];
		size_t path_len;
		napi_get_value_string_utf8(env, args[1], path, 1024, &path_len);

		char tipo[1024];
		size_t tipo_len;
		napi_get_value_string_utf8(env, args[2], tipo, 1024, &tipo_len);

		int32_t cant;
		napi_get_value_int32(env, args[3], &cant);

		int32_t amb;
		napi_get_value_int32(env, args[4], &amb);

		CRvia rv(numemp, path, tipo, cant, amb);
		napi_status status;
		napi_value result;
		//status = napi_create_double(env, rv.value(), &result);

		if (argc > 4)
		{
			status = napi_create_int32(env, 666, &result);
		}
		else
		{
			status = napi_create_int32(env, 0, &result);
		}
		
		return result;
	}

	napi_value Init(napi_env env, napi_value exports) 
	{
		napi_status status;
		napi_value fn;
		status = napi_create_function(env, nullptr, 0, RunExe, nullptr, &fn);
		status = napi_set_named_property(env, exports, "runExe", fn);
		return exports;
	}

	NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
} // namespace rvia


