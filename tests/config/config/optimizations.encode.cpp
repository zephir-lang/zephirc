// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include "config/config/optimizations.hpp"

TEST(OptimizationsTest, EncodeClass) {
  std::map<std::string, bool> container = {
      {"static-type-inference", true},
      {"static-type-inference-second-pass", true},
      {"local-context-pass", true},
      {"constant-folding", true},
      {"static-constant-class-folding", true},
      {"call-gatherer-pass", true},
      {"check-invalid-reads", false},
      {"internal-call-transformation", false},
  };

  auto opt = std::make_shared<zephir::config::Optimizations>(container);
  auto yaml = YAML::convert<zephir::config::OptimizationsPtr>::encode(opt);

  EXPECT_TRUE(yaml.IsMap());

  EXPECT_TRUE(yaml["static-type-inference"].as<bool>());
  EXPECT_TRUE(yaml["static-type-inference-second-pass"].as<bool>());
  EXPECT_TRUE(yaml["local-context-pass"].as<bool>());
  EXPECT_TRUE(yaml["constant-folding"].as<bool>());
  EXPECT_TRUE(yaml["static-constant-class-folding"].as<bool>());
  EXPECT_TRUE(yaml["call-gatherer-pass"].as<bool>());
  EXPECT_FALSE(yaml["check-invalid-reads"].as<bool>());
  EXPECT_FALSE(yaml["internal-call-transformation"].as<bool>());
}
