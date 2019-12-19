#!/usr/bin/env bash

# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# set sharness verbosity. we set the env var directly as
# it's too late to pass in --verbose, and --verbose is harder
# to pass through in some cases.
# shellcheck disable=SC2034
test "$TEST_VERBOSE" = 1 && verbose=t

PROJECTDIR=$(cd "$(dirname "$0")/../" || exit 1; pwd)
TESTSDIR="$PROJECTDIR/tests"
SHARNESS_TEST_SRCDIR="$TESTSDIR/sharness"
SHARNESS_LIB="$SHARNESS_TEST_SRCDIR/sharness.sh"
export PROJECTDIR TESTSDIR SHARNESS_TEST_SRCDIR SHARNESS_LIB

# shellcheck source=lib/sharness/sharness.sh
source "$SHARNESS_LIB" || {
  echo >&2 "Cannot source: $SHARNESS_LIB"
  echo >&2 "Please check Sharness installation."
  exit 1
}

if test "$TEST_VERBOSE" = 1; then
  (>&1 printf "# TEST_VERBOSE='%s'\n" "$TEST_VERBOSE")
fi

: "${ZEPHIR_BIN_DIR:=$PROJECTDIR/build/bin}"

ZEPHIR_BIN="$ZEPHIR_BIN_DIR/zephir"
FIXTURESDIR="$TESTSDIR/fixtures"
OUTPUTDIR="$TESTSDIR/output"
export FIXTURESDIR OUTPUTDIR ZEPHIR_BIN

function zephirc() {
  test "$TEST_VERBOSE" = 1 && (>&1 printf "# %s\\n" "$ZEPHIR_BIN $*")
  eval "$ZEPHIR_BIN $*"
}
