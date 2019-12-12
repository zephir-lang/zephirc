#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "zephir/config/extra.hpp"

TEST(ExtraTest, DecodeString) {
  YAML::Node node =
      YAML::Load("extra: {indent: \"spaces\", export-classes: false }");

  zephir::config::Extra expected("spaces", false);
  zephir::config::ExtraPtr actual = std::make_shared<zephir::config::Extra>();

  EXPECT_TRUE(
      YAML::convert<zephir::config::ExtraPtr>::decode(node["extra"], actual));
  EXPECT_EQ(*actual, expected);
}

TEST(ExtraTest, DecodeInvalid) {
  YAML::Node node = YAML::Load("foo: bar");
  zephir::config::ExtraPtr actual = std::make_shared<zephir::config::Extra>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::ExtraPtr>::decode(node["foo"], actual));
}
