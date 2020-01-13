// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "Context.hpp"

zephir::Context::Context(const std::string& file, int line, int cursor)
    : _file(file), _line(line), _cursor(cursor) {}
