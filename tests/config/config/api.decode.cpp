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

TEST(ApiTest, DecodeString) {
  auto yaml = YAML::Load(R"(
{
  path: doc/%version%,
  theme: {
    name: zephir,
    options: {
      github: https://github.com/acme,
      analytics: '',
      main_color: '#3E6496',
      link_color: '#3E6496',
      link_hover_color: '#5F9AE7'
    }
  }
})");

  ztheme::Options options({
      {"github", "https://github.com/acme"},
      {"analytics", ""},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  });
  zephir::config::api::Theme theme("zephir", options);
  zephir::config::Api expected("doc/%version%", theme);

  auto actual = std::make_shared<zephir::config::Api>();

  EXPECT_TRUE(YAML::convert<zephir::config::ApiPtr>::decode(yaml, actual));
  EXPECT_EQ(*actual, expected);
}

TEST(ApiTest, DecodeInvalid) {
  auto yaml = YAML::Load("foo: bar");
  auto actual = std::make_shared<zephir::config::Api>();

  EXPECT_FALSE(
      YAML::convert<zephir::config::ApiPtr>::decode(yaml["foo"], actual));
}
