#include <catch2/catch.hpp>
#include <cstring>

#include "argv.hpp"
#include "../src/commands/cmd.hpp"

SCENARIO("Invoke api command", "[commands]") {
    GIVEN("fresh cmd instance") {
        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        WHEN("invoked without arguments") {
            Argv argv({
                "zephir",
                "api",
                ""
            });

            char **args = argv.argv();
            auto result = commands::parseopt(args, cmd);

            THEN("command is API") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::API );
            }

            THEN("all API options are in default state") {
                REQUIRE( !cmd.api.backend );
                REQUIRE( !cmd.api.path );
                REQUIRE( !cmd.api.output );
                REQUIRE( !cmd.api.options );
                REQUIRE( !cmd.api.url );
                REQUIRE( !cmd.api.help );
            }

            THEN("all global options are in default state") {
                REQUIRE( !cmd.quiet );
                REQUIRE( !cmd.common_help );
                REQUIRE( !cmd.version );
                REQUIRE( !cmd.vernum );
                REQUIRE( !cmd.dumpversion );
            }
        }

        WHEN("invoked with --help argument") {
            Argv argv({
                  "zephir",
                  "api",
                  "--help",
                  ""
            });

            char **args = argv.argv();
            auto result = commands::parseopt(args, cmd);

            THEN("command is API") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::API );
            }

            THEN("only help option was changed") {
                REQUIRE( !cmd.api.backend );
                REQUIRE( !cmd.api.path );
                REQUIRE( !cmd.api.output );
                REQUIRE( !cmd.api.options );
                REQUIRE( !cmd.api.url );
                REQUIRE( cmd.api.help );
            }

            THEN("all global options are in default state") {
                REQUIRE( !cmd.quiet );
                REQUIRE( !cmd.common_help );
                REQUIRE( !cmd.version );
                REQUIRE( !cmd.vernum );
                REQUIRE( !cmd.dumpversion );
            }
        }

        WHEN("invoked with general arguments") {
            Argv argv({
                "zephir",
                "api",
                "--url=http://test.com",
                "--backend=ZendEngine3",
                "-p", "theme",
                "-o", "out",
                "--options=opts"
                ,
                ""
            });

            char **args = argv.argv();
            auto result = commands::parseopt(args, cmd);

            THEN("command is API") {
                REQUIRE( result );
                REQUIRE( cmd.kind == commands::API );
            }

            THEN("general options were changed") {
                REQUIRE( ((std::string) cmd.api.backend) == "ZendEngine3" );
                REQUIRE( ((std::string) cmd.api.path) == "theme" );
                REQUIRE( ((std::string) cmd.api.output) == "out" );
                REQUIRE( ((std::string) cmd.api.options) == "opts" );
                REQUIRE( ((std::string) cmd.api.url) == "http://test.com" );
                REQUIRE( !cmd.api.help );
            }
        }
    }
}
