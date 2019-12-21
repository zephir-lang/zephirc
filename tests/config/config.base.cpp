// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <cstdio>
#include <string>

#include "asserts.hpp"
#include "config/config.hpp"
#include "env/base.hpp"
#include "filesystem/filesystem.hpp"

using input_t = std::vector<std::string>;

class ConfigBaseTest : public ::testing::Test {
 protected:
  ConfigBaseTest() : argv() {}
  void TearDown() override {
    if (zephir::filesystem::exists("foo")) {
      remove("foo");
    }
  }
  input_t argv;
};

TEST_F(ConfigBaseTest, SimpleConstructor) {
  zephir::Config expected("fake");

  EXPECT_FALSE(expected.changed());
  EXPECT_FALSE(expected.loaded());
}

TEST_F(ConfigBaseTest, DoNothingOnHelp) {
  argv.assign({"--help"});

  // Redirect std::cout
  auto oldCoutStreamBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());

  auto config = zephir::Config::factory(argv, "foo").get();

  // Restore old std::cout
  std::cout.rdbuf(oldCoutStreamBuf);

  EXPECT_FALSE(config->changed());
  EXPECT_FALSE(config->loaded());
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

TEST_F(ConfigBaseTest, CorrectConfigFile) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({});
  auto file = tests_root + "/fixtures/phalcon-4x.yml";
  auto config = zephir::Config::factory(argv, file).get();

  EXPECT_FALSE(config->changed());
  EXPECT_TRUE(config->loaded());
}

TEST_F(ConfigBaseTest, GetValue) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  argv.assign({});
  auto file = tests_root + "/fixtures/legacy.yml";
  auto config = zephir::Config::factory(argv, file);

  auto actual = config->get<std::string>("author", "undefined");
  EXPECT_EQ("Zephir Team", actual);

  actual = config->get<std::string>("foo", "bar");
  EXPECT_EQ("bar", actual);

  auto stubs = config->get<bool>("stubs-run-after-generate", "stubs", true);
  EXPECT_FALSE(stubs);
}

TEST_F(ConfigBaseTest, SetValue) {
  auto config = std::make_shared<zephir::Config>("foo");
  EXPECT_FALSE(config->changed());

  auto silent = config->get<bool>("silent", true);
  EXPECT_FALSE(silent);

  config->set("silent", true);
  silent = config->get<bool>("silent", true);
  EXPECT_TRUE(silent);
  EXPECT_TRUE(config->changed());

  auto warn = config->get("unused-variable", "warnings", false);
  EXPECT_TRUE(warn);

  config->set("unused-variable", "warnings", false);
  warn = config->get("unused-variable", "warnings", false);
  EXPECT_FALSE(warn);
}
