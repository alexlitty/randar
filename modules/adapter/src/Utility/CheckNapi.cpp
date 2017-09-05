#include <radapter/Utility/CheckNapi.hpp>

void radapter::checkNapi(napi_env env, napi_status status)
{
    if (status != napi_ok) {
        const napi_extended_error_info* info;

        napi_status substatus = napi_get_last_error_info(env, &info);
        if (substatus != napi_ok) {
            throw std::runtime_error("Cannot retrieve N-API error info");
        }

        throw std::runtime_error(info->error_message);
    }
}
