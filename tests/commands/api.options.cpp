// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "console/application.hpp"
#include "console/commands/api.hpp"

using namespace zephir::console::commands;

class ApiCmdTest : public ::testing::Test {
 protected:
  ApiCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(ApiCmdTest, RunWithoutOptions) {
  argv.assign({"api"});
  auto app = std::make_unique<zephir::console::Application>(argv, "tests");
  app->AddCommand(std::make_unique<ApiCommand>("api"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
