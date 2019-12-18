// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "console/application.hpp"
#include "console/commands/compile.hpp"

using namespace zephir::console::commands;

class CompileCmdTest : public ::testing::Test {
 protected:
  CompileCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(CompileCmdTest, RunWithoutOptions) {
  argv.assign({"compile"});
  auto app = std::make_unique<zephir::console::Application>(argv, "tests");
  app->AddCommand(std::make_unique<CompileCommand>("compile"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
