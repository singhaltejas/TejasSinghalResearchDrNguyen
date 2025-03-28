#!/bin/bash

DACAPO_JAR="dacapo-23.11-MR2-chopin.jar"
BENCHMARK1="avrora"
BENCHMARK2="eclipse"
LOG_FILE="benchmark.log"

# Clear previous log file
> "$LOG_FILE"

java -jar "$DACAPO_JAR" -s large "$BENCHMARK1" &
PID1=$!
java -jar "$DACAPO_JAR" -s large "$BENCHMARK2" &
PID2=$!


END_TIME=$((SECONDS + 60))

while [ $SECONDS -lt $END_TIME ]; do
    if ! ps -p $PID1 > /dev/null && ! ps -p $PID2 > /dev/null; then
        break  # Exit if both processes have finished
    fi
    
    # Collect CPU and Memory usage
    if ps -p $PID1 > /dev/null; then
        CPU1=$(ps -p $PID1 -o %cpu=)
        MEM1=$(ps -p $PID1 -o rss=)
        echo "[$(date)] $BENCHMARK1 - CPU: $CPU1% | MEM: $((MEM1/1024)) MB" >> "$LOG_FILE"
    fi
    
    if ps -p $PID2 > /dev/null; then
        CPU2=$(ps -p $PID2 -o %cpu=)
        MEM2=$(ps -p $PID2 -o rss=)
        echo "[$(date)] $BENCHMARK2 - CPU: $CPU2% | MEM: $((MEM2/1024)) MB" >> "$LOG_FILE"
    fi
    
    sleep 2
done

echo "Benchmarking completed. Log saved in $LOG_FILE"

