#include <radapter/Utility/CheckNapi.hpp>

void radapter::checkNapi(const std::string& action, napi_env env, napi_status status)
{
    if (status != napi_ok) {
        const napi_extended_error_info* info;
        std::string msg = "Cannot " + action + ": ";

        napi_status substatus = napi_get_last_error_info(env, &info);
        if (substatus != napi_ok) {
            msg += "N-API error info unavailable";
        } else {
            msg += info->error_message;
        }

        throw std::runtime_error(msg);
    }
}
