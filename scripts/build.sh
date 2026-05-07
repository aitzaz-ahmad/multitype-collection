#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE="Debug"
BUILD_TESTING="ON"
BUILD_DIR="build"

while [[ $# -gt 0 ]]; do
    case "$1" in
        --release)
            BUILD_TYPE="Release"
            shift
            ;;
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --no-tests)
            BUILD_TESTING="OFF"
            shift
            ;;
        --build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

cmake -S . -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DBUILD_TESTING="$BUILD_TESTING"

cmake --build "$BUILD_DIR"
