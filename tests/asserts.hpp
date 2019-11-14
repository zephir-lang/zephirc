// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_TESTS_ASSERTS_HPP_
#define ZEPHIR_TESTS_ASSERTS_HPP_

#define EXPECT_THROW_EXCEPTION(exception_type, statement, message) \
  ASSERT_THROW(statement, exception_type);                         \
  try {                                                            \
    statement;                                                     \
  } catch (const exception_type& e) {                              \
    EXPECT_STREQ(e.what(), message);                               \
  }

#endif  // ZEPHIR_TESTS_ASSERTS_HPP_
