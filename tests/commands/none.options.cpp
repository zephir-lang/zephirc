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

class NoneCmdTest : public ::testing::Test {
 protected:
  NoneCmdTest() : options() {}

  commands::Options options;
};

TEST_F(NoneCmdTest, InitWithoutParams) {
  Argv argv({"zephir", ""});

  // command is NONE
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::NONE);

  // all global options in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingHelpOptions) {
  Argv argv({"zephir", "--help", ""});
  auto cmd = options.parseopt(argv.argv());

  // only help option is changed
  EXPECT_TRUE(cmd.common.help);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingVersonOptions) {
  Argv argv({"zephir", "--version", ""});
  auto cmd = options.parseopt(argv.argv());

  // only version option is changed
  EXPECT_TRUE(cmd.common.version);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingUndefinedCommandWithOptions) {
  Argv argv({"zephir", "qwerty", "--version", "--help", ""});

  try {
    auto cmd = options.parseopt(argv.argv());
    FAIL() << "commands::Options::parseopt() should throw an error"
           << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "Command \"qwerty\" is not defined.");
  } catch (std::runtime_error &e) {
    FAIL() << "Was expecting commands::OptionException: " << e.what()
           << std::endl;
  } catch (...) {
    FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception
           << std::endl;
  }
}

TEST_F(NoneCmdTest, UsingQuietOptions) {
  Argv argv({"zephir", "--quiet", "--version", "--help", ""});

  try {
    auto cmd = options.parseopt(argv.argv());
    FAIL() << "commands::Options::parseopt() should throw an error"
           << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "Option \"--quiet\" isn't allowed in this context.");
  } catch (std::runtime_error &e) {
    FAIL() << "Was expecting commands::OptionException: " << e.what()
           << std::endl;
  } catch (...) {
    FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception
           << std::endl;
  }
}

TEST_F(NoneCmdTest, UsingVernumOptions) {
  Argv argv({"zephir", "--vernum", ""});
  auto cmd = options.parseopt(argv.argv());

  // only vernum option is changed
  EXPECT_TRUE(cmd.common.vernum);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingDumpversionOptions) {
  Argv argv({"zephir", "--dumpversion", "--version", "--help", ""});
  auto cmd = options.parseopt(argv.argv());

  // only dumpversion option is changed
  EXPECT_TRUE(cmd.common.dumpversion);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.quiet);
}
