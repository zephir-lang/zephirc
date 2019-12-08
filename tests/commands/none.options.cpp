// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "commands.hpp"
#include "zephir/main.hpp"

using input_t = std::vector<std::string>;

class NoneCmdTest
    : public testing::TestWithParam<std::tuple<std::string, int>> {
 protected:
  NoneCmdTest() : argv(){};
  input_t argv;
};

TEST_P(NoneCmdTest, RunUsingGlobalOptions) {
  int expected = std::get<1>(GetParam());
  const std::string& option = std::get<0>(GetParam());

  argv.assign({option});
  auto actual = zephir::commands::CreateFromArgv(argv);
  EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    BulkTest, NoneCmdTest,
    testing::Values(std::make_tuple("--help", EXIT_HELP),
                    std::make_tuple("--version", EXIT_SUCCESS),
                    std::make_tuple("--vernum", EXIT_SUCCESS),
                    std::make_tuple("--dumpversion", EXIT_SUCCESS)));
