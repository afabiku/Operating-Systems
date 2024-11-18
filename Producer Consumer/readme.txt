Producer-Consumer Shared Memory Program
This project demonstrates a Producer-Consumer solution using shared memory and semaphores to enable synchronized data exchange between two processes.
The Producer generates random integers and places them in a shared memory buffer, while the Consumer retrieves and processes these values.

Compilation and Execution
To compile and run the program on a Linux terminal:
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer
./producer & ./consumer &


Expected Output
Upon running, you will see an output similar to the following as Producer and Consumer add and remove items in the shared buffer:

Producer created item 4 at position [1]
Consumer removed item 1 from position [0]
Consumer removed item 4 from position [1]
Producer created item 6 at position [0]
Producer created item 4 at position [1]
Consumer removed item 6 from position [0]
Consumer removed item 4 from position [1]
Producer created item 6 at position [0]
Producer created item 0 at position [1]
Consumer removed item 6 from position [0]
Consumer removed item 0 from position [1]
Producer created item 5 at position [0]
Producer created item 0 at position [1]
Consumer removed item 5 from position [0]
Consumer removed item 0 from position [1]
Producer created item 9 at position [0]
Consumer removed item 9 from position [0]

This output demonstrates synchronized interactions where the Producer and Consumer share the buffer efficiently, 
with semaphores ensuring that both processes operate safely without overwriting each other’s data.