#!/bin/bash
# 1. Quick Rebuild
make clean && make

# 2. Set Library Path
export LD_LIBRARY_PATH=$(pwd)/ta-lib/src/.libs:$LD_LIBRARY_PATH

# 3. Execute with Timestamp
echo "--- STARGATE EXECUTION: $(date) ---"
./quant_engine
