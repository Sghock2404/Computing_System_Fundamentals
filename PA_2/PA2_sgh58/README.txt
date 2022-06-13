This README consists of what language this project uses, and instructions/commands on how to run and compile the program in the TXST CS Department Linux Server

The following project was compiled and ran using C++ and also in Kali Linux which is a VirtualBox that I have installed on my PC.

Step 1: Open a command-line terminal on Kali Linux
Step 2: Use the command "ssh" to log in to the TXST CS Department Linux server (we will use zeus.cs.txstate.edu)
		- ssh NetID@zeus.cs.txstate.edu
Step 3: Use the command "cd" to access the following class directory in the server containing the project
		- cd CS_Fundamentals
Step 4: Use "cd" into the following directory containing the project in "CS_Fundamentals" (In this case, I called it PA2)
		- cd PA2
Step 5: Compile the first program with the following command:
		- g++ -std=c++11 PA_2.cpp -o PA_2
			*specified c++11 for the libraries used in the code
			*-o is an executable that will compile and name the program PA_2
Step 6: Run the first program with the following command and with two inputs. (The first input is the average arrival rate (lambda) and the second input is the service time):
-Example(s):	./PA_2 10 0.04
			./PA_2 11 0.04
			./PA_2 29 0.04
			./PA_2 30 0.04

The following metrics will be calculated and will be displayed:
	- Average turnaround time of processes
	- Total throughput (number of processes done per unit time)
	- Average CPU utilization
	- Average number of processes in the Ready Queue