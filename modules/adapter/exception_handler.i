%include "exception.i"

%exception {
    try {
        $action
    } catch (std::runtime_error &e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}
