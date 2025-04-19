#!/bin/bash

ORIGINAL_GREP="grep"
MY_GREP="../s21_grep"

OUT_ORIGINAL="out_original.txt"
OUT_MY="out_my.txt"
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
        check_valgrind $MY_GREP "$@"
    else
        echo -e "${RED}Test failed: output mismatch${NC}"
    fi
}

FLAGS=("-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-f" "-o")
PATTERN="a{3}"
PATTERN_FILE="patterns.txt"
TEST_FILES=("1.txt" "2.txt" "3.txt")

for flag in "${FLAGS[@]}"; do
    echo -n "Testing flag: $flag ... "
    if [ "$flag" == "-f" ]; then
        $ORIGINAL_GREP $flag "$PATTERN_FILE" "${TEST_FILES[@]}" > "$OUT_ORIGINAL" 2>/dev/null
        $MY_GREP $flag "$PATTERN_FILE" "${TEST_FILES[@]}" > "$OUT_MY" 2>/dev/null
        compare_outputs $flag "$PATTERN_FILE" "${TEST_FILES[@]}"
    else
        $ORIGINAL_GREP $flag "$PATTERN" "${TEST_FILES[@]}" > "$OUT_ORIGINAL" 2>/dev/null
        $MY_GREP $flag "$PATTERN" "${TEST_FILES[@]}" > "$OUT_MY" 2>/dev/null
        compare_outputs $flag "$PATTERN" "${TEST_FILES[@]}"
    fi
done

COMBINATIONS=(
    "-iv" "-ic" "-il" "-in" "-ih" "-is" "-if" "-io"
    "-vc" "-vl" "-vn" "-vh" "-vs" "-vf" "-vo"
    "-cl" "-cn" "-ch" "-cs" "-cf" "-co"
    "-ln" "-lh" "-ls" "-lf" "-lo"
    "-nh" "-ns" "-nf" "-no"
    "-hs" "-hf" "-ho"
    "-sf" "-so"
    "-fo"
    "-ei" "-ev" "-ec" "-el" "-en" "-eh" "-es" "-ef" "-eo"
)

for combo in "${COMBINATIONS[@]}"; do
    echo -n "Testing combination: $combo ... "
    $ORIGINAL_GREP $combo "$PATTERN" "${TEST_FILES[@]}" > "$OUT_ORIGINAL" 2>/dev/null
    $MY_GREP $combo "$PATTERN" "${TEST_FILES[@]}" > "$OUT_MY" 2>/dev/null
    compare_outputs $combo "$PATTERN" "${TEST_FILES[@]}"
done

rm -f "$OUT_ORIGINAL" "$OUT_MY" "$VALGRIND_LOG"