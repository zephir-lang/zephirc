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
  CompileCmdTest() : argv(){};
  Argv argv;
};

TEST_F(CompileCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "compile"});
  auto retval = zephir::commands::CreateFromArgv(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
