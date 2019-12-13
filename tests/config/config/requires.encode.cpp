#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include "zephir/config/requires.hpp"

TEST(RequiresTest, EncodeClass) {
  std::vector<std::string> extensions = {"PDO", "SPL", "standard", "hash",
                                         "json"};
  zephir::config::RequiresPtr requires =
      std::make_shared<zephir::config::Requires>(extensions);

  YAML::Node node;
  node["requires"] =
      YAML::convert<zephir::config::RequiresPtr>::encode(requires);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(extensions,
            node["requires"]["extensions"].as<std::vector<std::string>>());
}
