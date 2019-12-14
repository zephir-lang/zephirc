// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_VERSION_HPP_
#define ZEPHIR_VERSION_HPP_

#include "zephir/main.hpp"

#define ZEPHIR_VERSION_MAJOR 1
#define ZEPHIR_VERSION_MINOR 0
#define ZEPHIR_VERSION_PATCH 0

#define ZEPHIR_VERSION_STRING    \
  TOSTRING(ZEPHIR_VERSION_MAJOR) \
  "." TOSTRING(ZEPHIR_VERSION_MINOR) "." TOSTRING(ZEPHIR_VERSION_PATCH)

#define ZEPHIR_VERSION_ID                                                \
  (((ZEPHIR_VERSION_MAJOR)*10000000) + ((ZEPHIR_VERSION_MINOR)*100000) + \
   (ZEPHIR_VERSION_PATCH))

#endif  // ZEPHIR_VERSION_HPP_
