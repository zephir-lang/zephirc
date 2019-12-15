// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include <zephir/config/stubs.hpp>

TEST(StubsTest, EncodeClass) {
  auto stubs = std::make_shared<zephir::config::Stubs>(
      "ide/%version%/%namespace%", false, "/* header */");

  auto yaml = YAML::convert<zephir::config::StubsPtr>::encode(stubs);

  EXPECT_TRUE(yaml.IsMap());

  EXPECT_EQ("ide/%version%/%namespace%", yaml["path"].as<std::string>());
  EXPECT_FALSE(yaml["stubs-run-after-generate"].as<bool>());
  EXPECT_EQ("/* header */", yaml["banner"].as<std::string>());
}
