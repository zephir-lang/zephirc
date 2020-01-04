// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "config/config.hpp"
#include "properties.hpp"
#include "tester.hpp"

TEST_F(ConfigBaseTest, GetValue) {
  argv.assign({});
  auto file = std::string(TESTS_ROOT) + "/fixtures/legacy.yml";
  auto config = zephir::Config::factory(argv, file);

  auto actual = config->get<std::string>("author", "undefined");
  EXPECT_EQ("Phalcon Team", actual);

  actual = config->get<std::string>("foo", "bar");
  EXPECT_EQ("bar", actual);

  auto stubs = config->get<bool>("stubs-run-after-generate", "stubs", true);
  EXPECT_FALSE(stubs);
}

TEST_F(ConfigBaseTest, SetValue) {
  auto config = std::make_shared<zephir::Config>("fake");

  auto silent = config->get<bool>("silent", true);
  EXPECT_FALSE(silent);

  config->set("silent", true);
  silent = config->get<bool>("silent", true);
  EXPECT_TRUE(silent);

  EXPECT_TRUE(config->get("unused-variable", "warnings", false));

  config->set("unused-variable", "warnings", false);
  EXPECT_FALSE(config->get("unused-variable", "warnings", false));

  config->set("test", "", true);
  EXPECT_FALSE(config->get("test", false));
  EXPECT_FALSE(config->get("test", "", false));
}

TEST_F(ConfigBaseTest, FindValue) {
  zephir::Config expected("fake");

  EXPECT_FALSE(expected.has("foo"));
  EXPECT_FALSE(expected.has("foo", "bar"));

  EXPECT_TRUE(expected.has("name"));
  EXPECT_TRUE(expected.has("unused-variable", "warnings"));
}
