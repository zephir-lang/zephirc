// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "zephir/config/optimizations.hpp"

TEST(OptimizationsTest, DecodeString) {
  YAML::Node node = YAML::Load(
      "optimizations: {static-type-inference: true, "
      "static-type-inference-second-pass: true, "
      "local-context-pass: true, "
      "constant-folding: true, "
      "static-constant-class-folding: true, "
      "call-gatherer-pass: true, "
      "check-invalid-reads: false, "
      "internal-call-transformation: false }");

  zephir::config::Optimizations expected(true, true, true, true, true, true,
                                         false, false);
  zephir::config::OptimizationsPtr actual =
      std::make_shared<zephir::config::Optimizations>();

  EXPECT_TRUE(YAML::convert<zephir::config::OptimizationsPtr>::decode(
      node["optimizations"], actual));
  EXPECT_EQ(*actual, expected);
}

TEST(OptimizationsTest, DecodeInvalid) {
  YAML::Node node = YAML::Load("foo: bar");
  zephir::config::OptimizationsPtr actual =
      std::make_shared<zephir::config::Optimizations>();

  EXPECT_FALSE(YAML::convert<zephir::config::OptimizationsPtr>::decode(
      node["foo"], actual));
}
