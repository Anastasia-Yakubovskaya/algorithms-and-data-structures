import subprocess
import unittest

class TestASCII85withPython(unittest.TestCase):
    def run_encoder(self, input_data):
        process = subprocess.Popen(['./work1', '1'],
                                 stdin=subprocess.PIPE,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE)
        stdout, stderr = process.communicate(input=input_data.encode())
        return stdout.decode('utf-8', errors='replace').strip(), process.returncode, stderr.decode()
     
    def run_decoder(self, input_data):
        process = subprocess.Popen(['./work1', '2'],
                                 stdin=subprocess.PIPE,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE)
        stdout, stderr = process.communicate(input=input_data.encode())
        return stdout.decode('utf-8', errors='replace').strip(), process.returncode, stderr.decode()
        
    def test_encode_with_implementation(self):
        test_cases = [
            ("Hello", "87cURDZ"),  
            ("Test", "<+U,m"), 
        ]
        
        for input_str, expected in test_cases:
            with self.subTest(input_str=input_str):
                cpp_encoded, returncode, stderr = self.run_encoder(input_str)
                self.assertEqual(returncode, 0)
                self.assertEqual(cpp_encoded, expected)
                
    def test_decode_valid_strings(self):
        test_cases = [
            ("87cURDZ", "Hello"),
            ("<+U,m", "Test"),
        ]
        
        for input_str, expected in test_cases:
            with self.subTest(input_str=input_str):
                cpp_decoded, returncode, stderr = self.run_decoder(input_str)
                self.assertEqual(returncode, 0)
                self.assertEqual(cpp_decoded, expected)
                
    def test_decode_invalid_chars(self):
        test_cases = [
            ("<+U,m\x01", "Недопустимый символ"), 
            ("hello\x7f", "Недопустимый символ"), 
            ("привет", "Недопустимый символ"),     
            ("\x00\x01", "Недопустимый символ")   
        ]
        
        for input_str, expected_msg in test_cases:
            with self.subTest(input_str=input_str):
                process = subprocess.Popen(
                    ['./work1', '2'],
                    stdin=subprocess.PIPE,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    universal_newlines=True,
                    encoding='utf-8',
                    errors='replace'
                )
                stdout, stderr = process.communicate(input=input_str + '\n')
                
                self.assertIn(expected_msg, stderr)
                self.assertEqual(process.returncode, 0)
                

if __name__ == '__main__':
    unittest.main(verbosity=2)
