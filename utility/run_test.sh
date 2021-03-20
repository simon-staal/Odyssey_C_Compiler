#!/bin/bash

set -euo pipefail

# Staging output directory
if [[ ! -d "out" ]] ; then
  mkdir out
fi

if [[ $# -eq 0 ]] ; then
  >&2 echo "Usage: utility/run_test.sh <test_name>"
  >&2 echo "<test_name> is the name of a test in the compiler_tests directory without filepath (i.e. return_constant.c)"
  exit 1
fi

echo "==========Compiling compiler=========="
make

# Recursively finds test file
shopt -s globstar
TEST=$(echo compiler_tests/**/"${1}")
TEST_DRIVER=$(echo "${TEST}" | cut -f 1 -d '.')
TEST_DRIVER="${TEST_DRIVER}_driver.c"
OUT=$(echo "out/${1}" | cut -f 1 -d '.')

echo "==========Running test for ${1}=========="
echo "Compiling ${1}"
bin/c_compiler -S "${TEST}" -o "${OUT}.s"

echo "========================================="
echo "Assembling output"
mips-linux-gnu-gcc -mfp32 -static -o "${OUT}.o" -c "${OUT}.s"

echo "Linking with driver program"
mips-linux-gnu-gcc -mfp32 -static -o "${OUT}" "${OUT}.o" "${TEST_DRIVER}"

echo "Simulating"
set +e
qemu-mips "${OUT}"
RESULT=${?}
set -e

if [[ ${RESULT} -eq 0 ]] ; then
  >&2 echo "Testcase ${1} passed successfully"
else
  >&2 echo "Testcase ${1} failed"
fi
