#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <iostream>
#include <fstream>
#include <string>


#include "../src/include/eegimage.h"


static PyObject *
pybcisift_extract_full(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    PyObject* seq;
    int seqlen;
    int i;

    int heightofimage = 256;
    int gamma = 1;
    int gammat = 1;
    int signallength = 256;
    bool normalize = true;
    int imageid = 1;

    if (!PyArg_ParseTuple(args, "i(ii)(ii)piO", 
                                &i,
                                &heightofimage,
                                &signallength,
                                &gamma,
                                &gammat,
                                &normalize,
                                &imageid,
                                &seq))
        return NULL;


    /* get one argument as a sequence */
    seq = PySequence_Fast(seq, "argument must be iterable");
    if(!seq)
        return 0;

    printf("Height: %d\n", heightofimage);
    printf("Length: %d\n", signallength);
    printf("Gamma and gammat: %d, %d\n", gamma, gammat);
    printf("Normalize: %d\n", (normalize?1:0));
    


    float descr[128];
    double signal[signallength];
    
    memset(signal,0,sizeof(double)*signallength);

    /* prepare data as an array of doubles */
    seqlen = PySequence_Fast_GET_SIZE(seq);
    //if(!dbar) {
    //    Py_DECREF(seq);
    //    return PyErr_NoMemory(  );
    //}
    for(i=0; i < seqlen; i++) {
        PyObject *fitem;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if(!item) {
            Py_DECREF(seq);
            return 0;
        }
        fitem = PyNumber_Float(item);
        if(!fitem) {
            Py_DECREF(seq);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return 0;
        }
        signal[i] = PyFloat_AS_DOUBLE(fitem);
        //printf("[%10.2f]", signal[i]);
        Py_DECREF(fitem);
    }    

    /* clean up, compute, and return result */
    Py_DECREF(seq);

    eegimage(&descr[0],signal,heightofimage,signallength,gamma,gammat,normalize,imageid);


    int N=128;
    PyObject* python_val = PyList_New(N);
    for (int i = 0; i < N; ++i)
    {
        PyObject* pv = Py_BuildValue("f", descr[i]);
        PyList_SetItem(python_val, i, pv);
    }


    return python_val;




    //sts = 3;
    //return Py_BuildValue("i", sts);
}

static PyObject *
pybcisift_extract(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    PyObject* seq;
    int seqlen;
    int i;

    //if (!PyArg_ParseTuple(args, "s", &command))
    //    return NULL;


    //sts = system(command);

    /* get one argument as a sequence */
    if(!PyArg_ParseTuple(args, "O", &seq))
        return 0;
    seq = PySequence_Fast(seq, "argument must be iterable");
    if(!seq)
        return 0;


    float descr[128];
    double signal[256];
    
    memset(signal,0,sizeof(double)*256);

    /* prepare data as an array of doubles */
    seqlen = PySequence_Fast_GET_SIZE(seq);
    //if(!dbar) {
    //    Py_DECREF(seq);
    //    return PyErr_NoMemory(  );
    //}
    for(i=0; i < seqlen; i++) {
        PyObject *fitem;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if(!item) {
            Py_DECREF(seq);
            return 0;
        }
        fitem = PyNumber_Float(item);
        if(!fitem) {
            Py_DECREF(seq);
            PyErr_SetString(PyExc_TypeError, "all items must be numbers");
            return 0;
        }
        signal[i] = PyFloat_AS_DOUBLE(fitem);
        Py_DECREF(fitem);
    }    

    /* clean up, compute, and return result */
    Py_DECREF(seq);

    eegimage(&descr[0],signal,256,256,1,1,true,1);


    int N=128;
    PyObject* python_val = PyList_New(N);
    for (int i = 0; i < N; ++i)
    {
        PyObject* pv = Py_BuildValue("f", descr[i]);
        PyList_SetItem(python_val, i, pv);
    }


    return python_val;




    //sts = 3;
    //return Py_BuildValue("i", sts);
}

static PyMethodDef methods[] = {
    {"extract",  pybcisift_extract, METH_VARARGS,
     "Extract a SIFT descriptor from the signal"},
    {"extract_full", pybcisift_extract_full, METH_VARARGS,
     "Extract a SIFT descriptor with parameters from the signal"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
    PyModuleDef_HEAD_INIT,
    "pybcisift",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    methods
};

PyMODINIT_FUNC
PyInit_pybcisift(void)
{
    return PyModule_Create(&spammodule);
}


int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("pybcisift", PyInit_pybcisift);

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyImport_ImportModule("pybcisift");


    PyMem_RawFree(program);
    return 0;
}
