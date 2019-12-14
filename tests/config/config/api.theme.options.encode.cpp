// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <zephir/config/api/theme/options.hpp>

namespace ztheme = zephir::config::api::theme;

TEST(ApiOptionsTest, EncodeClass) {
  std::map<std::string, std::string> container = {
      {"github", ""},
      {"analytics", ""},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  };
  auto warnings = std::make_shared<ztheme::Options>(container);

  YAML::Node node;
  node["options"] = YAML::convert<ztheme::OptionsPtr>::encode(warnings);

  EXPECT_TRUE(node.IsMap());

  EXPECT_EQ("", node["options"]["github"].as<std::string>());
  EXPECT_EQ("", node["options"]["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496", node["options"]["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496", node["options"]["link_color"].as<std::string>());
  EXPECT_EQ("#5F9AE7", node["options"]["link_hover_color"].as<std::string>());
}
