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

TEST(ApiThemeTest, DecodeString) {
  auto yaml = YAML::Load(R"(
{
  name: zephir,
  options: {
    github: "",
    analytics: "",
    main_color: "#3E6496",
    link_color: "#3E6496",
    link_hover_color: "#5F9AE7"
  }
})");

  ztheme::Options options({
      {"github", ""},
      {"analytics", ""},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  });

  zephir::config::api::Theme expected("zephir", options);
  auto actual = std::make_shared<zephir::config::api::Theme>();

  EXPECT_TRUE(
      YAML::convert<zephir::config::api::ThemePtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(ApiThemeTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::api::Theme>();

  EXPECT_FALSE(YAML::convert<zephir::config::api::ThemePtr>::decode(yaml["foo"],
                                                                    actual));
}
