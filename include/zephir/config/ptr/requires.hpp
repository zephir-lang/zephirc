// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_PTR_REQUIRES_HPP_
#define ZEPHIR_CONFIG_PTR_REQUIRES_HPP_

#include <memory>

namespace zephir::config {
class Requires;
using RequiresPtr = std::shared_ptr<Requires>;
}  // namespace zephir::config

#endif  // ZEPHIR_CONFIG_PTR_REQUIRES_HPP_
