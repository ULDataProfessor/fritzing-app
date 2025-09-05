#!/bin/bash
set -e

echo "📦 Fritzing Dependency Installer for macOS"
echo "=========================================="

# Check if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "❌ Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    
    # Add Homebrew to PATH for Apple Silicon Macs
    if [[ $(uname -m) == "arm64" ]]; then
        echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
        eval "$(/opt/homebrew/bin/brew shellenv)"
    fi
fi

echo "✅ Homebrew found"

# Update Homebrew
echo "🔄 Updating Homebrew..."
brew update

# Install Qt (latest compatible version)
echo "📱 Installing Qt..."
if ! brew list qt@6 &> /dev/null; then
    brew install qt@6
    echo 'export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"' >> ~/.zprofile
    export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"
fi

# Install build dependencies
echo "🔧 Installing build dependencies..."
dependencies=(
    "cmake"
    "pkg-config"
    "libgit2"
    "boost"
    "ngspice"
    "quazip"
    "clipper"
)

for dep in "${dependencies[@]}"; do
    if ! brew list "$dep" &> /dev/null; then
        echo "Installing $dep..."
        brew install "$dep"
    else
        echo "✅ $dep already installed"
    fi
done

# Install optional dependencies for better performance
echo "⚡ Installing optional performance dependencies..."
optional_deps=(
    "ccache"  # Compiler cache for faster rebuilds
    "ninja"   # Faster build system
)

for dep in "${optional_deps[@]}"; do
    if ! brew list "$dep" &> /dev/null; then
        echo "Installing $dep..."
        brew install "$dep"
    else
        echo "✅ $dep already installed"
    fi
done

echo ""
echo "🎉 All dependencies installed successfully!"
echo ""
echo "Next steps:"
echo "1. Run: ./build_optimized.sh"
echo "2. Or run: ./build_optimized.sh --clean (for clean build)"
echo ""
echo "Environment setup:"
echo "- Qt: $(qmake --version | head -1)"
echo "- Homebrew: $(brew --version | head -1)"
