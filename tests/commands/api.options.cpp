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

class ApiCmdTest : public ::testing::Test {
 protected:
  ApiCmdTest() : options() {}

  commands::Options options;
};

TEST_F(ApiCmdTest, InitWithoutParams) {
  Argv argv({"zephir", "api", ""});

  // command is API
  auto pr = options.parseopt(argv.argc(), argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::API);

  // all API options are in default state
  EXPECT_FALSE(pr.api.backend);
  EXPECT_FALSE(pr.api.path);
  EXPECT_FALSE(pr.api.output);
  EXPECT_FALSE(pr.api.options);
  EXPECT_FALSE(pr.api.url);
  EXPECT_FALSE(pr.api.help);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(ApiCmdTest, UsingHelp) {
  Argv argv({"zephir", "api", "--help", ""});

  // command is API
  auto pr = options.parseopt(argv.argc(), argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::API);

  // only help option was changed
  EXPECT_TRUE(pr.api.help);

  // other API options are in default state
  EXPECT_FALSE(pr.api.backend);
  EXPECT_FALSE(pr.api.path);
  EXPECT_FALSE(pr.api.output);
  EXPECT_FALSE(pr.api.options);
  EXPECT_FALSE(pr.api.url);

  // all global options are in default state
  EXPECT_FALSE(pr.common.quiet);
  EXPECT_FALSE(pr.common.help);
  EXPECT_FALSE(pr.common.version);
  EXPECT_FALSE(pr.common.vernum);
  EXPECT_FALSE(pr.common.dumpversion);
}

TEST_F(ApiCmdTest, TypicalUsage) {
  Argv argv({"zephir", "api", "--url=http://test.com", "--backend=ZendEngine3",
             "-p", "theme", "-o", "out", "--options=opts", ""});

  // command is API
  auto pr = options.parseopt(argv.argc(), argv.argv());
  EXPECT_EQ(pr.get_kind(), commands::CmdKind::API);

  // API options are changed
  EXPECT_STREQ(pr.api.backend, "ZendEngine3");
  EXPECT_STREQ(pr.api.path, "theme");
  EXPECT_STREQ(pr.api.output, "out");
  EXPECT_STREQ(pr.api.options, "opts");
  EXPECT_STREQ(pr.api.url, "http://test.com");
  EXPECT_FALSE(pr.api.help);
}

TEST_F(ApiCmdTest, ThrowExceptionOnIncorrectOption) {
  Argv argv({"zephir", "api", "--foo", ""});

  try {
    options.parseopt(argv.argc(), argv.argv());
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
