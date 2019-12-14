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

TEST(ApiOptionsTest, DecodeString) {
  auto node = YAML::Load(R"(
options: {
  github: "",
  analytics: "",
  main_color: "#3E6496",
  link_color: "#3E6496",
  link_hover_color: "#5F9AE7"
})");

  ztheme::Options expected({
      {"github", ""},
      {"analytics", ""},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  });

  auto actual = std::make_shared<ztheme::Options>();

  EXPECT_TRUE(
      YAML::convert<ztheme::OptionsPtr>::decode(node["options"], actual));
  EXPECT_EQ(*actual, expected);
}

TEST(ApiOptionsTest, DecodeInvalid) {
  auto node = YAML::Load("foo: bar");
  auto actual = std::make_shared<ztheme::Options>();

  EXPECT_FALSE(YAML::convert<ztheme::OptionsPtr>::decode(node["foo"], actual));
}
