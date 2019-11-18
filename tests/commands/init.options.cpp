// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "commands.hpp"

class InitCmdTest : public ::testing::Test {
 protected:
  InitCmdTest() : argv(){};
  Argv argv;
};

TEST_F(InitCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "init"});
  auto retval = zephir::commands::ParseOptions(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
