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

PASSED=0
TOTAL=0

for TEST in ${TESTS}; do
  set +e
  utility/run_test.sh ${TEST}
  RESULT=${?}
  set -e
  if [[ ${RESULT} -eq 0 ]] ; then
    PASSED=$((${PASSED}+1))
  fi
  TOTAL=$((${TOTAL}+1))
done

echo "========================================="
echo "Passed ${PASSED} out of ${TOTAL} tests"
