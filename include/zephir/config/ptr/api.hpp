// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_PTR_API_HPP_
#define ZEPHIR_CONFIG_PTR_API_HPP_

#include <memory>

namespace zephir::config {
class Api;
using ApiPtr = std::shared_ptr<Api>;
}  // namespace zephir::config

#endif  // ZEPHIR_CONFIG_PTR_API_HPP_
