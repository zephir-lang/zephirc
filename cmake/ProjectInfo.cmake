# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

set(VERSION_RE "#define[ \t]+ZEPHIR_VERSION_(MAJOR|MINOR|PATCH|TWEAK|EXTRA)")

file(STRINGS "${zephir_SOURCE_DIR}/include/zephir/version.hpp" VERSION_PARTS
     REGEX ${VERSION_RE})

foreach(PART ${VERSION_PARTS})
  if(PART MATCHES "${VERSION_RE}[ \t]+([^ ]+)$")
    set(PROJECT_VERSION_${CMAKE_MATCH_1}
        "${CMAKE_MATCH_2}"
        CACHE INTERNAL "")
  endif()
endforeach()

set(PROJECT_VERSION_WITHOUT_TWEAK ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

if(PROJECT_VERSION_TWEAK)
  set(PROJECT_VERSION ${PROJECT_VERSION_WITHOUT_TWEAK}.${PROJECT_VERSION_TWEAK})
else()
  set(PROJECT_VERSION ${PROJECT_VERSION_WITHOUT_TWEAK})
endif()

set(BUILD_SUFFIX)
if(PROJECT_VERSION_EXTRA)
  set(BUILD_SUFFIX "-${PROJECT_VERSION_EXTRA}")
endif()

set(PROJECT_DISPLAY_NAME Zephir)

string(TIMESTAMP CURRENT_YEAR %Y)
set(ZEPHIR_TEAM "Phalcon Team")
set(ZEPHIR_COPYRIGHT "© 2013-${CURRENT_YEAR} ${ZEPHIR_TEAM}")

set(PROJECT_DESCRIPTION "Yet another implementation of the Zephir compiler")

unset(PART)
unset(VERSION_RE)
unset(VERSION_PARTS)
unset(CURRENT_YEAR)
unset(PROJECT_VERSION_WITHOUT_TWEAK)
