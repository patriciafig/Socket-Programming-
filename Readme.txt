
*******************************************************
*  Name      :  Patricia Figueroa
*  Class     :  CSCI 4761
*  Lab#      :  Extra Credit Lab
*  Due Date  :  May 10, 2016
*******************************************************
                 Read Me

*******************************************************
*  Description of the program
*******************************************************

The goal of this assignment was to learn how to develop
an application protocol as well as build an application
over UNIX (Linux) socket.
This programming assignment, is a simple on-line login
verification program that implements the protocol,  a
client and a server that communicate using the protocol
through TCP sockets.
The client sends a username and password to the server
and the server will verifies whether the username and
password is correct or not.
*******************************************************
*  Source files
*******************************************************

Name:  client.c
       clientLogin.c
       clientLogin.h
       clientSignUp.c

       server.c
       Serverlogin.c

*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.

   The program was developed and tested on CLion 2017.1.1.
   It was compiled, run, and tested on macOS Sierra.

*******************************************************
*  How to build and run the program
*******************************************************

To run the server
-Go into folder Server and run make
an a.out file will be created
-run code as ./a.out xxxx (xxxx is any port number that
you wish to run)

To run the client code
-Go into folder Client and run make
an a.out file will be created
-run code as ./a.out ip_addr xxxx (ip_addr should be the ip
address on which the server is running and xxxx the port number
for the same)


for example....

server side
./a.out 8844

client side
./a.out 127.0.0.1 8844 (using localhost as both are running on
the same machine)

Must have UserInfo.txt file available along with the server code