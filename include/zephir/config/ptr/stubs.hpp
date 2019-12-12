// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_PTR_STUBS_HPP_
#define ZEPHIR_CONFIG_PTR_STUBS_HPP_

#include <memory>

namespace zephir {
namespace config {
class Stubs;
using StubsPtr = std::shared_ptr<Stubs>;
}  // namespace config
}  // namespace zephir

#endif  // ZEPHIR_CONFIG_PTR_STUBS_HPP_
