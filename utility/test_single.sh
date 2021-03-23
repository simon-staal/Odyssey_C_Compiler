#!/bin/bash

set -euo pipefail

if [[ $# -eq 0 ]] ; then
  >&2 echo "Usage: utility/single_test.sh <test_name>"
  >&2 echo "<test_name> is the name of a test in the compiler_tests directory without filepath (i.e. return_constant.c)"
  exit 1
fi

# Recursively finds test file
shopt -s globstar
TEST=$(echo compiler_tests/**/"${1}")

# Run single test
utility/run_test.sh ${TEST}
