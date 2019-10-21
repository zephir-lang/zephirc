#include "/usr/local/include/criterion/criterion.h"

#include "argv.hpp"
#include "../src/commands/cmd.hpp"

Test(commands, empty)
{
    Argv argv({
        "zephir",
        ""
    });

    char **args = argv.argv();

    commands::Cmd cmd;
    std::memset(&cmd, 0, sizeof(cmd));

    // command is NONE
    cr_assert_eq(commands::parseopt(args, cmd), true);
    cr_assert_eq(cmd.kind, commands::NONE);

    // all global options in default state
    cr_assert_eq(cmd.quiet, 0);
    cr_assert_eq(cmd.common_help, 0);
    cr_assert_eq(cmd.version, 0);
    cr_assert_eq(cmd.vernum, 0);
    cr_assert_eq(cmd.dumpversion, 0);
}

Test(commands, api_empty)
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
    cr_assert_eq(commands::parseopt(args, cmd), true);
    cr_assert_eq(cmd.kind, commands::API);

    // all API options are in default state
    cr_assert_eq(cmd.api.backend, 0);
    cr_assert_eq(cmd.api.path, 0);
    cr_assert_eq(cmd.api.output, 0);
    cr_assert_eq(cmd.api.options, 0);
    cr_assert_eq(cmd.api.url, 0);
    cr_assert_eq(cmd.api.help, 0);

    // all global options are in default state
    cr_assert_eq(cmd.quiet, 0);
    cr_assert_eq(cmd.common_help, 0);
    cr_assert_eq(cmd.version, 0);
    cr_assert_eq(cmd.vernum, 0);
    cr_assert_eq(cmd.dumpversion, 0);
}
