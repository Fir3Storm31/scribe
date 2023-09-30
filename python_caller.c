#include <Python.h>

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Usage: python_caller <python_file> <function_name>\n");
        return 1;
    }

    // Get the python file and function to be executed
    char *file_name = argv[1];
    char *function_name = argv[2];

    // Check if file name ends with .py
    if (strcmp(file_name + strlen(file_name) - 3, ".py") == 0) {
        // Remove the .py extension
        file_name[strlen(file_name) - 3] = '\0';
    }

    // Get the python directory
    char python_directory[1024];
    getcwd(python_directory, 1024);
    strcat(python_directory, "/python");

    // Initialize Python
    Py_Initialize();

    // Add the directory containing myscript.py to Python's sys.path
    PyObject *sysPath = PySys_GetObject("path");

    PyList_Append(sysPath, PyUnicode_DecodeFSDefault(python_directory));

    // Import the required Python module
    PyObject *pName = PyUnicode_DecodeFSDefault(file_name);
    PyObject *pModule = PyImport_Import(pName);
    Py_XDECREF(pName);

    if (pModule != NULL) {
        // Get a reference to the Python function
        PyObject *pFunction = PyObject_GetAttrString(pModule, function_name);

        if (pFunction && PyCallable_Check(pFunction)) {
            // call the Python function
            PyObject *pValue = PyObject_CallObject(pFunction, NULL);

            if (pValue != NULL) {
                // Process the returned value as an integer
                int result = PyLong_AsLong(pValue);
                printf("Return: %i\n", result);
                Py_XDECREF(pValue);
            } else {
                PyErr_Print();
            }
        } else {
            PyErr_Print();
        }

        // Clean up Python
        Py_XDECREF(pFunction);
        Py_XDECREF(pModule);

    }
    else {
        PyErr_Print();
        PyErr_Clear();
    }

    // Finalize Python
    Py_Finalize();

    return 0;
}
