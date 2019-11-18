// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "commands.hpp"

class HelpCmdTest : public ::testing::Test {
 protected:
  HelpCmdTest() : argv(){};
  Argv argv;
};

TEST_F(HelpCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "help"});
  auto retval = zephir::commands::ParseOptions(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
