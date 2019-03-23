#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>

#include "glm/glm.hpp"

#define v_xyz(obj) &obj.x, &obj.y, &obj.z

PyObject * meth_sort(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"direction", "mesh", "stride", NULL};

    glm::vec3 direction;
    Py_buffer mesh_view;
    int stride;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "(fff)y*i", keywords, v_xyz(direction), &mesh_view, &stride)) {
        return 0;
    }

    int num_triangles = (int)(mesh_view.len / (stride * 3));
    PyObject * res = PyBytes_FromStringAndSize(NULL, sizeof(glm::ivec3) * num_triangles);
    glm::ivec3 * ptr = (glm::ivec3 *)PyBytes_AS_STRING(res);

    // TODO: sort

    PyBuffer_Release(&mesh_view);
    return res;
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
