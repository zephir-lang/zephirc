#include <catch2/catch.hpp>
#include <cstdarg>

#include "../src/commands/cmd.hpp"

char **makeArgv(int count, ...)
{
    va_list args;
    int i;
    char **argv = (char **)malloc((static_cast<unsigned long>(count + 1)) * sizeof(char*));
    char *temp;
    va_start(args, count);
    for (i = 0; i < count; i++) {
        temp = va_arg(args, char*);
        argv[i] = (char*)malloc(sizeof(temp+1));
        strcpy(argv[i],temp);
    }
    argv[i] = nullptr;
    va_end(args);
    return argv;
}

SCENARIO("Compiler can be invoked without arguments", "[commands]") {
    GIVEN("an empty argument list") {
        char **args = makeArgv(1, "zephir");

        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        WHEN("invoked without arguments") {
            auto result = commands::parseopt(args, cmd);

            THEN("command is NONE") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::NONE );
            }
        }

        free(args);
    }
}
