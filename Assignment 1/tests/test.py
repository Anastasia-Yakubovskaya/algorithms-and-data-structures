#!/usr/bin/env python3
import base64
import subprocess
import random
import tempfile
import os


PROGRAM_NAME = "./ascii85"

def random_bytes(size, bad_bytes=None):
    if bad_bytes is None:
        bad_bytes = []
    random_data = []
    while len(random_data) < size:
        byte = random.randint(1, 255)  
        if byte not in bad_bytes:  
            random_data.append(byte)
    return bytes(random_data)

def test_encode_ascii85():
    print("Testing Encoding")
    
    for size in [10, 100, 1000]:
        print(f"Test with {size} bytes")
        
        random_data = random_bytes(size, bad_bytes=[10])  
        
        python_encoded = base64.a85encode(random_data, adobe=False).decode('ascii')
        
        with tempfile.NamedTemporaryFile() as temp_in:
            temp_in.write(random_data)
            temp_in.flush()
            
            our_encoded = subprocess.check_output(
                f"{PROGRAM_NAME} < {temp_in.name}",
                shell=True
            ).decode('ascii').strip()
            
            if python_encoded != our_encoded:
                print(f"Error with encoding on {size} bytes")
                print(f"Python encoded: {python_encoded[:50]}...")
                print(f"Our encoded: {our_encoded[:50]}...")
            else:
                print("Encoding tests passed successfully")
                
def test_decode_ascii85():
    print("Testing Decoding")
    
    for size in [10, 100, 1000]:
        print(f"Test with {size} bytes")
        
        random_data = random_bytes(size, bad_bytes=[10])  
        
        python_encoded = base64.a85encode(random_data, adobe=False)
          
        with tempfile.NamedTemporaryFile() as temp_encoded:
            temp_encoded.write(python_encoded)
            temp_encoded.flush()
            
            our_decoded = subprocess.check_output(
                f"{PROGRAM_NAME} -d < {temp_encoded.name}",
                shell=True
            )
            
            if random_data != our_decoded:
                print(f"Error with decoding on {size} bytes")
                print(f"Python decoded: {python_encoded[:50]}...")
                print(f"Our decoded: {our_encoded[:50]}...")
            else:
                print("Decoding tests passed successfully") 
                
                
def test_incorrect_data():
    print("Testing Incorrect Data Handling")
    
    incorrect_data = [
        ("", "Empty input"),
        ("zzzz", "Multiple 'z' for zeros"),
        ("~~~", "Invalid symbols")
    ]
    
    for data, description in incorrect_data:
        print(f"Test case: {description}")
        
        try:
            result = subprocess.run(
                [PROGRAM_NAME, "-d"],
                input=data.encode('ascii'), 
                capture_output=True,
                text=False,
                timeout=1
            )
            
            if result.returncode == 0:
                print(f"FAIL: Accepted invalid input - {description}")
                print(f"Input: {data[:20]!r}")
            else:
                print(f"PASS: Rejected as expected ")
                
        except subprocess.TimeoutExpired:
            print("FAIL: Timeout on invalid input")
        except Exception as e:
            print(f"ERROR: {type(e).__name__}: {e}")          
        

if __name__ == "__main__":         
    try:
        test_encode_ascii85()
        test_decode_ascii85()
        test_incorrect_data()
        print("All tests passed successfully")
    except Exception as e:
        print(f"Unexpected error: {e}")
        exit(1)
