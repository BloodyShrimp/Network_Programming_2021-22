import socket
import os
import atexit
import time

class automata:
    def __init__(self):
        self.state = 'I'
        self.sum = 0
        self.number = 0
    
    def step(self, symbol):
        # print(f'initial state {self.state}')
        # print(f'symbol: {symbol}')
        if self.state == 'I':
            self.reset()
            if (symbol >= 48 and symbol <= 57):
                self.state = 'C'
                self.number = 10 * self.number + (symbol - 48)
            elif symbol == 13:
                self.state = 'RERR'
                return b'ERROR\r\n'
            else:
                self.state = 'ERR'
                return b'ERROR\r\n'
        
        elif self.state == 'C':
            if (symbol >= 48 and symbol <= 57):
                self.state = 'C'
                self.number = 10 * self.number + (symbol - 48)
            elif symbol == 32:
                self.state = 'S'
                self.sum = self.sum + self.number
                self.number = 0
            elif symbol == 13:
                self.state = 'R'
            else:
                self.state = 'ERR'
                return b'ERROR\r\n'

        elif self.state == 'S':
            if (symbol >= 48 and symbol <= 57):
                self.state = 'C'
                self.number = 10 * self.number + (symbol - 48)
            elif symbol == 13:
                self.state = 'RERR'
            else:
                self.state = 'ERR'
                return b'ERROR\r\n'

        elif self.state == 'R':
            if symbol == 10:
                self.state = 'I'
                self.sum = self.sum + self.number
                return f'{self.sum}\r\n'.encode()
            else:
                self.state = 'ERR'
                return b'ERROR\r\n'
        
        elif self.state == 'ERR':
            if symbol == 13:
                self.state = 'RERR'
            else:
                self.state = 'ERR'
            return b'ERROR\r\n'

        elif self.state == 'RERR':
            if symbol == 10:
                self.state = 'I'
            else:
                self.state = 'ERR'
            return b'ERROR\r\n'

        # print(f'final state {self.state}')
        return b'WIP'

    def reset(self):
        self.state = 'I'
        self.sum = 0
        self.number = 0
    
def closing(sock):
    sock.close()
    print('Closed socket')

port = 2020
message_len = 1024

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('', port))
atexit.register(closing, sock)

while True:
    print('Waiting for connection')
    sock.listen()
    conn, addr = sock.accept()
    print(f'New connection {addr}')

    pid = os.fork()
    if(pid == 0):
        automat = automata()
        prev = -1
        # conn.settimeout(5.0)
        while True:
            data = conn.recv(message_len)
            if not data:
                print("Empty data")
                break
            for s in data:
                result = automat.step(s)
                if prev == 13 and s == 10:
                    print(f'result: {result}')
                    sent_bytes = conn.send(result)
                    print(f'sent {sent_bytes} bytes')
                prev = s
        time.sleep(2)
        conn.close()
        print('Connection closed in child')
        sock.close()
        print('Socket closed in child')
        os._exit(0)
    else:
        conn.close()
        print('Connection closed')
