#!/bin/bash
set -e

echo "🚀 Fritzing Optimized Build Script"
echo "=================================="

# Get CPU count for parallel compilation
CPU_COUNT=$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)
echo "Using $CPU_COUNT parallel jobs"

# Set build directory
BUILD_DIR="../release64"
CURRENT_DIR=$(pwd)

# Clean previous build if requested
if [ "$1" = "--clean" ]; then
    echo "🧹 Cleaning previous build..."
    rm -rf "$BUILD_DIR"
    make clean 2>/dev/null || true
fi

# Check dependencies
echo "🔍 Checking dependencies..."
missing_deps=()

# Check Qt
if ! command -v qmake &> /dev/null; then
    missing_deps+=("Qt (qmake)")
fi

# Check Homebrew dependencies
for dep in libgit2 boost ngspice quazip clipper; do
    if ! brew list "$dep" &> /dev/null; then
        missing_deps+=("$dep")
    fi
done

if [ ${#missing_deps[@]} -ne 0 ]; then
    echo "❌ Missing dependencies:"
    printf '   - %s\n' "${missing_deps[@]}"
    echo ""
    echo "Install with: brew install ${missing_deps[*]}"
    exit 1
fi

echo "✅ All dependencies found"

# Configure build with optimizations
echo "⚙️  Configuring build with optimizations..."
qmake CONFIG+=release \
      QMAKE_CXXFLAGS+="-O3 -march=native -mtune=native -flto" \
      QMAKE_LFLAGS+="-flto" \
      phoenix.pro

# Build with parallel jobs
echo "🔨 Building with $CPU_COUNT parallel jobs..."
make -j"$CPU_COUNT"

# Check if build was successful
if [ -f "$BUILD_DIR/Fritzing.app/Contents/MacOS/Fritzing" ]; then
    echo "✅ Build successful!"
    echo "📱 Application: $BUILD_DIR/Fritzing.app"
    
    # Get build size
    APP_SIZE=$(du -sh "$BUILD_DIR/Fritzing.app" | cut -f1)
    echo "📊 Application size: $APP_SIZE"
    
    # Get build time
    echo "⏱️  Build completed at: $(date)"
    
else
    echo "❌ Build failed!"
    exit 1
fi
