This is Programming / Reverse Engineering.

## Description

A compiled chat server is provided to the player along with a rough skeleton of the C code used to create it. The server has a function that will print the flag, but it is obfuscated as to not be easily reverse engineered. When the server binary is executed, it prompts the user to enter a start command value, a listening address, and a listening port. There are two start command values: 0 - record messages to a file, 1 - print flag. The only valid user entered start command is 0. However, there is a bug in the scanf function for the listening port which allows the player to overwrite the start command value to 1 and print the flag when a message is sent to the server.

## Challenge

> That Python dead drop program put Aurora Pharmaceuticals' IT team on high alert; they looked closer at notifications in their Security Operation Center (SOC) and identified even more malware deep in the network! They retrieved a compiled binary along with some rough code from yet another infected user workstation. It appears to be some sort of Command and Control server, but requires a password to be accessed. Intel indicates that the full flag from “PROGO3 - Dead Drop” may work as the password.. Dig into this program and see what secrets it holds.

> Files:
>
> 1\. PROG05
>
> 2\. not_C2_server.c

## Hints

1. Although the server logs client messages by default, it does appear to have another function which produces the flag when executed.
2. Whoever wrote this server must not have a heap of experience. Our C code Subject Matter Experts analyzed the code and reported the compiled server can be exploited with certain user provided values to print the secret when a client sends it a message.
3. Our C code analysts reported that certain listening port inputs cause this program to print an error. See if you can leverage that to print the flag instead.

## Solution

See PROG05.c for the full chat server code.

1. Execute the compiled chat server.
2. Enter the password from PROG04
   1. flag{the current plan is world domination}
3. Enter the only valid command number.
   1. 0
4. Enter a listening address.
   1. 0.0.0.0
5. Enter a listening port between 65536 and 131071 (inclusive). This is the valid range of numbers that will overflow the listening port value and set start_cmd to 1 which causes the server to print the flag when it receives a message.
   1. 120000
6. The server will print out “Listening for connections on 0.0.0.0:54464”. Connect to the listening port with netcat and send any message.
   1. nc 127.0.0.1 54464
   2. Test message.
7. The server will print the flag.
   1. flag{heaps and stacks and bugs oh my!}

## Flag

flag{heaps and stacks and bugs oh my!}
