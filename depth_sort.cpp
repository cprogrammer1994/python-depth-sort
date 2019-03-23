#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

PyObject * meth_sort(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "", keywords)) {
        return 0;
    }

    Py_RETURN_NONE;
}

PyMethodDef module_methods[] = {
    {"sort", (PyCFunction)meth_sort, METH_VARARGS | METH_KEYWORDS, 0},
    {0},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "depth_sort", 0, -1, module_methods, 0, 0, 0, 0};

extern "C" PyObject * PyInit_depth_sort() {
    PyObject * module = PyModule_Create(&module_def);
    return module;
}
