#include <radapter/Utility/CallbackInfo.hpp>

radapter::CallbackInfo::CallbackInfo(napi_env env, napi_callback_info info)
{
    this->env = env;

    // We can't tell how many arguments were passed yet, so we provide an
    // array with a reasonably large size first.
    this->args.resize(RADAPTER_MAX_CALLBACK_ARGC);
    size_t argc = this->args.size();

    radapter::checkNapi("retrieve callback info", env, napi_get_cb_info(
        env,
        info,
        &argc,
        this->args.data(),
        &this->self,
        nullptr
    ));

    // argc is now filled with the actual argument count. Resize accordingly.
    this->args.resize(argc);
}
