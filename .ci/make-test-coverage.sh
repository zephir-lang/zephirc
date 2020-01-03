#!/usr/bin/env bash

# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# -e  Exit immediately if a command exits with a non-zero status.
# -u  Treat unset variables as an error when substituting.
set -eu

[[ "${BASH_SOURCE[0]}" != "${0}" ]] && {
  >&2 echo "This script isn't designed to be sourced. Abort."
  exit 1
}

PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../" >/dev/null 2>&1 && pwd )"
pushd "$PROJECT_DIR"

[ -d build ] || mkdir build
cd build || exit 1

[ -f Makefile ] && {
  make clean
}

# Cleanup
rm -fr ./ccov
find . -type f \( -name '*.gcno' -o -name '*.gcda' \) -delete

[ -d ccov ] || mkdir ccov
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
ZEPHIR_TESTS_ROOT="$PROJECT_DIR/tests" make check

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
    '/usr/*' \
    '*/tests/*' \
    '*/.conan/*' \
  --no-checksum \
  --quiet \
  --output-file ./ccov/coverage.cleaned

# Ensure that this is being run not inside a CI container
if [ "${CI}" != "true" ]
then
  genhtml \
    --quiet \
    --output-directory ./ccov/html \
    ./ccov/coverage.cleaned

  printf "\n\tOpen file://%s/build/ccov/html/index.html" "$PROJECT_DIR"
  printf "\n\tin your browser to view the coverage report.\n\n"
fi

popd
