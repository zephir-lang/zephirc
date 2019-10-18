#include <catch2/catch.hpp>

#include "test_helpers.hpp"
#include "../src/commands/cmd.hpp"

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
