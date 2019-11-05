// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <cstring>

// TODO: Make it better
#include "../../src/commands/cmd.hpp"
#include "../../src/commands/optionexception.hpp"
#include "../../src/commands/options.hpp"
#include "../argv.hpp"

class ApiCmdTest : public ::testing::Test {
 protected:
  ApiCmdTest() : options() {}

  commands::Options options;
};

TEST_F(ApiCmdTest, InitWithoutParams) {
  Argv argv({"zephir", "api", ""});

  // command is API
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::API);

  // all API options are in default state
  EXPECT_FALSE(cmd.api.backend);
  EXPECT_FALSE(cmd.api.path);
  EXPECT_FALSE(cmd.api.output);
  EXPECT_FALSE(cmd.api.options);
  EXPECT_FALSE(cmd.api.url);
  EXPECT_FALSE(cmd.api.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(ApiCmdTest, UsingHelp) {
  Argv argv({"zephir", "api", "--help", ""});

  // command is API
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::API);

  // only help option was changed
  EXPECT_TRUE(cmd.api.help);

  // other API options are in default state
  EXPECT_FALSE(cmd.api.backend);
  EXPECT_FALSE(cmd.api.path);
  EXPECT_FALSE(cmd.api.output);
  EXPECT_FALSE(cmd.api.options);
  EXPECT_FALSE(cmd.api.url);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(ApiCmdTest, TypicalUsage) {
  Argv argv({"zephir", "api", "--url=http://test.com", "--backend=ZendEngine3",
             "-p", "theme", "-o", "out", "--options=opts", ""});

  // command is API
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::API);

  // API options are changed
  EXPECT_STREQ(cmd.api.backend, "ZendEngine3");
  EXPECT_STREQ(cmd.api.path, "theme");
  EXPECT_STREQ(cmd.api.output, "out");
  EXPECT_STREQ(cmd.api.options, "opts");
  EXPECT_STREQ(cmd.api.url, "http://test.com");
  EXPECT_FALSE(cmd.api.help);
}

TEST_F(ApiCmdTest, ThrowExceptionOnIncorrectOption) {
  Argv argv({"zephir", "api", "--foo", ""});

  try {
    auto cmd = options.parseopt(argv.argv());
    FAIL() << "commands::Options::parseopt() should throw an error"
           << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "The \"--foo\" option does not exist.");
  } catch (std::runtime_error &e) {
    FAIL() << "Was expecting commands::OptionException: " << e.what()
           << std::endl;
  } catch (...) {
    FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception
           << std::endl;
  }
}
