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
  auto yaml = YAML::convert<zephir::ConfigPtr>::encode(config);

  EXPECT_TRUE(yaml.IsMap());

  EXPECT_EQ("", yaml["namespace"].as<std::string>());
  EXPECT_EQ("", yaml["name"].as<std::string>());
  EXPECT_EQ("", yaml["description"].as<std::string>());
  EXPECT_EQ("Zephir Team", yaml["author"].as<std::string>());
  EXPECT_EQ("0.0.1", yaml["version"].as<std::string>());
  EXPECT_EQ("ZendEngine3", yaml["backend"].as<std::string>());

  EXPECT_FALSE(yaml["verbose"].as<bool>());
  EXPECT_FALSE(yaml["silent"].as<bool>());

  EXPECT_TRUE(yaml["requires"].IsMap());
  EXPECT_TRUE(yaml["requires"]["extensions"].IsSequence());
  EXPECT_EQ(0, yaml["requires"]["extensions"].size());

  EXPECT_TRUE(yaml["stubs"].IsMap());
  auto stubs = yaml["stubs"];
  EXPECT_EQ("ide/%version%/%namespace%", stubs["path"].as<std::string>());
  EXPECT_FALSE(stubs["stubs-run-after-generate"].as<bool>());
  EXPECT_EQ("", stubs["banner"].as<std::string>());

  EXPECT_TRUE(yaml["api"].IsMap());
  EXPECT_EQ("doc/%version%", yaml["api"]["path"].as<std::string>());
  EXPECT_EQ("zephir", yaml["api"]["theme"]["name"].as<std::string>());

  EXPECT_TRUE(yaml["api"]["theme"].IsMap());
  EXPECT_TRUE(yaml["api"]["theme"]["options"].IsMap());

  auto options = yaml["api"]["theme"]["options"];
  EXPECT_EQ("", options["github"].as<std::string>());
  EXPECT_EQ("", options["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496", options["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496", options["link_color"].as<std::string>());
  EXPECT_EQ("#5F9AE7", options["link_hover_color"].as<std::string>());

  EXPECT_TRUE(yaml["warnings"].IsMap());
  EXPECT_TRUE(yaml["optimizations"].IsMap());
  EXPECT_TRUE(yaml["extra"].IsMap());
}
