# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

set(versionRegex "#define[ \t]+ZEPHIR_VERSION_(MAJOR|MINOR|PATCH)")

file(STRINGS "${CMAKE_SOURCE_DIR}/include/zephir/version.hpp" zephirVersion
     REGEX ${versionRegex})

foreach(part ${zephirVersion})
  if(part MATCHES "${versionRegex}[ \t]+([^ ]+)$")
    set(ZEPHIR_VERSION_${CMAKE_MATCH_1}
        "${CMAKE_MATCH_2}"
        CACHE INTERNAL "")
  endif()
endforeach()

unset(versionRegex)
unset(zephirVersion)

set(ZEPHIR_VERSION
    ${ZEPHIR_VERSION_MAJOR}.${ZEPHIR_VERSION_MINOR}.${ZEPHIR_VERSION_PATCH})

mark_as_advanced(ZEPHIR_VERSION_MAJOR ZEPHIR_VERSION_MINOR ZEPHIR_VERSION_PATCH)

# Version.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
