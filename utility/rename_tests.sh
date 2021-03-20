#!/bin/bash

set -euo pipefail

for FILE in $(find compiler_tests/float -type f -name "*.c") ; do
  F_NAME=$(basename "${FILE}")
  F_PATH=$(dirname "${FILE}")
  echo "${F_PATH}/float_${F_NAME}"
  # mv "${FILE}" "${F_PATH}/float_${F_NAME}"
done
