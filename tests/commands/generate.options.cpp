// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "console/application.hpp"
#include "console/commands/generate.hpp"

using namespace zephir::console::commands;

class GenerateCmdTest : public ::testing::Test {
 protected:
  GenerateCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(GenerateCmdTest, RunWithoutOptions) {
  argv.assign({"generate"});
  auto config = std::make_shared<zephir::Config>("foo");
  auto app =
      std::make_unique<zephir::console::Application>(config, argv, "tests");
  app->AddCommand(std::make_unique<GenerateCommand>("generate"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
