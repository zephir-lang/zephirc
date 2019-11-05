// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

// TODO(klay): Make it better.
#include "../../src/commands/cmd.hpp"
#include "../../src/commands/optionexception.hpp"
#include "../../src/commands/options.hpp"
#include "../argv.hpp"

class InitCmdTest : public ::testing::Test {
 protected:
  InitCmdTest() : options() {}

  commands::Options options;
};

TEST_F(InitCmdTest, InitWithoutParams) {
  Argv argv({"zephir", "init", ""});

  // command is INIT
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::INIT);

  // all INIT options are in default state
  EXPECT_FALSE(cmd.init.ns);
  EXPECT_FALSE(cmd.init.backend);
  EXPECT_FALSE(cmd.init.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(InitCmdTest, InitWithNamespace) {
  Argv argv({"zephir", "init", "phalcon", ""});

  // command is INIT
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::INIT);

  // namespace option is changed
  EXPECT_STREQ(cmd.init.ns, "phalcon");

  // other INIT options are in default state
  EXPECT_FALSE(cmd.init.backend);
  EXPECT_FALSE(cmd.init.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(InitCmdTest, UsingNamespaceOptionsSeparator) {
  Argv argv({"zephir", "init", "--", "test", ""});

  // command is INIT
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::INIT);

  // namespace option is changed
  EXPECT_STREQ(cmd.init.ns, "test");

  // other INIT options are in default state
  EXPECT_FALSE(cmd.init.backend);
  EXPECT_FALSE(cmd.init.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(InitCmdTest, InitWithNamespaceAndBackend) {
  Argv argv({"zephir", "init", "phalcon", "--backend=ZendEngine4", ""});

  // command is INIT
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::INIT);

  // namespace and backend options are changed
  EXPECT_STREQ(cmd.init.ns, "phalcon");
  EXPECT_STREQ(cmd.init.backend, "ZendEngine4");

  // other INIT options are in default state
  EXPECT_FALSE(cmd.init.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(InitCmdTest, InitWithNamespaceAndBackend2) {
  Argv argv({"zephir", "init", "--backend=ZendEngine2", "foo", ""});

  // command is INIT
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::INIT);

  // namespace and backend options are changed (order doesn't matter)
  EXPECT_STREQ(cmd.init.ns, "foo");
  EXPECT_STREQ(cmd.init.backend, "ZendEngine2");

  // other INIT options are in default state
  EXPECT_FALSE(cmd.init.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(InitCmdTest, UsingNamespaceOptionsSeparatorAndBackend) {
  Argv argv({"zephir", "init", "--backend=ZendEngine3", "--", "test", ""});

  // command is INIT
  auto cmd = options.parseopt(argv.argv());
  EXPECT_EQ(cmd.kind, commands::CmdKind::INIT);

  // namespace and backend options are changed
  EXPECT_STREQ(cmd.init.ns, "test");
  EXPECT_STREQ(cmd.init.backend, "ZendEngine3");

  // other INIT options are in default state
  EXPECT_FALSE(cmd.init.help);

  // all global options are in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}

TEST_F(InitCmdTest, InvalidNamespaceFormat) {
  Argv argv({"zephir", "init", "123456789", ""});

  try {
    auto cmd = options.parseopt(argv.argv());
    FAIL() << "commands::Options::parseopt() should throw an error"
           << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "Invalid namespace format: \"123456789\".");
  } catch (std::runtime_error &e) {
    FAIL() << "Was expecting commands::OptionException: " << e.what()
           << std::endl;
  } catch (...) {
    FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception
           << std::endl;
  }
}

TEST_F(InitCmdTest, InvalidNamespaceFormat2) {
  Argv argv({"zephir", "init", "test ns", ""});

  try {
    auto cmd = options.parseopt(argv.argv());
    FAIL() << "commands::Options::parseopt() should throw an error"
           << std::endl;
  } catch (commands::OptionException &e) {
    EXPECT_STREQ(e.what(), "Invalid namespace format: \"test ns\".");
  } catch (std::runtime_error &e) {
    FAIL() << "Was expecting commands::OptionException: " << e.what()
           << std::endl;
  } catch (...) {
    FAIL() << "ERROR: Unexpected exception thrown: " << std::current_exception
           << std::endl;
  }
}
