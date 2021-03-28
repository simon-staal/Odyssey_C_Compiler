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

# Run single test
utility/run_test.sh ${TEST} -V
