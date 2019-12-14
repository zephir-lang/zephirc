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
  zephir::config::Api expected("doc/%version%", theme);

  auto api = std::make_shared<zephir::config::Api>("doc/%version%", theme);

  YAML::Node node;
  node["api"] = YAML::convert<zephir::config::ApiPtr>::encode(api);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ("doc/%version%", node["api"]["path"].as<std::string>());
  EXPECT_EQ("zephir", node["api"]["theme"]["name"].as<std::string>());

  EXPECT_TRUE(node["api"]["theme"].IsMap());
  EXPECT_TRUE(node["api"]["theme"]["options"].IsMap());

  EXPECT_EQ("", node["api"]["theme"]["options"]["github"].as<std::string>());
  EXPECT_EQ("", node["api"]["theme"]["options"]["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496",
            node["api"]["theme"]["options"]["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496",
            node["api"]["theme"]["options"]["link_color"].as<std::string>());
  EXPECT_EQ(
      "#5F9AE7",
      node["api"]["theme"]["options"]["link_hover_color"].as<std::string>());
}
