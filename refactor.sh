#!/bin/bash

set -euo pipefail

#cp -r include/ src/include_impl/

find src/include_impl/ -type d | while read d ; do
  echo "${d}"
  for file in ${d}/*.hpp ; do
    mv "$file" "${file%.hpp}.cpp"
  done
done
