// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_IMPL_HPP_
#define ZEPHIR_CONFIG_IMPL_HPP_

#include <string>

namespace zephir {
template <typename T>
inline T Config::get(const std::string &key, const T &fallback) const {
  return container_[key].as<T, T>(fallback);
}

template <typename T>
inline T zephir::Config::get(const std::string &key, const std::string &ns,
                             const T &fallback) const {
  return container_[ns][key].as<T, T>(fallback);
}
}  // namespace zephir
#endif  // ZEPHIR_CONFIG_IMPL_HPP_
