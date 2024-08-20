import subprocess

# Path to the .exe file
exe_path = "hw4_client.exe"

# Start the process
process = subprocess.Popen(exe_path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

# Provide user_name
output, error = process.communicate(input="archer\n56M9JNQ60KB7APLC\nUSER")
print(output)

