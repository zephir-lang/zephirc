// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <zephir/config.hpp>

#include "env/base.hpp"

using input_t = std::vector<std::string>;

TEST(ConfigTest, EncodeClass) {
  auto tests_root = TestEnvironment::tests_root();
  if (tests_root.empty()) {
    GTEST_SKIP();
  }

  auto file = tests_root + "/fixtures/legacy.yml";
  input_t argv({});

  auto config = zephir::Config::CreateFromArgv(argv, file);

  YAML::Node yaml;
  yaml = YAML::convert<zephir::ConfigPtr>::encode(config);

  EXPECT_TRUE(yaml.IsMap());

  EXPECT_EQ("", yaml["namespace"].as<std::string>());
  EXPECT_EQ("", yaml["name"].as<std::string>());
  EXPECT_EQ("", yaml["description"].as<std::string>());
  EXPECT_EQ("Zephir Team", yaml["author"].as<std::string>());
  EXPECT_EQ("0.0.1", yaml["version"].as<std::string>());
  EXPECT_EQ("ZendEngine3", yaml["backend"].as<std::string>());

  EXPECT_FALSE(yaml["verbose"].as<bool>());
  EXPECT_FALSE(yaml["silent"].as<bool>());
}
