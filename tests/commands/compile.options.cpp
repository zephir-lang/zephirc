// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include "argv.hpp"
#include "commands.hpp"

class CompileCmdTest : public ::testing::Test {
 protected:
  CompileCmdTest() = default;
};

TEST_F(CompileCmdTest, RunWithoutOptions) {
  Argv argv({"zephir", "compile"});

  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
