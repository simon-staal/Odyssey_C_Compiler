#!/bin/bash

set -euo pipefail

# Staging output directory
if [[ ! -d "out" ]] ; then
  mkdir out
fi

if [[ $# -eq 0 ]] ; then
  >&2 echo "Usage: utility/test_test.sh <test_path>"
  >&2 echo "<test_path> is the full path to a test"
  exit 1
fi

TEST=${1}
TEST_NAME=${TEST%.c}
TEST_NAME=${TEST_NAME##*/}
TEST_DRIVER=$(echo "${TEST}" | cut -f 1 -d '.')
TEST_DRIVER="${TEST_DRIVER}_driver.c"
OUT=$(echo "out/${TEST_NAME}" | cut -f 1 -d '.')

echo "==========Running test for ${TEST_NAME}=========="
echo "Compiling ${TEST_NAME}"
mips-linux-gnu-gcc -mfp32 -static -o "${OUT}.s" -S "${TEST}"

echo "==============================================="
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
  >&2 echo "Testcase ${1} is correct"
else
  >&2 echo "Testcase ${1} is incorrect"
  exit 1
fi
