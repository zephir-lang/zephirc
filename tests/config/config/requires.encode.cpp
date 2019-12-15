// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include <zephir/config/requires.hpp>

TEST(RequiresTest, EncodeClass) {
  std::vector<std::string> expected = {"PDO", "SPL", "standard", "hash"};
  auto requires = std::make_shared<zephir::config::Requires>(expected);
  auto yaml = YAML::convert<zephir::config::RequiresPtr>::encode(requires);

  EXPECT_TRUE(yaml.IsMap());
  EXPECT_EQ(expected, yaml["extensions"].as<std::vector<std::string>>());
}
