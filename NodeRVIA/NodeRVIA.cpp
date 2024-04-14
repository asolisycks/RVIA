/*#define NAPI_VERSION 3
#include <node_api.h> 

#include "narvia.hpp"

namespace NodeRVIA
{
    using v8::Local;
    using v8::Object;

    void InitAll(Local<Object> exports)
    {
        Narvia::Init(exports);
    }

    NODE_MODULE(hcmain, InitAll)

}  // namespace hc*/

#define NAPI_VERSION 3
#include <node_api.h>

napi_value Method(napi_env env, napi_callback_info info) 
{
  napi_status status;
  napi_value world;
  status = napi_create_string_utf8(env, "¡Hola Mundo!", NAPI_AUTO_LENGTH, &world);
  return world;
}

napi_value Init(napi_env env, napi_value exports) 
{
  napi_status status;
  napi_value fn;
  status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
  status = napi_set_named_property(env, exports, "hello", fn);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
