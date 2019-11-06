// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "argv.hpp"

#include <initializer_list>

Argv::Argv(std::initializer_list<const char *> args) {
  if (args.size() > 0) {
    m_argv.reserve(args.size() - 1);
  }

  for (const auto &iter : args) {
    m_argv.push_back(iter);
  }
}

std::vector<const char *> Argv::argv() const { return m_argv; }
