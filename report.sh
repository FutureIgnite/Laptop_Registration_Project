#!/bin/bash

INPUT_XML="memory_leaks_report.txt"
OUTPUT_TXT="clean_memory_report.txt"

echo "🧠 Memory Leak Report - $(date)" > "$OUTPUT_TXT"
echo "=====================================" >> "$OUTPUT_TXT"

# Total leak summary
grep -oP '(?<=<kind>)[^<]+' "$INPUT_XML" | sort | uniq -c | while read count kind; do
  echo "Leak Type: $kind | Count: $count" >> "$OUTPUT_TXT"
done

echo "" >> "$OUTPUT_TXT"
echo "🔍 Detailed Leaks:" >> "$OUTPUT_TXT"
echo "-------------------------------------" >> "$OUTPUT_TXT"

# Iterate over each <error> block
IFS=$'\n'
for error in $(awk '/<error>/{flag=1;next}/<\/error>/{print;flag=0}flag' "$INPUT_XML" | sed -e 's/^/    /'); do
  # Parse and display each <error> block with clarity
  xmlstarlet sel -t -m "//error" \
  -o "-------------------------------------" -n \
  -o "Leak Type       : " -v "kind" -n \
  -o "Bytes Leaked    : " -v "xwhat/leakedbytes" -n \
  -o "Blocks Affected : " -v "xwhat/leakedblocks" -n \
  -o "Location        : " -n \
  -m "stack/frame" \
    -o "  ↳ " -v "fn" -o " (" -v "file" -o ":" -v "line" -o ")" -n \
  -o "-------------------------------------" -n \
  "$INPUT_XML" >> "$OUTPUT_TXT" 
done

echo "=====================================" >> "$OUTPUT_TXT"
echo "✅ Report written to $OUTPUT_TXT"
