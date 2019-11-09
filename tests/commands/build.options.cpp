// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include "argv.hpp"
#include "commands.hpp"

class BuildCmdTest : public ::testing::Test {
 protected:
  BuildCmdTest() = default;
};

TEST_F(BuildCmdTest, RunWithoutOptions) {
  Argv argv({"zephir", "build"});

  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
