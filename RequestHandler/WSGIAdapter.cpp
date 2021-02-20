#include <unordered_map>
#include <python3.7m/Python.h>
#include <string>
#include <iostream>
#include "WSGIAdapter.h"

void WSGIAdapter::forward(std::unordered_map<std::string, std::string*>& request_environment){
    forward_wsgi(request_environment);
}

void WSGIAdapter::forward_wsgi(std::unordered_map<std::string, std::string*>& request_environment){
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/ec2-user/test/')");

    auto p_module  = PyImport_ImportModule("app");
    auto p_dict   = PyModule_GetDict(p_module);
    auto app_callable = PyDict_GetItemString(p_dict, "app");

    
    
    //build the env dict for app()
    auto* env = PyDict_New();
    auto *p_args = PyTuple_New(1);
    
    for(auto h: request_environment){
        PyDict_SetItemString(env, h.first.c_str(),Py_BuildValue("s",h.second->c_str()));
    }

    PyTuple_SetItem(p_args, 0, env);
    auto response = PyObject_CallObject(app_callable, p_args);
    char buffer[256];
    PyArg_Parse(response, "s", &buffer);
    
    std::cout<<buffer<<std::endl;
    //PyDict_SetItemString(env, "result",Py_BuildValue("s","ok"));
    if (response == NULL)
        return;

    int nTupleSize = PyTuple_Size(response);
    for (int l = 0; l < nTupleSize; l++)
    {
        PyObject *pTupleList = PyTuple_GetItem(response, l);
        int nTupleListSize = PyList_Size(pTupleList);
        for (int m = 0; m < nTupleListSize; m++)
        {
            PyObject* pTupleListValue = PyList_GetItem(pTupleList, m);
            int nValue = 0;
            PyArg_Parse(pTupleListValue, "i", &nValue);
            std::cout << nValue << std::endl;
        }
    }
    Py_DECREF(p_module);
    Py_DECREF(p_dict);
    Py_DECREF(app_callable);
    Py_DECREF(env);
    Py_DECREF(p_args);
    Py_DECREF(response);
    //Py_DECREF(pTupleList);
    Py_Finalize();
}