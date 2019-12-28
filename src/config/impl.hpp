// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_IMPL_HPP_
#define ZEPHIR_CONFIG_IMPL_HPP_

#include <string>

namespace zephir {
/// \brief Gets a value by its key
template <typename T>
inline T Config::get(const std::string &key, const T &fallback) const {
  return container_[key].as<T, T>(fallback);
}

/// \brief Gets a value by its key and namespace
template <typename T>
inline T zephir::Config::get(const std::string &key, const std::string &ns,
                             const T &fallback) const {
  if (container_[ns].IsDefined()) {
    return container_[ns][key].as<T, T>(fallback);
  }

  return fallback;
}

/// \brief Sets a value for a provided key
template <typename T>
inline zephir::Config &zephir::Config::set(const std::string &key,
                                           const T &rhs) {
  if (!key.empty()) {
    container_[key] = rhs;
  }

  return *this;
}

/// \brief Sets a value for a provided key for the the given namespace
template <typename T>
inline zephir::Config &zephir::Config::set(const std::string &key,
                                           const std::string &ns,
                                           const T &rhs) {
  if (!ns.empty() && !key.empty()) {
    container_[ns][key] = rhs;
  }

  return *this;
}
}  // namespace zephir
#endif  // ZEPHIR_CONFIG_IMPL_HPP_
