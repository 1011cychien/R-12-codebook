#!/bin/bash

mkdir -p `dirname /tmp/hash/pdf/"$@"`
cpp -dD -P -fpreprocessed "$@" | tr -d '[:space:]' | md5sum | cut -c-6 | tee /tmp/hash/pdf/"$@"
