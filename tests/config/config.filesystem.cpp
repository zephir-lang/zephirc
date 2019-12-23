// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "asserts.hpp"
#include "config/config.hpp"
#include "filesystem/filesystem.hpp"
#include "tester.hpp"

TEST_F(ConfigBaseTest, LoadConfigFile) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({});
  auto file = tests_root + "/fixtures/config/phalcon-4x.yml";
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
  auto file = tests_root + "/fixtures/config/bad-config.yml";
  EXPECT_THROW_EXCEPTION(std::runtime_error,
                         zephir::Config::factory(argv, file),
                         "Config file is broken");
}

TEST_F(ConfigBaseTest, DumpConfigFile) {
  if (zephir::filesystem::exists("empty")) {
    remove("empty");
  }

  argv.assign({});

  auto config1 = zephir::Config::factory(argv, "empty");
  auto name = config1->get<std::string>("name", "");
  EXPECT_EQ("", name);

  config1->dump("empty");
  EXPECT_TRUE(zephir::filesystem::exists("empty"));
}
