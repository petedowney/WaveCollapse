//
// Created by Pete Downey on 4/13/24.
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>
//#include <structmember.h>

#include "WaveCollapseInterface.h"

#include <vector>
#include <unordered_map>
#include <tuple>

#include "WaveCollapse.h"

static WaveCollapse* waveCollapse = nullptr;

static PyObject* intitilize(PyObject*, PyObject* args) {

    std::vector<float> STDStates;
    std::vector<Constraint> constraints;
    int chunkSize;

    if (!PyArg_ParseTuple(args, "O!O!i", &PyList_Type, &STDStates, &PyList_Type, &constraints, &chunkSize)) {
        return nullptr;
    }

    waveCollapse = new WaveCollapse(STDStates, constraints, chunkSize);
    return nullptr;
}

static PyObject* generateChunk(PyObject*, PyObject* args) {

    int x, y;
    bool collapse;

    if (!PyArg_ParseTuple(args, "iiO", &x, &y, &collapse)) {
        return nullptr;
    }

    waveCollapse->GenerateChunk(x, y, collapse);
    return nullptr;
}

static PyObject* containsChunk(PyObject*, PyObject* args) {

    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return nullptr;
    }

    return Py_BuildValue("b", waveCollapse->containsChunk(x, y));
}

static PyObject* collapseChunk(PyObject*, PyObject* args) {

    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return nullptr;
    }

    waveCollapse->collapseChunk(x, y);
    return nullptr;
}

static PyObject* setSeed(PyObject*, PyObject* args) {

    int seed;

    if (!PyArg_ParseTuple(args, "i", &seed)) {
        return nullptr;
    }

    waveCollapse->setSeed(seed);
    return nullptr;
}

static PyObject* getChunk(PyObject*, PyObject* args) {

    int x, y;

    if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
        return nullptr;
    }

    return Py_BuildValue("O", waveCollapse->getChunk(x, y));
}

static PyObject* getChunkSize(PyObject*, PyObject* args) {
    return Py_BuildValue("i", waveCollapse->getChunkSize());
}

static PyMethodDef WaveCollapseMethods[] = {
    {"intitilize", intitilize, METH_VARARGS, "Intitilize the wave collapse algorithm."},
    {"generateChunk", generateChunk, METH_VARARGS, "Generate a chunk."},
    {"containsChunk", containsChunk, METH_VARARGS, "Check if a chunk exists."},
    {"collapseChunk", collapseChunk, METH_VARARGS, "Collapse a chunk."},
    {"setSeed", setSeed, METH_VARARGS, "Set the seed for the random number generator."},
    {"getChunk", getChunk, METH_VARARGS, "Get a chunk."},
    {"getChunkSize", getChunkSize, METH_VARARGS, "Get the size of a chunk."},
    {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef WaveCollapseModule = {
    PyModuleDef_HEAD_INIT,
    "WaveCollapse",
    "Wave Collapse Algorithm",
    -1,
    WaveCollapseMethods
};

PyMODINIT_FUNC PyInit_WaveCollapse() {
    return PyModule_Create(&WaveCollapseModule);
}

