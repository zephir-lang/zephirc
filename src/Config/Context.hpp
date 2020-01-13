// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file Context.hpp
/// \brief The Collection of all context details.

#ifndef ZEPHIR_CONTEXT_H
#define ZEPHIR_CONTEXT_H

#include <string>

namespace zephir {

/// \brief The Collection of all context details.
class Context {
 public:
  /// Absolute file path to zephir file.
  std::string _file;
  /// Line number in zephir source file.
  int _line;
  /// Context character position in zephir source file.
  int _cursor;

  /// \brief Construct Context object.
  ///
  /// \param file Absolute file path to zephir file.
  /// \param line Line number in zephir source file.
  /// \param cursor Context character position in zephir source file.
  explicit Context(const std::string &file, int line, int cursor);
};
}  // namespace zephir

#endif  // ZEPHIR_CONTEXT_H
