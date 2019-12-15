// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <zephir/config/api.hpp>

namespace ztheme = zephir::config::api::theme;

TEST(ApiTest, EncodeClass) {
  ztheme::Options options({
      {"github", ""},
      {"analytics", ""},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  });

  zephir::config::api::Theme theme("zephir", options);

  auto api = std::make_shared<zephir::config::Api>("doc/%version%", theme);
  auto yaml = YAML::convert<zephir::config::ApiPtr>::encode(api);

  EXPECT_TRUE(yaml.IsMap());
  EXPECT_EQ("doc/%version%", yaml["path"].as<std::string>());
  EXPECT_EQ("zephir", yaml["theme"]["name"].as<std::string>());

  EXPECT_TRUE(yaml["theme"].IsMap());
  EXPECT_TRUE(yaml["theme"]["options"].IsMap());
  auto opts = yaml["theme"]["options"];

  EXPECT_EQ("", opts["github"].as<std::string>());
  EXPECT_EQ("", opts["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496", opts["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496", opts["link_color"].as<std::string>());
  EXPECT_EQ("#5F9AE7", opts["link_hover_color"].as<std::string>());
}
