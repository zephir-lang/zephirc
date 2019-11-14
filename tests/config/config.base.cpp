// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "asserts.hpp"
#include "config/config.hpp"
#include "env/base.hpp"

class ConfigBaseTest : public ::testing::Test {
 protected:
  ConfigBaseTest() : argv() {}
  Argv argv;
};

TEST_F(ConfigBaseTest, DoNothingOnHelp) {
  argv.assign({"zephir", "--help"});
  zephir::Config config =
      zephir::load_config(argv.argc(), argv.argv(), "non-existent-file");
  EXPECT_FALSE(config.changed);
}

TEST_F(ConfigBaseTest, BrokenConfigFile) {
  std::string tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({"zephir"});
  EXPECT_THROW_EXCEPTION(
      std::runtime_error,
      zephir::load_config(argv.argc(), argv.argv(),
                          tests_root + "/fixtures/bad-config.yml"),
      "Config file is broken");
}
