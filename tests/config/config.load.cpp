// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "asserts.hpp"
#include "config/config.hpp"
#include "config_tester.hpp"

TEST_F(ConfigBaseTest, LoadConfigFile) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({});
  auto file = tests_root + "/fixtures/phalcon-4x.yml";
  auto config = zephir::Config::factory(argv, file);

  auto actual = config->get<std::string>("namespace", "undefined");
  EXPECT_EQ("phalcon", actual);
}

TEST_F(ConfigBaseTest, BrokenConfigFile) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({});
  auto file = tests_root + "/fixtures/bad-config.yml";
  EXPECT_THROW_EXCEPTION(std::runtime_error,
                         zephir::Config::factory(argv, file),
                         "Config file is broken");
}
