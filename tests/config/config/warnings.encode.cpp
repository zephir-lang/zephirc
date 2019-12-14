// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "zephir/config/warnings.hpp"

TEST(WarningsTest, EncodeClass) {
  std::map<std::string, bool> container = {
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
  };
  auto warnings = std::make_shared<zephir::config::Warnings>(container);

  YAML::Node node;
  node["warnings"] =
      YAML::convert<zephir::config::WarningsPtr>::encode(warnings);

  EXPECT_TRUE(node.IsMap());

  EXPECT_TRUE(node["warnings"]["unused-variable"].as<bool>());
  EXPECT_FALSE(node["warnings"]["unused-variable-external"].as<bool>());
  EXPECT_TRUE(node["warnings"]["possible-wrong-parameter"].as<bool>());
  EXPECT_FALSE(
      node["warnings"]["possible-wrong-parameter-undefined"].as<bool>());
  EXPECT_TRUE(node["warnings"]["nonexistent-function"].as<bool>());
  EXPECT_TRUE(node["warnings"]["nonexistent-class"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-isset"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-array-update"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-objectupdate"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-fetch"].as<bool>());
  EXPECT_TRUE(node["warnings"]["invalid-array-index"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-array-append"].as<bool>());
  EXPECT_TRUE(node["warnings"]["invalid-return-type"].as<bool>());
  EXPECT_TRUE(node["warnings"]["unreachable-code"].as<bool>());
  EXPECT_TRUE(node["warnings"]["nonexistent-constant"].as<bool>());
  EXPECT_TRUE(node["warnings"]["not-supported-magic-constant"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-decrement"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-increment"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-clone"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-valid-new"].as<bool>());
  EXPECT_TRUE(node["warnings"]["non-array-access"].as<bool>());
  EXPECT_TRUE(node["warnings"]["invalid-reference"].as<bool>());
  EXPECT_TRUE(node["warnings"]["invalid-typeof-comparison"].as<bool>());
  EXPECT_TRUE(node["warnings"]["conditional-initialization"].as<bool>());
}