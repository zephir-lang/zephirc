// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <tuple>
#include <utility>

#include <zephir/main.hpp>

#include "console/application.hpp"

class NoneCmdTest
    : public testing::TestWithParam<std::tuple<std::string, int>> {
 protected:
  NoneCmdTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_P(NoneCmdTest, RunUsingGlobalOptions) {
  auto expected = std::get<1>(GetParam());
  const auto& option = std::get<0>(GetParam());

  argv.assign({option});

  auto config = std::make_shared<zephir::Config>("foo");
  auto app =
      std::make_unique<zephir::console::Application>(config, argv, "tests");
  auto actual = app->Run();

  EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    BulkTest, NoneCmdTest,
    testing::Values(std::make_tuple("--help", EXIT_HELP),
                    std::make_tuple("--version", EXIT_SUCCESS),
                    std::make_tuple("--vernum", EXIT_SUCCESS),
                    std::make_tuple("--dumpversion", EXIT_SUCCESS)));
