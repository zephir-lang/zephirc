// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "zephir/commands.hpp"

using input_t = std::vector<std::string>;

class InitCmdTest : public ::testing::Test {
 protected:
  InitCmdTest() : argv(){};
  input_t argv;
};

TEST_F(InitCmdTest, RunWithoutOptions) {
  argv.assign({"init"});
  auto retval = zephir::commands::CreateFromArgv(argv);
  EXPECT_EQ(retval, 0);
}
