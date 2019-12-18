// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "cli/application.hpp"
#include "cli/commands/init.hpp"

using namespace zephir::cli::commands;

class InitCmdTest : public ::testing::Test {
 protected:
  InitCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(InitCmdTest, RunWithoutOptions) {
  argv.assign({"init"});
  auto app = std::make_unique<zephir::cli::Application>(argv, "tests");
  app->AddCommand(std::make_unique<InitCommand>("init"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
