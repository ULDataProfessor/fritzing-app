#!/bin/bash
set -e

echo "🔧 Fritzing Parts Library Manager"
echo "================================="

PARTS_DIR="/Users/yoda/Downloads/release64/Fritzing.app/Contents/Resources/fritzing-parts"
ADAFRUIT_DIR="/Users/yoda/Downloads/Fritzing-Library"
BACKUP_DIR="/Users/yoda/Downloads/fritzing-parts-backup-$(date +%Y%m%d-%H%M%S)"

# Function to display usage
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --adafruit     Add Adafruit parts library"
    echo "  --sparkfun     Add SparkFun parts library"
    echo "  --custom DIR   Add custom parts from directory"
    echo "  --list         List available parts sources"
    echo "  --validate     Validate parts library"
    echo "  --backup       Create backup of current parts"
    echo "  --restore      Restore from backup"
    echo "  --help         Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 --adafruit                    # Add Adafruit library"
    echo "  $0 --custom /path/to/parts       # Add custom parts"
    echo "  $0 --validate                    # Validate current library"
}

# Function to create backup
create_backup() {
    echo "💾 Creating backup of current parts library..."
    if [ -d "$PARTS_DIR" ]; then
        cp -r "$PARTS_DIR" "$BACKUP_DIR"
        echo "✅ Backup created: $BACKUP_DIR"
    else
        echo "❌ Parts directory not found: $PARTS_DIR"
        exit 1
    fi
}

# Function to add Adafruit parts
add_adafruit_parts() {
    echo "🔌 Adding Adafruit parts library..."
    
    if [ ! -d "$ADAFRUIT_DIR" ]; then
        echo "📥 Cloning Adafruit Fritzing Library..."
        cd /Users/yoda/Downloads
        git clone https://github.com/adafruit/Fritzing-Library.git
    fi
    
    # Create contrib directory if it doesn't exist
    mkdir -p "$PARTS_DIR/contrib/adafruit"
    
    # Copy Adafruit parts
    echo "📋 Copying Adafruit parts..."
    cp -r "$ADAFRUIT_DIR/parts"/* "$PARTS_DIR/contrib/adafruit/" 2>/dev/null || true
    
    # Copy .fzbz files for easy import
    echo "📦 Copying Adafruit part bundles..."
    mkdir -p "$PARTS_DIR/contrib/adafruit/bundles"
    cp "$ADAFRUIT_DIR"/*.fzbz "$PARTS_DIR/contrib/adafruit/bundles/" 2>/dev/null || true
    
    echo "✅ Adafruit parts added successfully!"
    
    # Count parts
    ADAFRUIT_COUNT=$(find "$PARTS_DIR/contrib/adafruit" -name "*.fzpz" | wc -l)
    echo "📊 Adafruit parts added: $ADAFRUIT_COUNT"
}

# Function to add SparkFun parts
add_sparkfun_parts() {
    echo "⚡ Adding SparkFun parts library..."
    
    SPARKFUN_DIR="/Users/yoda/Downloads/SparkFun-Fritzing-Library"
    
    if [ ! -d "$SPARKFUN_DIR" ]; then
        echo "📥 Cloning SparkFun Fritzing Library..."
        cd /Users/yoda/Downloads
        git clone https://github.com/sparkfun/Fritzing-Library.git SparkFun-Fritzing-Library
    fi
    
    # Create contrib directory if it doesn't exist
    mkdir -p "$PARTS_DIR/contrib/sparkfun"
    
    # Copy SparkFun parts
    echo "📋 Copying SparkFun parts..."
    cp -r "$SPARKFUN_DIR/parts"/* "$PARTS_DIR/contrib/sparkfun/" 2>/dev/null || true
    
    echo "✅ SparkFun parts added successfully!"
    
    # Count parts
    SPARKFUN_COUNT=$(find "$PARTS_DIR/contrib/sparkfun" -name "*.fzpz" | wc -l)
    echo "📊 SparkFun parts added: $SPARKFUN_COUNT"
}

# Function to add custom parts
add_custom_parts() {
    local custom_dir="$1"
    
    if [ ! -d "$custom_dir" ]; then
        echo "❌ Custom parts directory not found: $custom_dir"
        exit 1
    fi
    
    echo "🔧 Adding custom parts from: $custom_dir"
    
    # Create contrib directory if it doesn't exist
    mkdir -p "$PARTS_DIR/contrib/custom"
    
    # Copy custom parts
    echo "📋 Copying custom parts..."
    cp -r "$custom_dir"/* "$PARTS_DIR/contrib/custom/" 2>/dev/null || true
    
    echo "✅ Custom parts added successfully!"
    
    # Count parts
    CUSTOM_COUNT=$(find "$PARTS_DIR/contrib/custom" -name "*.fzpz" -o -name "*.fzp" | wc -l)
    echo "📊 Custom parts added: $CUSTOM_COUNT"
}

# Function to list available parts sources
list_sources() {
    echo "📚 Available Parts Sources:"
    echo "=========================="
    echo ""
    echo "🔌 Adafruit Industries:"
    echo "   - Repository: https://github.com/adafruit/Fritzing-Library"
    echo "   - Parts: Arduino, Feather, Circuit Playground, LED Backpacks"
    echo "   - Command: $0 --adafruit"
    echo ""
    echo "⚡ SparkFun Electronics:"
    echo "   - Repository: https://github.com/sparkfun/Fritzing-Library"
    echo "   - Parts: Development boards, sensors, breakout boards"
    echo "   - Command: $0 --sparkfun"
    echo ""
    echo "🏭 Seeed Studio:"
    echo "   - Repository: https://github.com/fritzing/fritzing_parts"
    echo "   - Parts: Grove modules, development boards"
    echo "   - Command: $0 --seeed"
    echo ""
    echo "🔧 Custom Parts:"
    echo "   - Any directory with .fzp or .fzpz files"
    echo "   - Command: $0 --custom /path/to/parts"
    echo ""
    echo "📖 Additional Resources:"
    echo "   - Fritzing Parts Database: https://fritzing.org/parts/"
    echo "   - Community Parts: https://github.com/fritzing/fritzing-parts"
    echo "   - Part Creation Guide: https://fritzing.org/learning/tutorials/creating-custom-parts/"
}

# Function to validate parts library
validate_parts() {
    echo "🔍 Validating parts library..."
    
    if [ ! -d "$PARTS_DIR" ]; then
        echo "❌ Parts directory not found: $PARTS_DIR"
        exit 1
    fi
    
    echo "📊 Parts Library Statistics:"
    echo "=========================="
    
    # Count parts by category
    CORE_COUNT=$(find "$PARTS_DIR/core" -name "*.fzp" 2>/dev/null | wc -l || echo 0)
    CONTRIB_COUNT=$(find "$PARTS_DIR/contrib" -name "*.fzpz" -o -name "*.fzp" 2>/dev/null | wc -l || echo 0)
    USER_COUNT=$(find "$PARTS_DIR/user" -name "*.fzp" 2>/dev/null | wc -l || echo 0)
    OBSOLETE_COUNT=$(find "$PARTS_DIR/obsolete" -name "*.fzp" 2>/dev/null | wc -l || echo 0)
    
    echo "Core parts:      $CORE_COUNT"
    echo "Contrib parts:   $CONTRIB_COUNT"
    echo "User parts:      $USER_COUNT"
    echo "Obsolete parts:  $OBSOLETE_COUNT"
    echo "Total parts:     $((CORE_COUNT + CONTRIB_COUNT + USER_COUNT + OBSOLETE_COUNT))"
    echo ""
    
    # Check for duplicate module IDs
    echo "🔍 Checking for duplicate module IDs..."
    find "$PARTS_DIR" -name "*.fzp" -exec grep -l "moduleId=" {} \; | xargs grep -h "moduleId=" | sort | uniq -d > /tmp/duplicates.txt 2>/dev/null || true
    
    if [ -s /tmp/duplicates.txt ]; then
        echo "⚠️  Found duplicate module IDs:"
        cat /tmp/duplicates.txt
    else
        echo "✅ No duplicate module IDs found"
    fi
    
    # Check git repository status
    if [ -d "$PARTS_DIR/.git" ]; then
        echo "🔄 Git repository status:"
        cd "$PARTS_DIR"
        git status --porcelain | wc -l | xargs echo "Uncommitted changes:"
        echo "Last commit: $(git log -1 --format='%h - %s (%cr)')"
    fi
    
    echo ""
    echo "✅ Parts library validation complete!"
}

# Function to restore from backup
restore_backup() {
    echo "🔄 Restoring from backup..."
    
    # Find the most recent backup
    LATEST_BACKUP=$(ls -td /Users/yoda/Downloads/fritzing-parts-backup-* 2>/dev/null | head -1)
    
    if [ -z "$LATEST_BACKUP" ]; then
        echo "❌ No backup found. Available backups:"
        ls -la /Users/yoda/Downloads/fritzing-parts-backup-* 2>/dev/null || echo "No backups available"
        exit 1
    fi
    
    echo "📁 Restoring from: $LATEST_BACKUP"
    
    # Create backup of current state
    create_backup
    
    # Restore from backup
    rm -rf "$PARTS_DIR"
    cp -r "$LATEST_BACKUP" "$PARTS_DIR"
    
    echo "✅ Parts library restored successfully!"
}

# Main script logic
case "${1:-}" in
    --adafruit)
        create_backup
        add_adafruit_parts
        validate_parts
        ;;
    --sparkfun)
        create_backup
        add_sparkfun_parts
        validate_parts
        ;;
    --custom)
        if [ -z "${2:-}" ]; then
            echo "❌ Please specify custom parts directory"
            echo "Usage: $0 --custom /path/to/parts"
            exit 1
        fi
        create_backup
        add_custom_parts "$2"
        validate_parts
        ;;
    --list)
        list_sources
        ;;
    --validate)
        validate_parts
        ;;
    --backup)
        create_backup
        ;;
    --restore)
        restore_backup
        ;;
    --help|help|-h)
        usage
        ;;
    "")
        echo "❌ No option specified"
        echo ""
        usage
        exit 1
        ;;
    *)
        echo "❌ Unknown option: $1"
        echo ""
        usage
        exit 1
        ;;
esac

echo ""
echo "🎉 Parts management complete!"
echo ""
echo "Next steps:"
echo "1. Restart Fritzing to load new parts"
echo "2. Check the 'contrib' bin in the parts palette"
echo "3. Use 'File > Import...' to import .fzbz files"
