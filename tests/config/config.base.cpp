// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "argv.hpp"
#include "asserts.hpp"
#include "env/base.hpp"
#include "zephir/config.hpp"

class ConfigBaseTest : public ::testing::Test {
 protected:
  ConfigBaseTest() : argv() {}
  Argv argv;
};

TEST_F(ConfigBaseTest, DoNothingOnHelp) {
  argv.assign({"zephir", "--help"});

  // Redirect std::cout
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  zephir::Config config =
      zephir::Config::CreateFromArgv(argv.argc(), argv.argv(), "foo");

  // Restore old std::cout
  std::cout.rdbuf(oldCoutStreamBuf);

  EXPECT_FALSE(config.IsChanged());
}

TEST_F(ConfigBaseTest, BrokenConfigFile) {
  std::string tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({"zephir"});
  std::string file = tests_root + "/fixtures/bad-config.yml";
  EXPECT_THROW_EXCEPTION(
      std::runtime_error,
      zephir::Config::CreateFromArgv(argv.argc(), argv.argv(), file),
      "Config file is broken");
}

TEST_F(ConfigBaseTest, CorrectConfigFile) {
  std::string tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({"zephir"});
  std::string file = tests_root + "/fixtures/phalcon-4x.yml";
  zephir::Config config =
      zephir::Config::CreateFromArgv(argv.argc(), argv.argv(), file);

  EXPECT_FALSE(config.IsChanged());
}
