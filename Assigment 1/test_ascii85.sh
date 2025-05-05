#!/bin/bash

set -e

PROGRAM="./ascii85"
TEST_DIR="test_data"
mkdir -p "$TEST_DIR"

cleanup() {
    rm -rf "$TEST_DIR"
}

trap cleanup EXIT

generate_test_file() {
    local size=$1
    head -c "$size" /dev/urandom | tr -d '\000' > "$TEST_DIR/data_$size.bin"
}

hexdiff() {
    echo "Hex diff between expected and actual:"
    python3 -c "
import sys
with open('$1', 'rb') as f1, open('$2', 'rb') as f2:
    d1 = f1.read().hex()
    d2 = f2.read().hex()
    print(f'Expected: {d1[:80]}...')
    print(f'Actual:   {d2[:80]}...')
    for i, (c1, c2) in enumerate(zip(d1, d2)):
        if c1 != c2:
            print(f'First difference at position {i}: {c1} vs {c2}')
            break
"
}

test_encoding() {
    echo "Testing Encoding"
    for size in 10 100 1000; do
        echo -n "Test with $size bytes... "
        generate_test_file "$size"
        
        python3 -c "
import base64, sys
with open('$TEST_DIR/data_$size.bin', 'rb') as f:
    data = f.read()
    encoded = base64.a85encode(data).decode('ascii')
    with open('$TEST_DIR/python_$size.a85', 'w') as out:
        out.write(encoded)
"
        
        "$PROGRAM" < "$TEST_DIR/data_$size.bin" > "$TEST_DIR/our_$size.a85"
        
        if ! cmp -s "$TEST_DIR/python_$size.a85" "$TEST_DIR/our_$size.a85"; then
            echo "FAIL"
            hexdiff "$TEST_DIR/python_$size.a85" "$TEST_DIR/our_$size.a85"
            exit 1
        else
            echo "OK"
        fi
    done
}

test_decoding() {
    echo "Testing Decoding"
    for size in 10 100 1000; do
        echo -n "Test with $size bytes... "
        generate_test_file "$size"
        
        python3 -c "
import base64, sys
with open('$TEST_DIR/data_$size.bin', 'rb') as f:
    sys.stdout.buffer.write(base64.a85encode(f.read()))
" > "$TEST_DIR/encoded_$size.a85"
        
        "$PROGRAM" -d < "$TEST_DIR/encoded_$size.a85" > "$TEST_DIR/decoded_$size.bin"
        
        if ! cmp -s "$TEST_DIR/data_$size.bin" "$TEST_DIR/decoded_$size.bin"; then
            echo "FAIL"
            exit 1
        else
            echo "OK"
        fi
    done
}

test_error_handling() {
    echo "Testing Incorrect Data Handling"
    
    # Тест-кейсы: описание -> (данные, ожидаемый код возврата)
    declare -A test_cases=(
        ["Empty input"]=":1"
        ["Multiple 'z'"]="zzzz:1"
        ["Valid data"]="9jqo^:0"
    )
    
    for desc in "${!test_cases[@]}"; do
        IFS=':' read -r data expected <<< "${test_cases[$desc]}"
        echo -n "Test case: $desc... "
        
        set +e
        echo -n "$data" | "$PROGRAM" -d >/dev/null 2>&1
        actual=$?
        set -e
        
        if [ $actual -eq $expected ]; then
            echo "PASS"
        else
            echo "FAIL (got $actual, expected $expected)"
            exit 1
        fi
    done
}

test_encoding
test_decoding
test_error_handling

echo "All tests passed successfully!"
exit 0
