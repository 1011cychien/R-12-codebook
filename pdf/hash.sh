#!/bin/bash

mkdir -p `dirname /tmp/hash/pdf/"$@".md5`
cpp -dD -P -fpreprocessed "$@" | tr -d '[:space:]' | md5sum | cut -c-6 | tee /tmp/hash/pdf/"$@".md5
