// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "config/config/extra.hpp"

TEST(ExtraTest, DecodeString) {
  auto yaml = YAML::Load(R"({indent: spaces, export-classes: false})");
  auto actual = std::make_shared<zephir::config::Extra>();

  zephir::config::Extra expected("spaces", false);

  EXPECT_TRUE(YAML::convert<zephir::config::ExtraPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(ExtraTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Extra>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::ExtraPtr>::decode(yaml["foo"], actual));
}
