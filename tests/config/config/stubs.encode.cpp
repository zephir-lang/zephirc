// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include "zephir/config/stubs.hpp"

TEST(StubsTest, EncodeClass) {
  zephir::config::StubsPtr stubs = std::make_shared<zephir::config::Stubs>(
      "ide/%version%/%namespace%", false, "");

  YAML::Node node;
  node["stubs"] = YAML::convert<zephir::config::StubsPtr>::encode(stubs);

  EXPECT_TRUE(node.IsMap());

  EXPECT_EQ("ide/%version%/%namespace%",
            node["stubs"]["path"].as<std::string>());
  EXPECT_FALSE(node["stubs"]["stubs-run-after-generate"].as<bool>());
  EXPECT_EQ("", node["stubs"]["banner"].as<std::string>());
}
