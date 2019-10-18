#include <cstdarg>
#include <cstdlib>
#include <cstring>

#include "test_helpers.hpp"

char **makeArgv(int count, ...) {
    va_list args;
    int i;
    char **argv = (char **) malloc((static_cast<unsigned long>(count + 1)) * sizeof(char *));
    char *temp;

    va_start(args, count);

    for (i = 0; i < count; i++) {
        temp = va_arg(args, char*);
        argv[i] = (char *) malloc(sizeof(temp + 1));
        strcpy(argv[i], temp);
    }
    argv[i] = nullptr;

    va_end(args);

    return argv;
}
