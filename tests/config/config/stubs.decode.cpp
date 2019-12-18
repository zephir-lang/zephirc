// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "config/config/stubs.hpp"

TEST(StubsTest, DecodeString) {
  auto yaml = YAML::Load(
      R"(
{
  path: ide/%version%/%namespace%,
  stubs-run-after-generate: false,
  banner: /* header */
})");

  zephir::config::Stubs expected("ide/%version%/%namespace%", false,
                                 "/* header */");
  auto actual = std::make_shared<zephir::config::Stubs>();

  EXPECT_TRUE(YAML::convert<zephir::config::StubsPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(StubsTest, DecodeInvalid) {
  auto node = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Stubs>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::StubsPtr>::decode(node["foo"], actual));
}
