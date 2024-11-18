Banker's Algorithm for Deadlock Avoidance
Programming Assignment #2

Overview
This project implements the Banker's Algorithm to determine if a system is in a safe state. The system has:

5 Processes: P0 to P4
3 Resource Types:
A (10 instances)
B (5 instances)
C (7 instances)

How to Compile and Run (Linux)
```
g++ -o banker bankersalgo.cpp ./banker
```

Example Output:
```
Safe Sequence: P1, P3, P4, P0, P2
```
