// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "commands.hpp"

class CleanCmdTest : public ::testing::Test {
 protected:
  CleanCmdTest() : argv(){};
  Argv argv;
};

TEST_F(CleanCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "clean"});
  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
