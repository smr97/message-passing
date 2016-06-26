# message-passing
## Short practice code to learn message passing between posix threads.
This code uses 2 threads to demonstrate a working mailbox prototpe
that relies on the existing mqueue.h header and the corresponding POSIX message queue implementation.

## Compile command
Download and extract.
Run following command gcc -pthread message.c -o message -lrt
Execute ./message
Type in the desired message, and see it printed back to you. If you observe the code, scanf and printf are in 2 separate threads and no variable is accessed globally.
