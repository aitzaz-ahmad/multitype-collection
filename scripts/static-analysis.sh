#!/usr/bin/env bash
set -euo pipefail

RUN_CPPCHECK=true
RUN_CLANG_TIDY=true
BUILD_DIR="build"

usage() {
    cat <<EOF
Usage: $0 [options]

Options:
  --cppcheck        Run cppcheck only
  --clang-tidy      Run clang-tidy only
  --both            Run cppcheck and clang-tidy (default)
  --build-dir DIR   Build directory for clang-tidy compile_commands.json
  -h, --help        Show this help
EOF
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        --cppcheck)
            RUN_CPPCHECK=true
            RUN_CLANG_TIDY=false
            shift
            ;;
        --clang-tidy)
            RUN_CPPCHECK=false
            RUN_CLANG_TIDY=true
            shift
            ;;
        --both)
            RUN_CPPCHECK=true
            RUN_CLANG_TIDY=true
            shift
            ;;
        --build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            usage
            exit 1
            ;;
    esac
done

if [[ "$OSTYPE" == "darwin"* ]]; then
    export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
fi

if [[ "$RUN_CPPCHECK" == true ]]; then
    echo "========== cppcheck =========="

    cppcheck \
        --enable=all \
        --inline-suppr \
        --error-exitcode=1 \
        --suppress=missingIncludeSystem \
        --suppress=unusedFunction \
        --suppress=checkersReport \
        --quiet \
        --std=c++17 \
        -I include \
        src include
fi

if [[ "$RUN_CLANG_TIDY" == true ]]; then
    echo "========== clang-tidy =========="

    if [[ ! -f "$BUILD_DIR/compile_commands.json" ]]; then
        echo "Missing $BUILD_DIR/compile_commands.json"
        echo "Run: cmake -S . -B $BUILD_DIR -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
        exit 1
    fi

    clang_tidy_extra_args=()

    if [[ "$OSTYPE" == "darwin"* ]]; then
        export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

        SDKROOT="$(xcrun --show-sdk-path)"
        TOOLCHAIN_INCLUDE="$(xcode-select -p)/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1"

        clang_tidy_extra_args=(
            --extra-arg=-isysroot
            --extra-arg="$SDKROOT"
            --extra-arg=-isystem
            --extra-arg="$TOOLCHAIN_INCLUDE"
        )
    fi

    files=$(git ls-files '*.cpp')

    if [[ -z "$files" ]]; then
        echo "No C++ source files found."
        exit 0
    fi

    clang-tidy -p "$BUILD_DIR" "${clang_tidy_extra_args[@]}" $files
fi
