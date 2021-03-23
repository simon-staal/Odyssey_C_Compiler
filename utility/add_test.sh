#!/bin/bash

set -euo pipefail

TEST_DIR="compiler_tests/"

if [[ $# -eq 0 ]] ; then
  >&2 echo "Usage: utlility/add_test.sh <filepath>"
  >&2 echo "<filepath> is the filepath from ${TEST_DIR} to the new test name, i.e. control_flow/for_empty_it"
  exit 1
fi

NAME="$1"

touch "${TEST_DIR}${NAME}.c"
touch "${TEST_DIR}${NAME}_driver.c"

git add "${TEST_DIR}${NAME}.c" "${TEST_DIR}${NAME}_driver.c"

>&2 echo "Created files"
