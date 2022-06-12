class automata:
    def __init__(self):
        self.state = 'I'
        self.sum = 0
        self.number = 0
    
    def step(self, symbol):
        # print(f'initial state {self.state}')
        if self.state == 'I':
            self.reset()
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
                self.state = 'I'
                self.sum = self.sum + self.number
                return self.sum
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

automat = automata()
zapytanie = b'5 10  5 8\r\n2 2\r\n13 7 5\r\n\r\n'
for s in zapytanie:
    wynik = automat.step(s)
    print(wynik)
