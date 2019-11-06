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

class InitCmdTest : public ::testing::Test {
 protected:
  InitCmdTest() : options() {}

  commands::Options options;
};

TEST_F(InitCmdTest, InitWithoutParams) {
  Argv argv({"zephir", "init", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // all INIT options are in default state
  EXPECT_FALSE(pr.init.ns);
  EXPECT_FALSE(pr.init.backend);
  EXPECT_FALSE(pr.init.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, HelpOption) {
  Argv argv({"zephir", "init", "--help", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // only help option is changed
  EXPECT_TRUE(pr.init.help);

  // other INIT options are in default state
  EXPECT_FALSE(pr.init.ns);
  EXPECT_FALSE(pr.init.backend);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, InitWithNamespace) {
  Argv argv({"zephir", "init", "phalcon", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // namespace option is changed
  EXPECT_STREQ(pr.init.ns, "phalcon");

  // other INIT options are in default state
  EXPECT_FALSE(pr.init.backend);
  EXPECT_FALSE(pr.init.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, UsingNamespaceOptionsSeparator) {
  Argv argv({"zephir", "init", "--", "test", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // namespace option is changed
  EXPECT_STREQ(pr.init.ns, "test");

  // other INIT options are in default state
  EXPECT_FALSE(pr.init.backend);
  EXPECT_FALSE(pr.init.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, InitWithNamespaceAndBackend) {
  Argv argv({"zephir", "init", "phalcon", "--backend=ZendEngine4", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // namespace and backend options are changed
  EXPECT_STREQ(pr.init.ns, "phalcon");
  EXPECT_STREQ(pr.init.backend, "ZendEngine4");

  // other INIT options are in default state
  EXPECT_FALSE(pr.init.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, InitWithNamespaceAndBackend2) {
  Argv argv({"zephir", "init", "--backend=ZendEngine2", "foo", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // namespace and backend options are changed (order doesn't matter)
  EXPECT_STREQ(pr.init.ns, "foo");
  EXPECT_STREQ(pr.init.backend, "ZendEngine2");

  // other INIT options are in default state
  EXPECT_FALSE(pr.init.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, UsingNamespaceOptionsSeparatorAndBackend) {
  Argv argv({"zephir", "init", "--backend=ZendEngine3", "--", "test", ""});

  // command is INIT
  auto pr = options.parse(argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::INIT);

  // namespace and backend options are changed
  EXPECT_STREQ(pr.init.ns, "test");
  EXPECT_STREQ(pr.init.backend, "ZendEngine3");

  // other INIT options are in default state
  EXPECT_FALSE(pr.init.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(InitCmdTest, InvalidNamespaceFormat) {
  Argv argv({"zephir", "init", "123456789", ""});

  try {
    options.parse(argv.argv());
    FAIL() << "commands::Options::parse() should throw an error" << std::endl;
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
    options.parse(argv.argv());
    FAIL() << "commands::Options::parse() should throw an error" << std::endl;
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
