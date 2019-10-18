#include <catch2/catch.hpp>
#include <cstring>

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

            THEN("all global options in default state") {
                REQUIRE( !cmd.quiet );
                REQUIRE( !cmd.common_help );
                REQUIRE( !cmd.version );
                REQUIRE( !cmd.vernum );
                REQUIRE( !cmd.dumpversion );
            }
        }

        free(args);
    }
}

SCENARIO("Invoke api command", "[commands]") {
    GIVEN("fresh cmd instance") {
        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        WHEN("invoked without arguments") {
            char **args = makeArgv(2, "zephir", "api");
            auto result = commands::parseopt(args, cmd);

            THEN("command is API") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::API );
            }

            THEN("all API options in default state") {
                REQUIRE( !cmd.api.backend );
                REQUIRE( !cmd.api.path );
                REQUIRE( !cmd.api.output );
                REQUIRE( !cmd.api.options );
                REQUIRE( !cmd.api.url );
                REQUIRE( !cmd.api.help );
            }

            THEN("all global options in default state") {
                REQUIRE( !cmd.quiet );
                REQUIRE( !cmd.common_help );
                REQUIRE( !cmd.version );
                REQUIRE( !cmd.vernum );
                REQUIRE( !cmd.dumpversion );
            }

            free(args);
        }

        WHEN("invoked with --help argument") {
            char **args = makeArgv(3, "zephir", "api", "--help");
            auto result = commands::parseopt(args, cmd);

            THEN("command is API") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::API );
            }

            THEN("only help option is changed") {
                REQUIRE( !cmd.api.backend );
                REQUIRE( !cmd.api.path );
                REQUIRE( !cmd.api.output );
                REQUIRE( !cmd.api.options );
                REQUIRE( !cmd.api.url );
                REQUIRE( cmd.api.help );
            }

            THEN("all global options in default state") {
                REQUIRE( !cmd.quiet );
                REQUIRE( !cmd.common_help );
                REQUIRE( !cmd.version );
                REQUIRE( !cmd.vernum );
                REQUIRE( !cmd.dumpversion );
            }

            free(args);
        }

        WHEN("invoked with general arguments") {
            char **args = makeArgv(9, "zephir", "api",
                    "--backend=ZendEngine3", "-p", "theme", "-o", "out",
                    "--options=opts", "--url=http://test.com");
            auto result = commands::parseopt(args, cmd);

            THEN("command is API") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::API );
            }

            THEN("general options was changed") {
                REQUIRE( (std::string) cmd.api.backend == "ZendEngine3" );
                REQUIRE( (std::string) cmd.api.path == "theme" );
                REQUIRE( (std::string) cmd.api.output == "out" );
                REQUIRE( (std::string) cmd.api.options == "opts" );
                REQUIRE( (std::string) cmd.api.url == "http://test.com" );
                REQUIRE( !cmd.api.help );
            }

            free(args);
        }
    }
}
