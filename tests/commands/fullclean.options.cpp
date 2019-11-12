// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "commands.hpp"

class FullcleanCmdTest : public ::testing::Test {
 protected:
  FullcleanCmdTest() : argv(){};
  Argv argv;
};

TEST_F(FullcleanCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "fullclean"});
  auto retval = zephir::commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
