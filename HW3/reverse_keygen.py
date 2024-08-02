import subprocess

# Define the path to the executable and the arguments
exe_path = 'keygen.exe '

mapping = {}

for chr_idx in range(32, 127):
    # Run the executable with the arguments
    args = [chr(chr_idx)]
    if '*' == chr(chr_idx):
        pass
    result = subprocess.run([exe_path] + args, capture_output=True, text=True)

    mapping[result.stdout] = chr(chr_idx)

#mapping['8'] = '*'

def decode_keygen(key: str):
    return ''.join(mapping[char] for char in key if char in mapping)

print(decode_keygen('7VLV8OM84T9CKKMQ'))


