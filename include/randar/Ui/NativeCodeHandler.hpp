#ifndef RANDAR_UI_NATIVE_CODE_HANDLER_HPP
#define RANDAR_UI_NATIVE_CODE_HANDLER_HPP

namespace randar
{
    struct NativeCodeHandler
    {
        virtual void execute(
            const std::string& name,
            const ::CefV8ValueList& arguments,
            ::CefRefPtr<::CefV8Value>& returnValue) = 0;
    };
}

#endif
