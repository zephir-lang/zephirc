// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_PTR_HPP
#define ZEPHIR_CONFIG_PTR_HPP

/// \file Ptr.hpp
/// \brief Represents type definition for a shared pointer to a Config instance.

#include <memory>

namespace zephir {
class Config;

/// \brief A type definition for a shared pointer to a Config instance.
using ConfigPtr = std::shared_ptr<Config>;
}  // namespace zephir

#endif  // ZEPHIR_SRC_CONFIG_PTR_HPP
