#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include "zephir/config/extra.hpp"

TEST(ExtraTest, EncodeClass) {
  zephir::config::ExtraPtr metadata =
      std::make_shared<zephir::config::Extra>("spaces", false);

  YAML::Node node;
  node["extra"] = YAML::convert<zephir::config::ExtraPtr>::encode(metadata);

  EXPECT_TRUE(node.IsMap());

  EXPECT_EQ("spaces", node["extra"]["indent"].as<std::string>());
  EXPECT_FALSE(node["extra"]["export-classes"].as<bool>());
}
