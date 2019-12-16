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

#include <zephir/cli/application.hpp>
#include <zephir/cli/commands/clean_command.hpp>

using namespace zephir::cli::commands;

class CleanCmdTest : public ::testing::Test {
 protected:
  CleanCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(CleanCmdTest, RunWithoutOptions) {
  argv.assign({"clean"});
  auto app = std::make_unique<zephir::cli::Application>(argv, "tests");
  app->AddCommand(std::make_unique<CleanCommand>("build"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
