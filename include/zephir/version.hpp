// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file version.hpp
/// \brief Provides compiler version information.

#ifndef ZEPHIR_VERSION_HPP_
#define ZEPHIR_VERSION_HPP_

#include <zephir/main.hpp>

/// \brief Represents compiler major version.
#define ZEPHIR_VERSION_MAJOR 1

/// \brief Represents compiler minor version.
#define ZEPHIR_VERSION_MINOR 0

/// \brief Represents compiler patch version.
#define ZEPHIR_VERSION_PATCH 0

/// \brief Represents compiler version string.
#define ZEPHIR_VERSION_STRING    \
  TOSTRING(ZEPHIR_VERSION_MAJOR) \
  "." TOSTRING(ZEPHIR_VERSION_MINOR) "." TOSTRING(ZEPHIR_VERSION_PATCH)

/// \brief Represents compiler version ID.
#define ZEPHIR_VERSION_ID                                                \
  (((ZEPHIR_VERSION_MAJOR)*10000000) + ((ZEPHIR_VERSION_MINOR)*100000) + \
   (ZEPHIR_VERSION_PATCH))

/// \brief Represents human readable name of this project.
#define ZEPHIR_NAME "Zephir"

#endif  // ZEPHIR_VERSION_HPP_
