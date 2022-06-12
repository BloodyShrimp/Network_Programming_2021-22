import socket
import time

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 2020  # The port used by the server

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
# s.sendall(b"\r\n")
# # s.sendall(b"\r\n2 2\r\n")
# s.sendall(b"10 20")
# s.sendall(b" 10 20 ")
# s.sendall(b"10\r\n")
s.sendall(b"50 60 20\r\n10")
s.sendall(b"0 123456 \r\n10 0")
s.sendall(b"1 22\r\n")
data = s.recv(1024)
print(f"Received {data!r}\n")
s.close()
