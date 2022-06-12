class automata:
    def __init__(self):
        self.state = 'I'
        self.sum = 0
        self.number = 0
    
    def step(self, symbol):
        # print(f'initial state {self.state}')
        if self.state == 'I':
            if (symbol >= 48 and symbol <= 57):
                self.state = 'C'
                self.number = 10 * self.number + (symbol - 48)
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
            else:
                self.state = 'ERR'
                return b'ERROR\r\n'

        elif self.state == 'R':
            if symbol == 10:
                self.state = 'N'
                self.sum = self.sum + self.number
                return f'{self.sum}\r\n'.encode()
            else:
                self.state = 'ERR'
                return b'ERROR\r\n'
        
        elif self.state == 'ERR':
            self.state = 'ERR'
            return b'ERROR\r\n'

        # print(f'final state {self.state}')
        return -1