// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "commands.hpp"

using input_t = std::vector<std::string>;

class CleanCmdTest : public ::testing::Test {
 protected:
  CleanCmdTest() : argv(){};
  input_t argv;
};

TEST_F(CleanCmdTest, RunWithoutOptions) {
  argv.assign({"clean"});
  auto retval = zephir::commands::CreateFromArgv(argv);
  EXPECT_EQ(retval, 0);
}
