# File-Transfer-Program-using-C-and-TCP-Socket-Programming

This project implements a simple file-transfer program in C using TCP socket programming. It consists of two parts: a client and a server. The program is designed to work on UNIX-based systems such as Linux and Ubuntu.

## Features
- Client-Server Architecture: The project is divided into a client and a server, enabling file transfer between the two.

- TCP Socket Programming: Utilizes TCP (Transmission Control Protocol) for reliable and connection-oriented communication.

## Getting Started
### Prerequisites
- C Compiler
- UNIX-based system (Linux, Ubuntu)

### Usage

1. Compile the Code:
#### `gcc client.c -o client`
#### `gcc server.c -o server`

2. Run the Server:
#### `./server <port_number>`

3. Run the Client:
#### `./client <filename> <server_IP_address> <port_number>`

## File Descriptions
#### client.c: Code for the client-side of the file transfer.

#### server.c: Code for the server-side of the file transfer.

### How it Works
- The server listens on a specified port.
- The client connects to the server, reads a file, and sends it to the server.
- The server receives the file and saves it as "Greet_received.txt."
## Contributing
Feel free to contribute to the project by opening issues or pull requests.
