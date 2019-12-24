// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_PTR_HPP
#define ZEPHIR_CONFIG_PTR_HPP

#include <memory>

namespace zephir {
class Config;
using ConfigPtr = std::shared_ptr<Config>;
}  // namespace zephir

#endif  // ZEPHIR_SRC_CONFIG_PTR_HPP
