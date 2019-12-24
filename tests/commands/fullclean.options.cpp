// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "console/application.hpp"
#include "console/commands/fullclean.hpp"

using namespace zephir::console::commands;

class FullcleanCmdTest : public ::testing::Test {
 protected:
  FullcleanCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(FullcleanCmdTest, RunWithoutOptions) {
  argv.assign({"fullclean"});
  auto config = std::make_shared<zephir::Config>("foo");
  auto app =
      std::make_unique<zephir::console::Application>(config, argv, "tests");
  app->AddCommand(std::make_unique<FullCleanCommand>("fullclean"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
