#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "Testing all bad maps with Valgrind..."
echo "===================================="

check_memory_errors() {
    local output=$1
    local has_errors=0

    # Check for invalid reads
    if echo "$output" | grep -q "Invalid read"; then
        echo -e "${RED}Invalid read detected!${NC}"
        echo "$output" | grep -A 5 "Invalid read"
        has_errors=1
    fi

    # Check for invalid writes
    if echo "$output" | grep -q "Invalid write"; then
        echo -e "${RED}Invalid write detected!${NC}"
        echo "$output" | grep -A 5 "Invalid write"
        has_errors=1
    fi

    # Check for use of uninitialized values
    if echo "$output" | grep -q "Use of uninitialised value"; then
        echo -e "${RED}Use of uninitialized value detected!${NC}"
        echo "$output" | grep -A 5 "Use of uninitialised value"
        has_errors=1
    fi

    # Check for memory leaks
    if echo "$output" | grep -q "definitely lost:" && ! echo "$output" | grep -q "definitely lost: 0 bytes"; then
        echo -e "${RED}Memory leaks detected!${NC}"
        echo "$output" | grep -A 5 "definitely lost:"
        has_errors=1
    fi

    # Check for indirect leaks
    if echo "$output" | grep -q "indirectly lost:" && ! echo "$output" | grep -q "indirectly lost: 0 bytes"; then
        echo -e "${RED}Indirect memory leaks detected!${NC}"
        echo "$output" | grep -A 5 "indirectly lost:"
        has_errors=1
    fi

    # Check for still reachable blocks
    if echo "$output" | grep -q "still reachable:" && ! echo "$output" | grep -q "still reachable: 0 bytes"; then
        echo -e "${YELLOW}Still reachable blocks detected (potential leaks)${NC}"
        echo "$output" | grep -A 5 "still reachable:"
        has_errors=1
    fi

    if [ $has_errors -eq 0 ]; then
        echo -e "${GREEN}No memory errors detected${NC}"
        return 0
    fi
    return 1
}

for map in maps/bad/*.cub; do
    echo -e "\nTesting map: ${YELLOW}$map${NC}"
    echo "----------------------------------------"

    # Run with valgrind and capture output
    valgrind_output=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
                             --track-fds=yes --error-exitcode=1 ./cub3D "$map" 2>&1)
    exit_code=$?

    # Print program output (excluding valgrind output)
    echo "$valgrind_output" | grep -v "^==" | grep -v "^--"

    echo -e "\nValgrind Results:"
    echo "----------------"
    check_memory_errors "$valgrind_output"

    echo -e "\nExit code: $exit_code"
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}Program exited with error code $exit_code${NC}"
    fi
    echo "----------------------------------------"
done

echo -e "\nAll tests completed!"

