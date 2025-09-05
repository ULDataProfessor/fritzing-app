#!/bin/bash
set -e

echo "🔧 Fritzing Parts Library Optimizer"
echo "==================================="

PARTS_DIR="/Users/yoda/Downloads/release64/Fritzing.app/Contents/Resources/fritzing-parts"
BACKUP_DIR="/Users/yoda/Downloads/fritzing-parts-backup-$(date +%Y%m%d-%H%M%S)"

if [ ! -d "$PARTS_DIR" ]; then
    echo "❌ Parts directory not found: $PARTS_DIR"
    exit 1
fi

echo "📁 Parts directory: $PARTS_DIR"

# Create backup
echo "💾 Creating backup..."
cp -r "$PARTS_DIR" "$BACKUP_DIR"
echo "✅ Backup created: $BACKUP_DIR"

# Optimize parts database
echo "🗄️  Optimizing parts database..."
cd "$PARTS_DIR"

# Remove duplicate parts (keep only the latest version)
echo "🔍 Checking for duplicate parts..."
find core/ -name "*.fzp" | sort | while read -r file; do
    basename_file=$(basename "$file")
    duplicates=$(find core/ -name "$basename_file" | wc -l)
    if [ "$duplicates" -gt 1 ]; then
        echo "⚠️  Found $duplicates instances of $basename_file"
        # Keep the most recent one
        find core/ -name "$basename_file" -exec ls -t {} + | tail -n +2 | xargs rm -f
        echo "✅ Removed duplicate instances"
    fi
done

# Optimize SVG files (remove unnecessary whitespace)
echo "🎨 Optimizing SVG files..."
find . -name "*.svg" -exec sed -i '' 's/[[:space:]]*$//' {} \;
find . -name "*.svg" -exec sed -i '' '/^[[:space:]]*$/d' {} \;

# Create optimized parts index
echo "📋 Creating optimized parts index..."
find core/ -name "*.fzp" | wc -l > parts_count.txt
echo "✅ Parts count: $(cat parts_count.txt)"

# Optimize git repository
echo "🔄 Optimizing git repository..."
if [ -d ".git" ]; then
    git gc --aggressive --prune=now
    echo "✅ Git repository optimized"
fi

# Create parts validation report
echo "📊 Creating parts validation report..."
echo "Parts Library Validation Report" > validation_report.txt
echo "Generated: $(date)" >> validation_report.txt
echo "=================================" >> validation_report.txt
echo "" >> validation_report.txt

echo "Core parts: $(find core/ -name "*.fzp" | wc -l)" >> validation_report.txt
echo "Contrib parts: $(find contrib/ -name "*.fzp" 2>/dev/null | wc -l || echo 0)" >> validation_report.txt
echo "User parts: $(find user/ -name "*.fzp" 2>/dev/null | wc -l || echo 0)" >> validation_report.txt
echo "Obsolete parts: $(find obsolete/ -name "*.fzp" 2>/dev/null | wc -l || echo 0)" >> validation_report.txt

echo "✅ Validation report created: validation_report.txt"

# Calculate space savings
ORIGINAL_SIZE=$(du -sh "$BACKUP_DIR" | cut -f1)
CURRENT_SIZE=$(du -sh "$PARTS_DIR" | cut -f1)

echo ""
echo "📊 Optimization Results:"
echo "Original size: $ORIGINAL_SIZE"
echo "Optimized size: $CURRENT_SIZE"
echo "Backup location: $BACKUP_DIR"
echo ""
echo "✅ Parts library optimization complete!"
