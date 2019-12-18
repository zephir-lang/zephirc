// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "config/config/api/theme.hpp"

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
  auto yaml = YAML::convert<zephir::config::api::ThemePtr>::encode(theme);

  EXPECT_TRUE(yaml.IsMap());
  EXPECT_EQ("zephir", yaml["name"].as<std::string>());

  EXPECT_TRUE(yaml["options"].IsMap());

  EXPECT_EQ("", yaml["options"]["github"].as<std::string>());
  EXPECT_EQ("", yaml["options"]["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496", yaml["options"]["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496", yaml["options"]["link_color"].as<std::string>());
  EXPECT_EQ("#5F9AE7", yaml["options"]["link_hover_color"].as<std::string>());
}
