// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "config/config/optimizations.hpp"

TEST(OptimizationsTest, DecodeString) {
  auto yaml = YAML::Load(R"(
{
  call-gatherer-pass: true,
  check-invalid-reads: false,
  constant-folding: true,
  internal-call-transformation: false,
  local-context-pass: true,
  static-constant-class-folding: true,
  static-type-inference-second-pass: true,
  static-type-inference: true
})");

  zephir::config::Optimizations expected({
      {"static-type-inference", true},
      {"static-type-inference-second-pass", true},
      {"local-context-pass", true},
      {"constant-folding", true},
      {"static-constant-class-folding", true},
      {"call-gatherer-pass", true},
      {"check-invalid-reads", false},
      {"internal-call-transformation", false},
  });
  auto actual = std::make_shared<zephir::config::Optimizations>();

  EXPECT_TRUE(
      YAML::convert<zephir::config::OptimizationsPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(OptimizationsTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Optimizations>();

  EXPECT_FALSE(YAML::convert<zephir::config::OptimizationsPtr>::decode(
      yaml["foo"], actual));
}
