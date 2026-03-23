#!/bin/bash
TS=$(date +"%Y-%m-%d_%H%M")
FILE="stargate_snapshot_${TS}.tar.gz"

# Only archive files that exist to prevent 'stat' errors
FILES_TO_ARCHIVE=""
for f in quant_engine.cpp Makefile run_live.sh stargate_audit.csv run.sh; do
    if [ -f "$f" ]; then FILES_TO_ARCHIVE+="$f "; fi
done

echo "ARCHITECT LOG: Archiving $FILES_TO_ARCHIVE..."
tar -czf $FILE $FILES_TO_ARCHIVE
echo "SNAPSHOT SUCCESS: $FILE"
