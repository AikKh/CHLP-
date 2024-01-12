class Token:
    def __init__(self, token_type, value=None):
        self.token_type = token_type
        self.value = value

class Lexer:
    def __init__(self, input_string):
        self.input_string = input_string
        self.current_position = 0

    def get_next_token(self):
        if self.current_position < len(self.input_string):
            char = self.input_string[self.current_position]
            if char.isdigit():
                self.current_position += 1
                return Token('INTEGER', int(char))
            elif char == '+':
                self.current_position += 1
                return Token('PLUS', '+')
            elif char == '-':
                self.current_position += 1
                return Token('MINUS', '-')
            elif char == '*':
                self.current_position += 1
                return Token('MULT', '*')
            elif char == '/':
                self.current_position += 1
                return Token('DIV', '/')
            elif char == '(':
                self.current_position += 1
                return Token('LPAREN', '(')
            elif char == ')':
                self.current_position += 1
                return Token('RPAREN', ')')
            else:
                raise Exception(f"Unexpected character: {char}")
        else:
            # Return EOF token when end of input is reached
            return Token('EOF')

class Parser:
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = self.lexer.get_next_token()

        # Parse table for the grammar
        self.parse_table = {
            'expr': {'INTEGER': 'term expr_prime', 'LPAREN': 'term expr_prime'},
            'expr_prime': {'PLUS': '+ term expr_prime', 'MINUS': '- term expr_prime', 'RPAREN': '', 'EOF': ''},
            'term': {'INTEGER': 'factor term_prime', 'LPAREN': 'factor term_prime'},
            'term_prime': {'MULT': '* factor term_prime', 'DIV': '/ factor term_prime', 'PLUS': '', 'MINUS': '', 'RPAREN': '', 'EOF': ''},
            'factor': {'INTEGER': 'INTEGER', 'LPAREN': '( expr )'}
        }


    def match(self, expected_token_type):
        if self.current_token.token_type == expected_token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            raise Exception(f"Unexpected token: {self.current_token.token_type}. Expected: {expected_token_type}")

    def parse_non_terminal(self, non_terminal):
        production = self.parse_table[non_terminal][self.current_token.token_type]
        for symbol in production.split():
            if symbol.isupper():
                self.parse_non_terminal(symbol)
            else:
                self.match(symbol)

    def parse(self):
        # Start parsing from the 'expr' non-terminal
        self.parse_non_terminal('expr')

def main():
    input_string = "3 + (4 * 5) - 6"
    lexer = Lexer(input_string)
    parser = Parser(lexer)
    parser.parse()
    print("Parsing successful.")

if __name__ == "__main__":
    main()
