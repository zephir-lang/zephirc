#!/usr/bin/env bash

# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

set -eu

cd build || exit 1

[ -f Makefile ] && {
  make clean
}

# Cleanup
rm -fr ./ccov
find . -type f \( -name '*.gcno' -o -name '*.gcda' \) -delete

mkdir -p ./ccov
MAKEFLAGS="-j$(getconf _NPROCESSORS_ONLN)" make

# Cleanup lcov
lcov \
  --gcov-tool gcov \
  --directory . \
  --zerocounters

# Create baseline to make sure untouched files show up in the report
lcov \
  --gcov-tool gcov \
  --capture \
  --directory . \
  --initial \
  --no-checksum \
  --quiet \
  --output-file ./ccov/coverage.base

# Run tests
make check

# Debug
find . -type f \( -name '*.gcno' -o -name '*.gcda' \) -print

# Capturing lcov counters and generating report
lcov \
  --gcov-tool gcov \
  --capture \
  --directory . \
  --no-checksum \
  --quiet \
  --output-file ./ccov/coverage.info

lcov \
  --gcov-tool gcov \
  --add-tracefile ./ccov/coverage.base \
  --add-tracefile ./ccov/coverage.info \
  --output-file ./ccov/coverage.total

lcov \
  --gcov-tool gcov \
  --remove ./ccov/coverage.total \
    '/Applications/*' \
    '/usr/*'          \
    '*/tests/*'       \
    '*/.conan/*'      \
  --no-checksum \
  --quiet \
  --output-file ./ccov/coverage.cleaned

genhtml \
  --quiet \
  --output-directory ./ccov/html \
  ./ccov/coverage.cleaned
