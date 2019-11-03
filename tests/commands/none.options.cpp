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
  NoneCmdTest() : options(), cmd() {}

  commands::Cmd cmd;
  commands::Options options;
};

TEST_F(NoneCmdTest, InitWithoutParams) {
  Argv argv({"zephir", ""});

  // command is NONE
  options.parseopt(argv.argv(), cmd);
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
  options.parseopt(argv.argv(), cmd);

  // only help option is chaged
  EXPECT_TRUE(cmd.common.help);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingVersonOptions) {
  Argv argv({"zephir", "--version", ""});
  options.parseopt(argv.argv(), cmd);

  // only version option is chaged
  EXPECT_TRUE(cmd.common.version);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingQuietOptions) {
  Argv argv({"zephir", "--quiet", "--version", "--help", ""});

  try {
    options.parseopt(argv.argv(), cmd);
    FAIL() << "commands::Options::parseopt() should throw an error"
           << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "Command '--quiet' is not defined");
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
  options.parseopt(argv.argv(), cmd);

  // only vernum option is chaged
  EXPECT_TRUE(cmd.common.vernum);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingDumpversionOptions) {
  Argv argv({"zephir", "--dumpversion", "--version", "--help", ""});
  options.parseopt(argv.argv(), cmd);

  // only dumpversion option is chaged
  EXPECT_TRUE(cmd.common.dumpversion);

  // other global options are in default state
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.quiet);
}
