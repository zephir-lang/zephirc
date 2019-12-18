// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <string>

#include "config/config/extra.hpp"

TEST(ExtraTest, EncodeClass) {
  auto extra = std::make_shared<zephir::config::Extra>("spaces", false);
  auto yaml = YAML::convert<zephir::config::ExtraPtr>::encode(extra);

  EXPECT_TRUE(yaml.IsMap());

  EXPECT_EQ("spaces", yaml["indent"].as<std::string>());
  EXPECT_FALSE(yaml["export-classes"].as<bool>());
}
