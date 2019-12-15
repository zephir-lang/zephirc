// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include <zephir/config/extra.hpp>

TEST(ExtraTest, EncodeClass) {
  auto extra = std::make_shared<zephir::config::Extra>("spaces", false);
  auto node = YAML::convert<zephir::config::ExtraPtr>::encode(extra);

  EXPECT_TRUE(node.IsMap());

  EXPECT_EQ("spaces", node["indent"].as<std::string>());
  EXPECT_FALSE(node["export-classes"].as<bool>());
}
