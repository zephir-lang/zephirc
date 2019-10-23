#include <gtest/gtest.h>

#include "argv.hpp"
#include "../src/commands/cmd.hpp"

TEST(optparser, without_params)
{
    Argv argv({
                  "zephir",
                  ""
              });

    char **args = argv.argv();

    commands::Cmd cmd;
    std::memset(&cmd, 0, sizeof(cmd));

    // command is NONE
    ASSERT_TRUE(commands::parseopt(args, cmd));
    ASSERT_EQ(cmd.kind, commands::NONE);

    // all global options in default state
    ASSERT_FALSE(cmd.quiet);
    ASSERT_FALSE(cmd.common_help);
    ASSERT_FALSE(cmd.version);
    ASSERT_FALSE(cmd.vernum);
    ASSERT_FALSE(cmd.dumpversion);
}

TEST(optparser, api_without_params)
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
    ASSERT_TRUE(commands::parseopt(args, cmd));
    ASSERT_EQ(cmd.kind, commands::API);

    // all API options are in default state
    ASSERT_FALSE(cmd.api.backend);
    ASSERT_FALSE(cmd.api.path);
    ASSERT_FALSE(cmd.api.output);
    ASSERT_FALSE(cmd.api.options);
    ASSERT_FALSE(cmd.api.url);
    ASSERT_FALSE(cmd.api.help);

    // all global options are in default state
    ASSERT_FALSE(cmd.quiet);
    ASSERT_FALSE(cmd.common_help);
    ASSERT_FALSE(cmd.version);
    ASSERT_FALSE(cmd.vernum);
    ASSERT_FALSE(cmd.dumpversion);
}

TEST(optparser, api_using_help)
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
    ASSERT_TRUE(commands::parseopt(args, cmd));
    ASSERT_EQ(cmd.kind, commands::API);

    // only help option was changed
    ASSERT_FALSE(cmd.api.backend);
    ASSERT_FALSE(cmd.api.path);
    ASSERT_FALSE(cmd.api.output);
    ASSERT_FALSE(cmd.api.options);
    ASSERT_FALSE(cmd.api.url);
    ASSERT_TRUE(cmd.api.help);

    // all global options are in default state
    ASSERT_FALSE(cmd.quiet);
    ASSERT_FALSE(cmd.common_help);
    ASSERT_FALSE(cmd.version);
    ASSERT_FALSE(cmd.vernum);
    ASSERT_FALSE(cmd.dumpversion);
}

TEST(optparser, api_typical_usage)
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
    ASSERT_TRUE(commands::parseopt(args, cmd));
    ASSERT_EQ(cmd.kind, commands::API);

    // only help option was changed
    ASSERT_STREQ( cmd.api.backend, "ZendEngine3");
    ASSERT_STREQ(cmd.api.path, "theme");
    ASSERT_STREQ(cmd.api.output, "out");
    ASSERT_STREQ(cmd.api.options, "opts");
    ASSERT_STREQ(cmd.api.url, "http://test.com");
    ASSERT_FALSE(cmd.api.help);
}
