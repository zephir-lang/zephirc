// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "zephir/config/stubs.hpp"

TEST(StubsTest, DecodeString) {
  YAML::Node node = YAML::Load(
      R"(stubs: {path: "ide/%version%/%namespace%", stubs-run-after-generate: false, banner: ""})");

  zephir::config::Stubs expected("ide/%version%/%namespace%", false, "");
  zephir::config::StubsPtr actual = std::make_shared<zephir::config::Stubs>();

  EXPECT_TRUE(
      YAML::convert<zephir::config::StubsPtr>::decode(node["stubs"], actual));
  EXPECT_EQ(*actual, expected);
}

TEST(StubsTest, DecodeInvalid) {
  YAML::Node node = YAML::Load("foo: bar");
  zephir::config::StubsPtr actual = std::make_shared<zephir::config::Stubs>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::StubsPtr>::decode(node["foo"], actual));
}
