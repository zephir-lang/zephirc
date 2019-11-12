// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "commands.hpp"

class InstallCmdTest : public ::testing::Test {
 protected:
  InstallCmdTest() : argv(){};
  Argv argv;
};

TEST_F(InstallCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "install"});
  auto retval = zephir::commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
