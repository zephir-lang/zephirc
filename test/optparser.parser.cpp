#include <gtest/gtest.h>
#include <cstring>

#include "../src/commands/cmd.hpp"
#include "../src/commands/optionexception.hpp"
#include "argv.hpp"

TEST(optparser, without_params) {
  Argv argv({"zephir", ""});
  char **args = argv.argv();

  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  // command is NONE
  EXPECT_TRUE(commands::parseopt(args, cmd));
  EXPECT_EQ(cmd.kind, commands::CmdKind::NONE);

  // all global options in default state
  EXPECT_FALSE(cmd.quiet);
  EXPECT_FALSE(cmd.common_help);
  EXPECT_FALSE(cmd.version);
  EXPECT_FALSE(cmd.vernum);
  EXPECT_FALSE(cmd.dumpversion);
}

TEST(optparser, api_without_params) {
  Argv argv({"zephir", "api", ""});
  char **args = argv.argv();

  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  // command is NONE
  EXPECT_TRUE(commands::parseopt(args, cmd));
  EXPECT_EQ(cmd.kind, commands::CmdKind::API);

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

TEST(optparser, api_using_help) {
  Argv argv({"zephir", "api", "--help", ""});
  char **args = argv.argv();

  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  // command is NONE
  EXPECT_TRUE(commands::parseopt(args, cmd));
  EXPECT_EQ(cmd.kind, commands::CmdKind::API);

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

TEST(optparser, api_typical_usage) {
  Argv argv({"zephir", "api", "--url=http://test.com", "--backend=ZendEngine3",
             "-p", "theme", "-o", "out", "--options=opts", ""});
  char **args = argv.argv();

  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  // command is API
  EXPECT_TRUE(commands::parseopt(args, cmd));
  EXPECT_EQ(cmd.kind, commands::CmdKind::API);

  // API options should be changed
  EXPECT_STREQ(cmd.api.backend, "ZendEngine3");
  EXPECT_STREQ(cmd.api.path, "theme");
  EXPECT_STREQ(cmd.api.output, "out");
  EXPECT_STREQ(cmd.api.options, "opts");
  EXPECT_STREQ(cmd.api.url, "http://test.com");
  EXPECT_FALSE(cmd.api.help);
}

TEST(optparser, api_throw_exception) {
  Argv argv({"zephir", "api", "--foo", ""});
  char **args = argv.argv();

  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

  try {
    commands::parseopt(args, cmd);
    FAIL() << "commands::parseopt() should throw an error" << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "The '--foo' option does not exist");
  } catch (std::runtime_error &e) {
    FAIL() << "Was expecting commands::OptionException: " << e.what()
           << std::endl;
  } catch (...) {
    FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception
           << std::endl;
  }
}
