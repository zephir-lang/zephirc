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
  auto warn = yaml["warnings"];

  EXPECT_TRUE(warn["unused-variable"].as<bool>());
  EXPECT_FALSE(warn["unused-variable-external"].as<bool>());
  EXPECT_TRUE(warn["possible-wrong-parameter"].as<bool>());
  EXPECT_FALSE(warn["possible-wrong-parameter-undefined"].as<bool>());
  EXPECT_TRUE(warn["nonexistent-function"].as<bool>());
  EXPECT_TRUE(warn["nonexistent-class"].as<bool>());
  EXPECT_TRUE(warn["non-valid-isset"].as<bool>());
  EXPECT_TRUE(warn["non-array-update"].as<bool>());
  EXPECT_TRUE(warn["non-valid-objectupdate"].as<bool>());
  EXPECT_TRUE(warn["non-valid-fetch"].as<bool>());
  EXPECT_TRUE(warn["invalid-array-index"].as<bool>());
  EXPECT_TRUE(warn["non-array-append"].as<bool>());
  EXPECT_TRUE(warn["invalid-return-type"].as<bool>());
  EXPECT_TRUE(warn["unreachable-code"].as<bool>());
  EXPECT_TRUE(warn["nonexistent-constant"].as<bool>());
  EXPECT_TRUE(warn["not-supported-magic-constant"].as<bool>());
  EXPECT_TRUE(warn["non-valid-decrement"].as<bool>());
  EXPECT_TRUE(warn["non-valid-increment"].as<bool>());
  EXPECT_TRUE(warn["non-valid-clone"].as<bool>());
  EXPECT_TRUE(warn["non-valid-new"].as<bool>());
  EXPECT_TRUE(warn["non-array-access"].as<bool>());
  EXPECT_TRUE(warn["invalid-reference"].as<bool>());
  EXPECT_TRUE(warn["invalid-typeof-comparison"].as<bool>());
  EXPECT_TRUE(warn["conditional-initialization"].as<bool>());

  EXPECT_TRUE(yaml["optimizations"].IsMap());
  auto opts = yaml["optimizations"];

  EXPECT_TRUE(opts["static-type-inference"].as<bool>());
  EXPECT_TRUE(opts["static-type-inference-second-pass"].as<bool>());
  EXPECT_TRUE(opts["local-context-pass"].as<bool>());
  EXPECT_TRUE(opts["constant-folding"].as<bool>());
  EXPECT_TRUE(opts["static-constant-class-folding"].as<bool>());
  EXPECT_TRUE(opts["call-gatherer-pass"].as<bool>());
  EXPECT_FALSE(opts["check-invalid-reads"].as<bool>());
  EXPECT_FALSE(opts["internal-call-transformation"].as<bool>());

  EXPECT_TRUE(yaml["extra"].IsMap());
  auto extra = yaml["extra"];

  EXPECT_EQ("spaces", extra["indent"].as<std::string>());
  EXPECT_FALSE(extra["export-classes"].as<bool>());
}
