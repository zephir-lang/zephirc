#include <criterion/criterion.h>

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
    cr_expect(commands::parseopt(args, cmd));
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
    cr_expect(commands::parseopt(args, cmd));
    cr_assert_eq(cmd.kind, commands::API);

    // all API options are in default state
    cr_assert_not(cmd.api.backend);
    cr_assert_not(cmd.api.path);
    cr_assert_not(cmd.api.output);
    cr_assert_not(cmd.api.options);
    cr_assert_not(cmd.api.url);
    cr_assert_not(cmd.api.help);

    // all global options are in default state
    cr_assert_not(cmd.quiet);
    cr_assert_not(cmd.common_help);
    cr_assert_not(cmd.version);
    cr_assert_not(cmd.vernum);
    cr_assert_not(cmd.dumpversion);
}

Test(commands, api_help)
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
    cr_expect(commands::parseopt(args, cmd));
    cr_assert_eq(cmd.kind, commands::API);

    // only help option was changed
    cr_assert_not(cmd.api.backend);
    cr_assert_not(cmd.api.path);
    cr_assert_not(cmd.api.output);
    cr_assert_not(cmd.api.options);
    cr_assert_not(cmd.api.url);
    cr_expect(cmd.api.help);

    // all global options are in default state
    cr_assert_not(cmd.quiet);
    cr_assert_not(cmd.common_help);
    cr_assert_not(cmd.version);
    cr_assert_not(cmd.vernum);
    cr_assert_not(cmd.dumpversion);
}

Test(commands, api_full)
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
    cr_expect(commands::parseopt(args, cmd));
    cr_assert_eq(cmd.kind, commands::API);

    // only help option was changed
    cr_assert_str_eq( cmd.api.backend, "ZendEngine3");
    cr_assert_str_eq(cmd.api.path, "theme");
    cr_assert_str_eq(cmd.api.output, "out");
    cr_assert_str_eq(cmd.api.options, "opts");
    cr_assert_str_eq(cmd.api.url, "http://test.com");
    cr_assert_not(cmd.api.help);

}
