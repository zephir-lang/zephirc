// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "cli/application.hpp"
#include "cli/commands/build.hpp"

using namespace zephir::cli::commands;

class BuildCmdTest : public ::testing::Test {
 protected:
  BuildCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(BuildCmdTest, RunWithoutOptions) {
  argv.assign({"build"});
  auto app = std::make_unique<zephir::cli::Application>(argv, "tests");
  app->AddCommand(std::make_unique<BuildCommand>("build"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
