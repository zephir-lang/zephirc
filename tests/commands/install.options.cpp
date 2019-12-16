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
#include <zephir/cli/commands/install_command.hpp>

using namespace zephir::cli::commands;

class InstallCmdTest : public ::testing::Test {
 protected:
  InstallCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(InstallCmdTest, RunWithoutOptions) {
  argv.assign({"install"});
  auto app = std::make_unique<zephir::cli::Application>(argv, "tests");
  app->AddCommand(std::make_unique<InstallCommand>("install"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
