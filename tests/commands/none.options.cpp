// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

// TODO(klay): Make it better.
#include "../../src/commands/optionexception.hpp"
#include "../../src/commands/options.hpp"
#include "../../src/commands/parse_result.hpp"
#include "../argv.hpp"

class NoneCmdTest : public ::testing::Test {
 protected:
  NoneCmdTest() : options() {}

  commands::Options options;
};

TEST_F(NoneCmdTest, InitWithoutParams) {
  Argv argv({});

  // command is NONE
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::NONE);

  // all global options in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingHelpOptions) {
  Argv argv({"--help"});
  auto pr = options.parse(argv.argv());

  // only help option is changed
  EXPECT_TRUE(pr.common.help);

  // other global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingVersonOptions) {
  Argv argv({"--version"});
  auto pr = options.parse(argv.argv());

  // only version option is changed
  EXPECT_TRUE(pr.common.version);

  // other global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingUndefinedCommandWithOptions) {
  Argv argv({"qwerty", "--version", "--help"});

  try {
    options.parse(argv.argv());
    FAIL() << "commands::Options::parse() should throw an error" << std::endl;
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
  Argv argv({"--quiet", "--version", "--help"});

  try {
    options.parse(argv.argv());
    FAIL() << "commands::Options::parse() should throw an error" << std::endl;
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
  Argv argv({"--vernum"});
  auto pr = options.parse(argv.argv());

  // only vernum option is changed
  EXPECT_TRUE(pr.common.vernum);

  // other global options are in default state
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(NoneCmdTest, UsingDumpversionOptions) {
  Argv argv({"--dumpversion", "--version", "--help"});
  auto pr = options.parse(argv.argv());

  // only dumpversion option is changed
  EXPECT_TRUE(pr.common.dumpversion);

  // other global options are in default state
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.quiet);
}
