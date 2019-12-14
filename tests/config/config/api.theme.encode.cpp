// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <zephir/config/api/theme.hpp>

namespace ztheme = zephir::config::api::theme;

TEST(ApiThemeTest, EncodeClass) {
  ztheme::Options options({
      {"github", ""},
      {"analytics", ""},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  });

  auto theme = std::make_shared<zephir::config::api::Theme>("zephir", options);

  YAML::Node node;
  node["theme"] = YAML::convert<zephir::config::api::ThemePtr>::encode(theme);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ("zephir", node["theme"]["name"].as<std::string>());

  EXPECT_TRUE(node["theme"].IsMap());
  EXPECT_TRUE(node["theme"]["options"].IsMap());

  EXPECT_EQ("", node["theme"]["options"]["github"].as<std::string>());
  EXPECT_EQ("", node["theme"]["options"]["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496",
            node["theme"]["options"]["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496",
            node["theme"]["options"]["link_color"].as<std::string>());
  EXPECT_EQ("#5F9AE7",
            node["theme"]["options"]["link_hover_color"].as<std::string>());
}
