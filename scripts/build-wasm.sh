#!/bin/bash
set -euo pipefail

# Resolve project root regardless of where the script is invoked from
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

# -----------------------------------------------------------------------------
# 1. Activate Emscripten
# -----------------------------------------------------------------------------
# Adjust this path if your emsdk lives somewhere else.
EMSDK_DIR="$ROOT_DIR/emsdk"
if [[ ! -f "$EMSDK_DIR/emsdk_env.sh" ]]; then
    echo "Error: emsdk not found at $EMSDK_DIR" >&2
    echo "Set EMSDK_DIR in this script to the correct location." >&2
    exit 1
fi
# shellcheck disable=SC1091
source "$EMSDK_DIR/emsdk_env.sh"

# -----------------------------------------------------------------------------
# 2. Make sure a WASM-capable raylib is available
# -----------------------------------------------------------------------------
RAYLIB_DIR="$ROOT_DIR/vendor/raylib"
RAYLIB_REPO="https://github.com/raysan5/raylib.git"
RAYLIB_REF="5.5"   # pin to a known-good version; bump if you need newer features

build_raylib_wasm() {
    echo ">>> Building raylib for WebAssembly..."
    pushd "$RAYLIB_DIR/src" >/dev/null

    # Clean any previous build artefacts
    make clean >/dev/null 2>&1 || true

    # raylib ships a dedicated HTML5 target via Emscripten
    make PLATFORM=PLATFORM_WEB -j"$(sysctl -n hw.ncpu 2>/dev/null || nproc)"

    popd >/dev/null
}

if [[ ! -f "$RAYLIB_DIR/src/libraylib.a" ]]; then
    if [[ ! -d "$RAYLIB_DIR" ]]; then
        echo ">>> Cloning raylib ($RAYLIB_REF) into vendor/raylib..."
        mkdir -p "$(dirname "$RAYLIB_DIR")"
        git clone --depth 1 --branch "$RAYLIB_REF" "$RAYLIB_REPO" "$RAYLIB_DIR"
    fi
    build_raylib_wasm
fi

# -----------------------------------------------------------------------------
# 3. Collect sources and build
# -----------------------------------------------------------------------------
OUT_DIR="$ROOT_DIR/out"
mkdir -p "$OUT_DIR"

# All .cpp files under src/ plus the top-level main.cpp
SRC_FILES=$(find "$ROOT_DIR/src" -maxdepth 1 -name '*.cpp' | sort)
if [[ -z "$SRC_FILES" ]]; then
    echo "Error: no .cpp sources found under $ROOT_DIR/src" >&2
    exit 1
fi

echo ">>> Compiling to WebAssembly..."

# Warn if macOS Finder metadata files would sneak into the preloaded bundle
if find "$ROOT_DIR/resources" \( -name '.DS_Store' -o -name '._*' \) -print -quit | grep -q .; then
    echo "Warning: macOS metadata files (.DS_Store / ._*) found in resources/." >&2
    echo "         These will be included in the preloaded bundle and may shadow real assets." >&2
    echo "         Run:  find resources \\( -name '.DS_Store' -o -name '._*' \\) -delete" >&2
fi

emcc -o "$OUT_DIR/index.html" \
    "$ROOT_DIR/main.cpp" $SRC_FILES \
    -Os -Wall \
    -I"$ROOT_DIR/src" \
    -I"$RAYLIB_DIR/src" \
    -L"$RAYLIB_DIR/src" \
    "$RAYLIB_DIR/src/libraylib.a" \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    -s "EXPORTED_RUNTIME_METHODS=['HEAPF32','HEAPU8','HEAPU32','HEAP8','HEAP32','requestFullscreen']" \
    --shell-file "$ROOT_DIR/scripts/shell.html" \
    --preload-file "$ROOT_DIR/resources@/resources" \
    -s TOTAL_STACK=64MB \
    -s INITIAL_MEMORY=128MB \
    -s ASSERTIONS \
    -DPLATFORM_WEB

echo ">>> Build complete: $OUT_DIR/index.html"

# -----------------------------------------------------------------------------
# 4. Optionally serve the game with emrun
# -----------------------------------------------------------------------------
if [[ "${1:-}" == "--serve" || "${1:-}" == "-s" ]]; then
    echo ">>> Starting emrun (Ctrl-C to stop)..."
    cd "$OUT_DIR"
    emrun --no_browser --port 8080 index.html
else
    echo "Run with --serve to launch emrun, or open $OUT_DIR/index.html in a browser."
fi
