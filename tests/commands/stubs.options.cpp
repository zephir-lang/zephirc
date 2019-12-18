// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "cli/application.hpp"
#include "cli/commands/stubs.hpp"

using namespace zephir::cli::commands;

class StubsCmdTest : public ::testing::Test {
 protected:
  StubsCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(StubsCmdTest, RunWithoutOptions) {
  argv.assign({"stubs"});
  auto app = std::make_unique<zephir::cli::Application>(argv, "tests");
  app->AddCommand(std::make_unique<StubsCommand>("stubs"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
