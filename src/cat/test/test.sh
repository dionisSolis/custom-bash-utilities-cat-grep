#!/bin/bash

ORIGINAL_CAT="cat"
MY_CAT="../s21_cat"

OUT_ORIGINAL="cat.txt"
OUT_MY="my.txt"
VALGRIND_LOG="valgrind.log"

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
NC='\033[0m'

check_valgrind() {
    valgrind --leak-check=full --log-file="$VALGRIND_LOG" "$@" > /dev/null 2>&1
    if grep -q "ERROR SUMMARY: 0 errors" "$VALGRIND_LOG" && ! grep -q "definitely lost: [1-9]" "$VALGRIND_LOG"; then
        echo -e "${GREEN}Test passed${NC}"
    elif grep -q "definitely lost: [1-9]" "$VALGRIND_LOG"; then
        echo -e "${YELLOW}Test passed but with memory leaks${NC}"
    else
        echo -e "${RED}Test failed${NC}"
    fi
    rm -f "$VALGRIND_LOG"
}

compare_outputs() {
    diff -u "$OUT_ORIGINAL" "$OUT_MY" > /dev/null
    if [ $? -eq 0 ]; then
        check_valgrind $MY_CAT "$@"
    else
        echo -e "${RED}Test failed: output mismatch${NC}"
    fi
}

FLAGS=(
    ""
    "-b" "--number-nonblank"
    "-e" "-E"
    "-n" "--number"
    "-s" "--squeeze-blank"
    "-t" "-T" "-b -t"
)

TEST_FILES=("1.txt" "2.txt" "3.txt")

for flag in "${FLAGS[@]}"; do
    echo -n "Testing flag: $flag ... "
    $ORIGINAL_CAT $flag "${TEST_FILES[@]}" > "$OUT_ORIGINAL" 2>/dev/null
    $MY_CAT $flag "${TEST_FILES[@]}" > "$OUT_MY" 2>/dev/null
    compare_outputs $flag "${TEST_FILES[@]}"
done

rm -f "$OUT_ORIGINAL" "$OUT_MY" "$VALGRIND_LOG"