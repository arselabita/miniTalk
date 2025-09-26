import os
import subprocess
import time

class Colors:
	RED = '\033[91m'
	GREEN = '\033[92m'
	END = '\033[0m'

failed_commands = []

print("Starting tests... If they are taking too long, please check your code for infinite loops.")
time.sleep(3)

# Step 1: Test Makefile
try:
	makefileoutpout = subprocess.check_output("make", stderr=subprocess.STDOUT)
	print(makefileoutpout.decode())
	print("--------------------")
	print(Colors.GREEN + "Makefile test passed" + Colors.END)
except subprocess.CalledProcessError as e:
	print(Colors.RED + "Makefile test failed" + Colors.END)
	print(e.output.decode())
	exit(1)

time.sleep(1)

# Step 2: Test Norminette
try:
	norminetteoutpout = subprocess.check_output("norminette", stderr=subprocess.STDOUT)
	print(norminetteoutpout.decode())
	print("--------------------")
	print(Colors.GREEN + "Norminette test passed" + Colors.END)
except subprocess.CalledProcessError as e:
	print(Colors.RED + "Norminette test failed" + Colors.END)
	print(e.output.decode())
	exit(1)
	
time.sleep(1)

# Step 3: Check if ./server and ./client exist

if not os.path.isfile("./server") or not os.path.isfile("./client"):
	print(Colors.RED + "./server or ./client does not exist" + Colors.END)
print(Colors.GREEN + "./server and ./client exist" + Colors.END)

time.sleep(1)

# Step 4: Test communication between ./server and ./client 
# (./server should print "Server PID: <pid>" and wait indefinitely for a message from ./client)
messages = ["https://pastebin.com/raw/8sU1qgUR", "https://pastebin.com/raw/4bNigh8t", "https://pastebin.com/raw/P1cN1922", "https://pastebin.com/raw/akXKnJ52", "https://pastebin.com/raw/zSGxDyt4"]
total_time = 0
num_tests = 0
num_failures = 0
for message in messages:
	msglog = message
	message = subprocess.check_output(["curl", message]).decode()
	server = subprocess.Popen(["./server"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	start_time = time.time()
	client = subprocess.Popen(["./client", str(server.pid), message], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	while (client.stdout.read().decode()):
		if time.time() - start_time > 20:
			break
		time.sleep(1)
	server.terminate()
	end_time = time.time()
	serveroutpout = server.stdout.read().decode()
	time_taken = end_time - start_time
	if message in serveroutpout:
		print(msglog)
		print(Colors.GREEN + f"Communication test passed in {str(round(time_taken, 3))}s" + Colors.END)
	else:
		print(serveroutpout)
		print(Colors.RED + "Communication test failed" + Colors.END)
		failed_commands.append(f"./client {str(server.pid)} with {msglog} as text")
		num_failures += 1
	total_time += time_taken
	num_tests += 1

# Step 4.5: Test communication between ./server and ./client with a large message like "hehe" * 1000 multiple times to the same server
print("Next part will not validate the server output, only check the communication time.")
message = "hehe" * 2500
server = subprocess.Popen(["./server"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
for i in range(6):
	print(f"Testing 'hehe' * 1000 {i+1}/6")
	start_time = time.time()
	client = subprocess.Popen(["./client", str(server.pid), message], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	while (client.stdout.read().decode()):
		time.sleep(1)
	end_time = time.time()
	time_taken = end_time - start_time
	print(Colors.GREEN + f"Communication test passed in {str(round(time_taken, 3))}s" + Colors.END)
	total_time += time_taken
	num_tests += 1
	time.sleep(1)
server.terminate()
	

time.sleep(1)

# Step 5: Parsing test for client, the format is ./client <server_pid> <message>
tests = ['./client 1234', './client 0', './client 154 12134', './client 554 5773 44130', './client', './client 2147483648 "hehe"', './client hehe hehe', './client -2147483649 "hehe"', './client 0 "hehe"', './client 000 000']
num_parsing_failures = 0
for test in tests:
		print(f"Testing {test}")
		client = subprocess.Popen(test.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE, preexec_fn=os.setpgrp)
		client.wait()
		clientoutpout = client.stdout.read().decode()
		if "ERROR" in clientoutpout.upper():
			print(Colors.GREEN + f"Parsing test passed !" + Colors.END)
		else:
			print(Colors.RED + f"Parsing test failed for {test}" + Colors.END)
			failed_commands.append(test)
			num_parsing_failures += 1

time.sleep(1)

# Recap
subprocess.Popen("make fclean", shell=True).wait()
print("--------------------")
print("Test Recap:")
print(f"Average communication time: {round(total_time/num_tests, 3)}s")
print(f"Number of communication test failures: {num_failures}")
print(f"Number of parsing test failures: {num_parsing_failures}")
if failed_commands:
	print("Failed commands:")
	for command in failed_commands:
		print(command)

os.system("rm -f tester.py")