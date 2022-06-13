This README consists of what language this project uses, and instructions/commands on how to run and compile the program in the TXST CS Department Linux Server

The following project was compiled and ran using C++ and also in Kali Linux which is a VirtualBox that I have installed on my PC.

Step 1: Open a command-line terminal on Kali Linux
Step 2: ssh into the TXST CS Department Linux server (we will use zeus.cs.txstate.edu)
		- ssh NetID@zeus.cs.txstate.edu
Step 3: cd into the following class directory in the server containing the project
		- cd CS_Fundamentals
Step 4: cd into the following directory containing the project in "CS_Fundamentals" (In this case, I called it PA1)
		- cd PA1
Step 5: Compile the first program with the following command:
		- g++ -std=c++11 PA1_Q1.cpp -o PA1_Q1
			*specified c++11 for the libraries
			*-o is an executable that will compile and name the program PA1_Q1
Step 6: Run the first program with the following command:
		- ./PA1_Q1
The following results will be displayed:
	*Actual average arrival rate
	*Actual average service time
	
ssh NetID@zeus.cs.txstate.edu
cd CS_Fundamentals
cd PA1
g++ -std=c++11 PA1_Q1.cpp -o PA1_Q1
./PA1_Q1

After compiling and running the first program, we can now do the same with the second problem.

Step 7: While in the same directory, compile the program with the second problem with the following command:
	- g++ -std=c++11 PA1_Q2.cpp -o PA1_Q2
Step 8: Run that program with the following command:
	- ./PA1_Q2
The following results will be displayed:
	*Actual MTBF for Server A.
	*Actual MTBF for Server B.
	*What hour the servers will both fail.
(Can repeate Steps 1-4 if accidentally close out of Kali Linux)
g++ -std=c++11 PA1_Q2.cpp -o PA1_Q2
./PA1_Q2		