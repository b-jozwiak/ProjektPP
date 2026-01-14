#!/bin/bash

MEMCHECK=false
ARGS=()

for arg in "$@"; do
    if [ "$arg" = "--memcheck" ]; then
        MEMCHECK=true
    else
        ARGS+=("$arg")
    fi
done

if [ "$MEMCHECK" = true ]; then
    echo "Building with AddressSanitizer..."
    make memcheck
    ./out/rejestr_memcheck "${ARGS[@]}"
else
    echo "Building normally..."
    make
    ./out/rejestr "${ARGS[@]}"
fi
