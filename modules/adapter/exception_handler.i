%include "exception.i"

%exception {
    try {
        $action
    } catch (...) {
        SWIG_exception(SWIG_RuntimeError, "runtime error");
    }
}
