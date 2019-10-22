#include <UnitTest++/UnitTest++.h>
#include <cstring>

#include "argv.hpp"
#include "../src/commands/cmd.hpp"

SUITE(commands)
{
    TEST(empty)
    {
        Argv argv({
            "zephir",
            ""
        });

        char **args = argv.argv();

        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        // command is NONE
        CHECK(commands::parseopt(args, cmd));
        CHECK_EQUAL(cmd.kind, commands::NONE);

        // all global options in default state
        CHECK_EQUAL(cmd.quiet, 0);
        CHECK_EQUAL(cmd.common_help, 0);
        CHECK_EQUAL(cmd.version, 0);
        CHECK_EQUAL(cmd.vernum, 0);
        CHECK_EQUAL(cmd.dumpversion, 0);
    }

    TEST(api_empty)
    {
        Argv argv({
            "zephir",
            "api",
            ""
        });

        char **args = argv.argv();

        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        // command is NONE
        CHECK(commands::parseopt(args, cmd));
        CHECK_EQUAL(cmd.kind, commands::API);

        // all API options are in default state
        CHECK(!cmd.api.backend);
        CHECK(!cmd.api.path);
        CHECK(!cmd.api.output);
        CHECK(!cmd.api.options);
        CHECK(!cmd.api.url);
        CHECK(!cmd.api.help);

        // all global options are in default state
        CHECK(!cmd.quiet);
        CHECK(!cmd.common_help);
        CHECK(!cmd.version);
        CHECK(!cmd.vernum);
        CHECK(!cmd.dumpversion);
    }

    TEST(api_help)
    {
        Argv argv({
            "zephir",
            "api",
            "--help",
            ""
        });

        char **args = argv.argv();

        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        // command is NONE
        CHECK(commands::parseopt(args, cmd));
        CHECK_EQUAL(cmd.kind, commands::API);

        // only help option was changed
        CHECK(!cmd.api.backend);
        CHECK(!cmd.api.path);
        CHECK(!cmd.api.output);
        CHECK(!cmd.api.options);
        CHECK(!cmd.api.url);
        CHECK(cmd.api.help);

        // all global options are in default state
        CHECK(!cmd.quiet);
        CHECK(!cmd.common_help);
        CHECK(!cmd.version);
        CHECK(!cmd.vernum);
        CHECK(!cmd.dumpversion);
    }

    TEST(api_full)
    {
        Argv argv({
            "zephir",
            "api",
            "--url=http://test.com",
            "--backend=ZendEngine3",
            "-p", "theme",
            "-o", "out",
            "--options=opts",
            ""
        });

        char **args = argv.argv();

        commands::Cmd cmd;
        std::memset(&cmd, 0, sizeof(cmd));

        // command is NONE
        CHECK(commands::parseopt(args, cmd));
        CHECK_EQUAL(cmd.kind, commands::API);

        // only help option was changed
        CHECK_EQUAL( cmd.api.backend, "ZendEngine3");
        CHECK_EQUAL(cmd.api.path, "theme");
        CHECK_EQUAL(cmd.api.output, "out");
        CHECK_EQUAL(cmd.api.options, "opts");
        CHECK_EQUAL(cmd.api.url, "http://test.com");
        CHECK(!cmd.api.help);
    }
}
