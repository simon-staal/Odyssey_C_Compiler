#!/bin/bash

set -euo pipefail

# Usage: utility/test_dir.sh <dir_name> (optional)
# <dir_name> is the name of a directory in the compiler_tests directory(i.e. local_var)
# if unspecified will test all files in compiler_tests

if [[ $# -eq 0 ]] ; then
  TESTS=$(find compiler_tests -type f -not -name "*_driver.c")
else
  TESTS=$(find compiler_tests/${1} -type f -not -name "*_driver.c")
fi

# Formatting
TERMINAL_WIDTH=$(tput cols)
BUFFER=$(($TERMINAL_WIDTH / 2 - 9))
UNEVEN=$(($TERMINAL_WIDTH % 2))
if [[ $UNEVEN -eq 1 ]] ; then
  EXTRA="="
else
  EXTRA=""
fi

SEP=$(echo $(printf '=%.0s' $(eval "echo {1.."$(($BUFFER))"}")))

echo "${SEP}Compiling compiler${SEP}${EXTRA}"
make

PASSED=0
TOTAL=0
TEST_FAIL=""

for TEST in ${TESTS}; do
  set +e
  utility/run_test.sh ${TEST}
  RESULT=${?}
  set -e
  if [[ ${RESULT} -eq 0 ]] ; then
    PASSED=$((${PASSED}+1))
  else
    TEST_FAIL="${TEST_FAIL} ${TEST}"
  fi
  TOTAL=$((${TOTAL}+1))
done

echo $(printf '=%.0s' $(eval "echo {1.."$(($TERMINAL_WIDTH))"}"))
echo "Passed ${PASSED} out of ${TOTAL} tests"
echo "Failed: ${TEST_FAIL}"
