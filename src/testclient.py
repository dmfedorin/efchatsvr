import socket

HOST = "10.67.33.247"  # The server's hostname or IP address
PORT = 80  # The port used by the server

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((HOST, PORT))

running = True

while running:
    uin = input(">: ")
    
    s.sendall(bytes(uin, "utf-8"))

    if (uin == ">exit"):
        running = False
    
    data = s.recv(1024)

    print(f"Received {data!r}")

s.close()
