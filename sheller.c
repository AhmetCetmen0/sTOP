#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

// İşletim sistemi tespiti ve fonksiyon eşlemesi
#ifdef _WIN32
    #define popen _popen
    #define pclose _pclose
#endif

static PyObject* sheller_run(PyObject* self, PyObject* args) {
    const char* command;

    if (!PyArg_ParseTuple(args, "s", &command)) {
        return NULL;
    }

    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Komut çalıştırılamadı");
        return NULL;
    }

    char buffer[1024];
    PyObject* output = PyUnicode_New(0, 127);  // boş string

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        PyObject* line = PyUnicode_FromString(buffer);
        PyUnicode_Append(&output, line);
        Py_DECREF(line);
    }

    int status = pclose(fp);
    if (status == -1) {
        PyErr_SetString(PyExc_RuntimeError, "Komut sonlandırılamadı");
        return NULL;
    }

    return output;
}

static PyMethodDef ShellerMethods[] = {
    {"run", sheller_run, METH_VARARGS, "Komutu çalıştır ve çıktısını döndür"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef shellermodule = {
    PyModuleDef_HEAD_INIT,
    "sheller",
    "Terminal komutlarını çalıştıran modül",
    -1,
    ShellerMethods
};

PyMODINIT_FUNC PyInit_sheller(void) {
    return PyModule_Create(&shellermodule);
}
