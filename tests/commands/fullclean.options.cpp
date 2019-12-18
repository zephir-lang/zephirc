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
#include "cli/commands/fullclean.hpp"

using namespace zephir::cli::commands;

class FullcleanCmdTest : public ::testing::Test {
 protected:
  FullcleanCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(FullcleanCmdTest, RunWithoutOptions) {
  argv.assign({"fullclean"});
  auto app = std::make_unique<zephir::cli::Application>(argv, "tests");
  app->AddCommand(std::make_unique<FullCleanCommand>("fullclean"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
