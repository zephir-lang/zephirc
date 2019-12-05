// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "commands.hpp"

class ApiCmdTest : public ::testing::Test {
 protected:
  ApiCmdTest() : argv(){};
  Argv argv;
};

TEST_F(ApiCmdTest, RunWithoutOptions) {
  argv.assign({"zephir", "api"});
  auto retval = zephir::commands::CreateFromArgv(argv.argc(), argv.argv());
  EXPECT_EQ(retval, 0);
}
