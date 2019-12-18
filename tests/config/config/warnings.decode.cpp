// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "config/config/warnings.hpp"

TEST(WarningsTest, DecodeString) {
  auto yaml = YAML::Load(R"(
{
  unused-variable: true,
  unused-variable-external: false,
  possible-wrong-parameter: true,
  possible-wrong-parameter-undefined: false,
  nonexistent-function: true,
  nonexistent-class: true,
  non-valid-isset: true,
  non-array-update: true,
  non-valid-objectupdate: true,
  non-valid-fetch: true,
  invalid-array-index: true,
  non-array-append: true,
  invalid-return-type: true,
  unreachable-code: true,
  nonexistent-constant: true,
  not-supported-magic-constant: true,
  non-valid-decrement: true,
  non-valid-increment: true,
  non-valid-clone: true,
  non-valid-new: true,
  non-array-access: true,
  invalid-reference: true,
  invalid-typeof-comparison: true,
  conditional-initialization: true
})");

  zephir::config::Warnings expected({
      {"unused-variable", true},
      {"unused-variable-external", false},
      {"possible-wrong-parameter", true},
      {"possible-wrong-parameter-undefined", false},
      {"nonexistent-function", true},
      {"nonexistent-class", true},
      {"non-valid-isset", true},
      {"non-array-update", true},
      {"non-valid-objectupdate", true},
      {"non-valid-fetch", true},
      {"invalid-array-index", true},
      {"non-array-append", true},
      {"invalid-return-type", true},
      {"unreachable-code", true},
      {"nonexistent-constant", true},
      {"not-supported-magic-constant", true},
      {"non-valid-decrement", true},
      {"non-valid-increment", true},
      {"non-valid-clone", true},
      {"non-valid-new", true},
      {"non-array-access", true},
      {"invalid-reference", true},
      {"invalid-typeof-comparison", true},
      {"conditional-initialization", true},
  });

  auto actual = std::make_shared<zephir::config::Warnings>();

  EXPECT_TRUE(YAML::convert<zephir::config::WarningsPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(WarningsTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Warnings>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::WarningsPtr>::decode(yaml["foo"], actual));
}
