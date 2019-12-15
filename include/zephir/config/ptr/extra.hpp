// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_PTR_EXTRA_HPP_
#define ZEPHIR_CONFIG_PTR_EXTRA_HPP_

#include <memory>

namespace zephir::config {
class Extra;
using ExtraPtr = std::shared_ptr<Extra>;
}  // namespace zephir::config

#endif  // ZEPHIR_CONFIG_PTR_EXTRA_HPP_
