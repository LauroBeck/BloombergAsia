#!/bin/bash
export LD_LIBRARY_PATH=$(pwd)/ta-lib/src/.libs:$LD_LIBRARY_PATH
while true; do
    clear
    echo "============================================================"
    echo "  STARGATE CLUSTER | LIVE BREADTH MONITOR | $(date)"
    echo "============================================================"
    ./quant_engine
    echo "============================================================"
    sleep 30
done
