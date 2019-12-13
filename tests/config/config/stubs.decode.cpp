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
  auto node = YAML::Load(
      R"(stubs: {path: "ide/%version%/%namespace%", stubs-run-after-generate: false, banner: ""})");

  zephir::config::Stubs expected("ide/%version%/%namespace%", false, "");
  auto actual = std::make_shared<zephir::config::Stubs>();

  EXPECT_TRUE(
      YAML::convert<zephir::config::StubsPtr>::decode(node["stubs"], actual));
  EXPECT_EQ(*actual, expected);
}

TEST(StubsTest, DecodeInvalid) {
  auto node = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Stubs>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::StubsPtr>::decode(node["foo"], actual));
}
