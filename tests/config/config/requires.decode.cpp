// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "zephir/config/requires.hpp"

TEST(RequiresTest, DecodeString) {
  YAML::Node node = YAML::Load(
      R"(requires: {extensions: ["PDO", "SPL", "standard", "hash", "json"]})");

  zephir::config::Requires expected({"PDO", "SPL", "standard", "hash", "json"});
  zephir::config::RequiresPtr actual =
      std::make_shared<zephir::config::Requires>();

  EXPECT_TRUE(YAML::convert<zephir::config::RequiresPtr>::decode(
      node["requires"], actual));
  EXPECT_EQ(*actual, expected);
}

TEST(RequiresTest, DecodeInvalid) {
  YAML::Node node = YAML::Load("foo: bar");
  zephir::config::RequiresPtr actual =
      std::make_shared<zephir::config::Requires>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::RequiresPtr>::decode(node["foo"], actual));
}
