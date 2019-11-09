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
  NoneCmdTest(): argv() {};
  Argv argv;
};

TEST_F(NoneCmdTest, RunWithoutOptions) {
  argv.assign({"zephir"});
  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}

TEST_F(NoneCmdTest, RunHelpOption) {
  argv.assign({"zephir", "--help"});
  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, ZEPHIR_COMMANDS_EXIT_HELP);
}
