# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

set(_re "#define[ \t]+ZEPHIR_VERSION_(MAJOR|MINOR|PATCH)")

file(STRINGS "${zephir_SOURCE_DIR}/include/zephir/version.hpp" _parts
     REGEX ${_re})

foreach(_part ${_parts})
  if(_part MATCHES "${_re}[ \t]+([^ ]+)$")
    set(ZEPHIR_VERSION_${CMAKE_MATCH_1}
        "${CMAKE_MATCH_2}"
        CACHE INTERNAL "")
  endif()
endforeach()

set(PROJECT_VERSION
    "${ZEPHIR_VERSION_MAJOR}.${ZEPHIR_VERSION_MINOR}.${ZEPHIR_VERSION_PATCH}")
set(PROJECT_VERSION_MAJOR ${ZEPHIR_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${ZEPHIR_VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${ZEPHIR_VERSION_PATCH})
set(PROJECT_VERSION_TWEAK 0) # Not used for now

set(BUILD_SUFFIX)

set(ZEPHIR_DISPLAY_NAME Zephir)

string(TIMESTAMP CURRENT_YEAR %Y)
set(ZEPHIR_TEAM "Phalcon Team")
set(ZEPHIR_COPYRIGHT "© 2013-${CURRENT_YEAR} ${ZEPHIR_TEAM}")

set(PROJECT_DESCRIPTION "Yet another implementation of the Zephir compiler")
