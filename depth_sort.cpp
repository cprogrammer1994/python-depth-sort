#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>
#include <algorithm>

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

    float * values = (float *)malloc(num_triangles * 8);
    int * keys = (int *)(values + num_triangles);

    for (int i = 0; i < num_triangles; ++i) {
        const glm::vec3 & vert = *(glm::vec3 *)((char *)mesh_view.buf + stride * i * 3);
        values[i] = glm::dot(vert, direction);
        keys[i] = i;
    }

    std::sort(keys, keys + num_triangles, [values](int a, int b) { return values[a] < values[b]; });

    for (int i = 0; i < num_triangles; ++i) {
        *ptr++ = glm::ivec3 {keys[i] * 3 + 0, keys[i] * 3 + 1, keys[i] * 3 + 2};
    }

    free(values);

    PyBuffer_Release(&mesh_view);
    return res;
}

PyObject * meth_isort(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"direction", "mesh", "index", "stride", NULL};

    glm::vec3 direction;
    Py_buffer mesh_view;
    Py_buffer index_view;
    int stride;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "(fff)y*y*i", keywords, v_xyz(direction), &mesh_view, &index_view, &stride)) {
        return 0;
    }

    int num_triangles = (int)(index_view.len / sizeof(glm::ivec3));
    PyObject * res = PyBytes_FromStringAndSize(NULL, sizeof(glm::ivec3) * num_triangles);
    glm::ivec3 * ptr = (glm::ivec3 *)PyBytes_AS_STRING(res);

    float * values = (float *)malloc(num_triangles * 8);
    int * keys = (int *)(values + num_triangles);

    glm::ivec3 * triangles = (glm::ivec3 *)index_view.buf;

    for (int i = 0; i < num_triangles; ++i) {
        const glm::vec3 & vert = *(glm::vec3 *)((char *)mesh_view.buf + stride * triangles[i].x);
        values[i] = glm::dot(vert, direction);
        keys[i] = i;
    }

    std::sort(keys, keys + num_triangles, [values](int a, int b) { return values[a] < values[b]; });

    for (int i = 0; i < num_triangles; ++i) {
        *ptr++ = triangles[keys[i]];
    }

    free(values);

    PyBuffer_Release(&mesh_view);
    PyBuffer_Release(&index_view);
    return res;
}

PyMethodDef module_methods[] = {
    {"sort", (PyCFunction)meth_sort, METH_VARARGS | METH_KEYWORDS, 0},
    {"isort", (PyCFunction)meth_isort, METH_VARARGS | METH_KEYWORDS, 0},
    {0},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "depth_sort", 0, -1, module_methods, 0, 0, 0, 0};

extern "C" PyObject * PyInit_depth_sort() {
    PyObject * module = PyModule_Create(&module_def);
    return module;
}
