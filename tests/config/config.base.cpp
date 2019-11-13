// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "config/config.hpp"

class ConfigBaseTest : public ::testing::Test {
 protected:
  ConfigBaseTest() : argv(){};
  Argv argv;
};

TEST_F(ConfigBaseTest, DoNothingOnHelp) {
  argv.assign({"zephir", "--help"});
  zephir::Config config =
      zephir::load_config(argv.argc(), argv.argv(), "non-existent-file");
  EXPECT_FALSE(config.changed);
}
