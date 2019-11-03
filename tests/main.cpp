// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.

#include <gtest/gtest.h>

// For more see:
// https://github.com/google/googletest/blob/master/googletest/docs/primer.md#writing-the-main-function
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
