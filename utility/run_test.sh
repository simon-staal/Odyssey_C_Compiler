#!/bin/bash

set -euo pipefail

# Staging output directory
if [[ ! -d "out" ]] ; then
  mkdir out
fi

if [[ $# -eq 0 ]] ; then
  >&2 echo "Usage: utility/run_test.sh <test_path> -V (optional)"
  >&2 echo "<test_path> is the full path to a test"
  >&2 echo "-V enables visualalisation"
  exit 1
fi

TEST=${1}
TEST_NAME=${TEST%.c}
TEST_NAME=${TEST_NAME##*/}
TEST_DRIVER=$(echo "${TEST}" | cut -f 1 -d '.')
TEST_DRIVER="${TEST_DRIVER}_driver.c"
OUT=$(echo "out/${TEST_NAME}" | cut -f 1 -d '.')

# Formatting
TERMINAL_WIDTH=$(tput cols)
TITLE="Running test for ${TEST_NAME}"
LEN=`expr length "$TITLE"`
DIFF=$(($TERMINAL_WIDTH - $LEN))
BUFFER=$(($DIFF / 2))
UNEVEN=$(($DIFF % 2))
if [[ $UNEVEN -eq 1 ]] ; then
  EXTRA="="
else
  EXTRA=""
fi
SEP=$(echo $(printf '=%.0s' $(eval "echo {1.."$(($BUFFER))"}")))

echo "${SEP}${TITLE}${SEP}${EXTRA}"
echo "Compiling ${TEST_NAME}"
if [[ $# -eq 2 ]] ; then
  bin/c_compiler -S "${TEST}" -o "${OUT}.s" -V
else
  bin/c_compiler -S "${TEST}" -o "${OUT}.s"
fi

echo $(printf '=%.0s' $(eval "echo {1.."$(($TERMINAL_WIDTH))"}"))
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
  exit 1
fi
