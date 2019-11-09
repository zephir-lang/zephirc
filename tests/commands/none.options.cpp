// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include "argv.hpp"
#include "commands.hpp"

class NoneCmdTest : public ::testing::Test {
 protected:
  NoneCmdTest() = default;
};

TEST_F(NoneCmdTest, RunWithoutOptions) {
  Argv argv({"zephir"});

  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}

TEST_F(NoneCmdTest, RunHelpOption) {
  Argv argv({"zephir", "--help"});

  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_LT(retval, 0);
}
