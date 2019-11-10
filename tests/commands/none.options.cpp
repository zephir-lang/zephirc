// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <utility>

#include "argv.hpp"
#include "commands.hpp"
#include "zephir/main.hpp"

struct ArgsProvider {
  std::initializer_list<const char*> m_args;
  int m_expected;

  ArgsProvider(std::initializer_list<const char*> args, int expected)
      : m_args(args), m_expected(expected) {}
};

class NoneCmdTest : public testing::TestWithParam<ArgsProvider> {
 protected:
  NoneCmdTest() : argv(){};
  Argv argv;
};

ArgsProvider argsProvider[] = {
    {{"zephir", "--help"}, EXIT_HELP},
    {{"zephir", "--version"}, EXIT_SUCCESS},
    {{"zephir", "--vernum"}, EXIT_SUCCESS},
    {{"zephir", "--dumpversion"}, EXIT_SUCCESS},
};

TEST_P(NoneCmdTest, RunUsingGlobalOptions) {
  argv.assign(GetParam().m_args);
  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, GetParam().m_expected);
}

INSTANTIATE_TEST_SUITE_P(BulkTest, NoneCmdTest,
                         testing::ValuesIn(argsProvider));
