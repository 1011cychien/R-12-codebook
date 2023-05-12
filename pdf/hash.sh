#!/bin/bash

cpp -dD -P -fpreprocessed "$@" | tr -d '[:space:]' | md5sum | cut -c-6 | tee hash.tmp.txt
