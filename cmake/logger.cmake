# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

cmake_minimum_required(VERSION 3.1...3.16)

project(spdlog
    LANGUAGES   CXX
    DESCRIPTION "C++ logging library"
    )

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

# logger.cmake ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
