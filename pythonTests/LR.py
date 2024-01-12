class LRParser:
    def __init__(self):
        self.stack = []
        self.input_buffer = []
        self.action = [
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1, '$': 2},
            {'$': 0},
            {'+': -1, '-': -1, '*': 5, '/': 6, ')': -1},
            {'+': -3, '-': -3, '*': -3, '/': -3, ')': -3, '$': -3},
            {'+': -4, '-': -4, '*': -4, '/': -4, ')': -4, '$': -4},
            {'+': -5, '-': -5, '*': -5, '/': -5, ')': -5, '$': -5},
            {'(': 3, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
            {'+': 3, '-': 4, '*': 5, '/': 6, '(': 7, 'num': 1},
        ]
        self.goto = [
            {'E': 1, 'T': 2, 'F': 3},
            {},
            {},
            {},
            {},
            {},
            {},
            {'E': 8, 'T': 9, 'F': 10},
            {'T': 9, 'F': 10},
            {'T': 11, 'F': 10},
            {'T': 12, 'F': 10},
            {'T': 13, 'F': 10},
            {'T': 14, 'F': 10},
            {},
            {},
            {},
            {},
            {},
            {},
        ]

    def parse(self, tokens):
        self.input_buffer = tokens + [('$', 'EOF')]
        self.stack = [0]

        while True:
            current_state = self.stack[-1]
            current_symbol, symbol_type = self.input_buffer[0] if self.input_buffer else ('$', 'EOF')

            if current_symbol == '$' and current_state == 0:
                print("Parsing completed successfully.")
                break

            if symbol_type in self.action[current_state]:
                action_value = self.action[current_state][symbol_type]
                if action_value > 0:
                    # Shift
                    self.stack.append(current_symbol)
                    self.stack.append(action_value)
                    self.input_buffer.pop(0)
                elif action_value < 0:
                    # Reduce
                    production_number = -action_value
                    production_length = len(self.get_production(production_number).split())
                    for _ in range(2 * production_length):
                        self.stack.pop()
                    non_terminal = self.get_production(production_number).split()[0]
                    new_state = self.goto[self.stack[-1]][non_terminal]
                    self.stack.append(non_terminal)
                    self.stack.append(new_state)
                else:
                    print("Error: Invalid action value.")
                    break
            else:
                print(f"Error: Invalid symbol '{current_symbol}'.")
                break

    def get_production(self, production_number):
        productions = [
            None,
            'E -> E + T',
            'E -> E - T',
            'E -> T',
            'T -> T * F',
            'T -> T / F',
            'T -> F',
            'F -> ( E )',
            'F -> num'
        ]
        return productions[production_number]

# Example usage:
parser = LRParser()
tokens = [
    ('(', 'LPAREN'), ('5', 'NUM'), ('+', 'PLUS'), ('6', 'NUM'), (')', 'RPAREN'),
    ('*', 'MULT'), ('6', 'NUM'), ('/', 'DIV'), ('(', 'LPAREN'), ('4', 'NUM'), ('-', 'MINUS'), ('2', 'NUM'), (')', 'RPAREN'),
    ('$', 'EOF')
]
parser.parse(tokens)
