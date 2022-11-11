#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi
}

FILES="lib/*.cpp lib/*.h"

print_header "RUN cppcheck"
check_log "cppcheck ${FILES} --language=c++ --enable=all --inconclusive --error-exitcode=1 -I lib --suppress=missingIncludeSystem --suppress=unusedFunction" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ${FILES} -extra-arg-before=-xc++ -- -I lib" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint ${FILES}" "Can't open for reading"

print_header "SUCCESS"