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
    EXPECT_TRUE(commands::parseopt(args, cmd));
    EXPECT_EQ(cmd.kind, commands::NONE);

    // all global options in default state
    EXPECT_FALSE(cmd.quiet);
    EXPECT_FALSE(cmd.common_help);
    EXPECT_FALSE(cmd.version);
    EXPECT_FALSE(cmd.vernum);
    EXPECT_FALSE(cmd.dumpversion);
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
    EXPECT_TRUE(commands::parseopt(args, cmd));
    EXPECT_EQ(cmd.kind, commands::API);

    // all API options are in default state
    EXPECT_FALSE(cmd.api.backend);
    EXPECT_FALSE(cmd.api.path);
    EXPECT_FALSE(cmd.api.output);
    EXPECT_FALSE(cmd.api.options);
    EXPECT_FALSE(cmd.api.url);
    EXPECT_FALSE(cmd.api.help);

    // all global options are in default state
    EXPECT_FALSE(cmd.quiet);
    EXPECT_FALSE(cmd.common_help);
    EXPECT_FALSE(cmd.version);
    EXPECT_FALSE(cmd.vernum);
    EXPECT_FALSE(cmd.dumpversion);
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
    EXPECT_TRUE(commands::parseopt(args, cmd));
    EXPECT_EQ(cmd.kind, commands::API);

    // only help option was changed
    EXPECT_FALSE(cmd.api.backend);
    EXPECT_FALSE(cmd.api.path);
    EXPECT_FALSE(cmd.api.output);
    EXPECT_FALSE(cmd.api.options);
    EXPECT_FALSE(cmd.api.url);
    EXPECT_TRUE(cmd.api.help);

    // all global options are in default state
    EXPECT_FALSE(cmd.quiet);
    EXPECT_FALSE(cmd.common_help);
    EXPECT_FALSE(cmd.version);
    EXPECT_FALSE(cmd.vernum);
    EXPECT_FALSE(cmd.dumpversion);
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
    EXPECT_TRUE(commands::parseopt(args, cmd));
    EXPECT_EQ(cmd.kind, commands::API);

    // only help option was changed
    EXPECT_STREQ(cmd.api.backend, "ZendEngine3");
    EXPECT_STREQ(cmd.api.path, "theme");
    EXPECT_STREQ(cmd.api.output, "out");
    EXPECT_STREQ(cmd.api.options, "opts");
    EXPECT_STREQ(cmd.api.url, "http://test.com");
    EXPECT_FALSE(cmd.api.help);
}
