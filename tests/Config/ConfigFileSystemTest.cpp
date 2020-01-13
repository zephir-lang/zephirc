// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "Asserts.hpp"
#include "Config/Config.hpp"
#include "ConfigBaseTest.hpp"
#include "FileSystem/FileSystem.hpp"
#include "Properties.hpp"

TEST_F(ConfigBaseTest, LoadConfigFile) {
  argv.assign({});
  auto file = std::string(TESTS_ROOT) + "/fixtures/config/phalcon-4x.yml";
  auto config = zephir::Config::factory(&argv, file);

  auto actual = config->get<std::string>("namespace", "undefined");
  EXPECT_EQ("phalcon", actual);
}

TEST_F(ConfigBaseTest, BrokenConfigFile) {
  argv.assign({});
  auto file = std::string(TESTS_ROOT) + "/fixtures/config/bad-config.yml";
  EXPECT_THROW_EXCEPTION(std::runtime_error,
                         zephir::Config::factory(&argv, file),
                         "Config file is broken");
}

TEST_F(ConfigBaseTest, DumpConfigFile) {
  if (zephir::filesystem::exists("awesome.yml")) {
    remove("awesome.yml");
  }

  argv.assign({});

  auto config = zephir::Config::factory(&argv, "awesome.yml");
  config->set("name", "awesome");

  config->dump("awesome.yml");
  EXPECT_TRUE(zephir::filesystem::exists("awesome.yml"));

  config = zephir::Config::factory(&argv, "awesome.yml");
  auto name = config->get<std::string>("name", "");
  EXPECT_EQ("awesome", name);
}
