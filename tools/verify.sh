#!/usr/bin/env bash
set -euo pipefail

projectRoot="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
buildDir="${1:-$projectRoot/build}"
configuration="${2:-Debug}"
mkdir -p -- "$buildDir"
buildDir="$(cd -- "$buildDir" && pwd)"
logDir="$buildDir/verify-logs"
mkdir -p -- "$logDir"

runStep() {
    local stepName="$1"
    shift
    local logFile="$logDir/$stepName.log"
    local result=0
    "$@" >"$logFile" 2>&1 || result=$?
    if ((result != 0)) || grep -Eiq '(^|[^[:alpha:]])warning([[:space:]:]|$)' "$logFile"; then
        printf 'FAIL: %s (exit %s)\n' "$stepName" "$result"
        if grep -Eiq 'warning|error|failed|not run|no tests' "$logFile"; then
            grep -Ei 'warning|error|failed|not run|no tests' "$logFile" | tail -n 20 || true
        else
            tail -n 20 "$logFile"
        fi
        printf 'LOG: %s\n' "$logFile"
        exit 1
    fi
    printf 'PASS: %s\n' "$stepName"
}

# Không tải dependency ngầm trong bước xác minh.
runStep configure cmake -S "$projectRoot" -B "$buildDir" \
    -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE="$configuration" \
    -DFETCHCONTENT_FULLY_DISCONNECTED=ON
# Build lại mã dự án để warning không bị bỏ qua do cache object cũ.
runStep build cmake --build "$buildDir" --config "$configuration" --clean-first --parallel
runStep ctest ctest --test-dir "$buildDir" -C "$configuration" \
    --output-on-failure --no-tests=error
printf 'PASS: verify (build, 0 warnings, ctest)\n'
