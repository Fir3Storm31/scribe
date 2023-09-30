#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

int executePythonFunction(char *python_file, char *function_name) {

    // Calculate the length needed for the command string
    size_t command_len = strlen("./python_caller ") + strlen(python_file) + strlen(" ") + strlen(function_name) + 1;

    // Allocate memory for the command string
    char *command = (char *)malloc(command_len);

    if (command == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Construct the command string
    snprintf(command, command_len, "./python_caller %s %s", python_file, function_name);

    // Use the system function to execute the compiled C script
    int result = system(command);

    // Free the memory allocated for the command string
    free(command);

    // Check the return value to determine if the execution was successful
    if (result == 0) {
        printf("Script executed successfully.\n");
    } else {
        printf("Script execution failed.\n");
    }
    
    return result;
}