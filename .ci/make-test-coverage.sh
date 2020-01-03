#!/usr/bin/env bash

# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

[[ "${BASH_SOURCE[0]}" != "${0}" ]] && {
  >&2 echo "This script isn't designed to be sourced. Aborting."
  exit 1
}

# Trace ERR through pipes
set -o pipefail

# trace ERR through 'time command' and other functions
set -o errtrace

# set -e : exit the script if any statement returns a non-true return value
set -o errexit

# set -u : exit the script if you try to use an uninitialised variable
set -o nounset

# Prepare value for lcov's --gcov-tool option
test $# -lt 1 && GCOV_TOOL=gcov || GCOV_TOOL="$1"

if [[ "$(command -v "$GCOV_TOOL" 2>/dev/null || true)" = ""  && ! -f "$GCOV_TOOL" ]]
then
  >&2 printf "The gcov tool \"%s\" were not found. Aborting." "$GCOV_TOOL"
  exit 1
fi

PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../" >/dev/null 2>&1 && pwd )"
pushd "$PROJECT_DIR"

cd build || exit 1

[ -f Makefile ] && {
  make clean
}

# Cleanup
rm -fr ./ccov
find . -type f \( -name '*.gcno' -o -name '*.gcda' \) -delete

[ -d ccov ] || mkdir ccov
MAKEFLAGS="-j$(getconf _NPROCESSORS_ONLN)" make

# Debug
printf "       Using \"%s\" as a gcov tool...\n" "$GCOV_TOOL"

# Cleanup lcov
lcov \
  --gcov-tool "$GCOV_TOOL" \
  --directory . \
  --zerocounters

# Create baseline to make sure untouched files show up in the report
lcov \
  --gcov-tool "$GCOV_TOOL" \
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
  --gcov-tool "$GCOV_TOOL" \
  --capture \
  --directory . \
  --no-checksum \
  --quiet \
  --output-file ./ccov/coverage.info

lcov \
  --gcov-tool "$GCOV_TOOL" \
  --add-tracefile ./ccov/coverage.base \
  --add-tracefile ./ccov/coverage.info \
  --output-file ./ccov/coverage.total

lcov \
  --gcov-tool "$GCOV_TOOL" \
  --remove ./ccov/coverage.total \
    '/Applications/*' \
    '/usr/*' \
    '*/tests/*' \
    '*/.conan/*' \
  --no-checksum \
  --quiet \
  --output-file ./ccov/coverage.cleaned

# Ensure that this is being run not inside a CI container
[ -z "${GITHUB_ACTIONS}" ] && {
  genhtml \
    --quiet \
    --output-directory ./ccov/html \
    ./ccov/coverage.cleaned

  printf "       Open file://%s/build/ccov/html/index.html" "$PROJECT_DIR"
  printf "       in your browser to view the coverage report.\n\n"
}

popd
