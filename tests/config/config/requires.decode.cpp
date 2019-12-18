// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "config/config/requires.hpp"

TEST(RequiresTest, DecodeString) {
  auto yaml = YAML::Load(R"(
{ extensions: [PDO, SPL, standard, hash, json] })");

  zephir::config::Requires expected({"PDO", "SPL", "standard", "hash", "json"});
  auto actual = std::make_shared<zephir::config::Requires>();

  EXPECT_TRUE(YAML::convert<zephir::config::RequiresPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(RequiresTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Requires>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::RequiresPtr>::decode(yaml["foo"], actual));
}
