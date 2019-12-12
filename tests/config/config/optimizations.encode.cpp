#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include "zephir/config/optimizations.hpp"

TEST(OptimizationsTest, EncodeClass) {
  zephir::config::OptimizationsPtr opt =
      std::make_shared<zephir::config::Optimizations>(true, true, true, true,
                                                      true, true, false, false);

  YAML::Node node;
  node["optimizations"] =
      YAML::convert<zephir::config::OptimizationsPtr>::encode(opt);

  EXPECT_TRUE(node.IsMap());

  EXPECT_TRUE(node["optimizations"]["static-type-inference"].as<bool>());
  EXPECT_TRUE(
      node["optimizations"]["static-type-inference-second-pass"].as<bool>());
  EXPECT_TRUE(node["optimizations"]["local-context-pass"].as<bool>());
  EXPECT_TRUE(node["optimizations"]["constant-folding"].as<bool>());
  EXPECT_TRUE(
      node["optimizations"]["static-constant-class-folding"].as<bool>());
  EXPECT_TRUE(node["optimizations"]["call-gatherer-pass"].as<bool>());
  EXPECT_FALSE(node["optimizations"]["check-invalid-reads"].as<bool>());
  EXPECT_FALSE(
      node["optimizations"]["internal-call-transformation"].as<bool>());
}
