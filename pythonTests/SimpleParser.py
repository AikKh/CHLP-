class Token:
    def __init__(self, token_type, value=None):
        self.token_type = token_type
        self.value = value

class Lexer:
    def __init__(self, input_string):
        self.input_string = input_string
        self.current_position = 0

    def get_next_token(self):
        while self.current_position < len(self.input_string):
            current_char = self.input_string[self.current_position]

            if current_char.isdigit():
                return Token('INTEGER', int(self.extract_integer()))

            if current_char == '+':
                self.current_position += 1
                return Token('PLUS', '+')
            elif current_char == '-':
                self.current_position += 1
                return Token('MINUS', '-')
            elif current_char == '*':
                self.current_position += 1
                return Token('MULT', '*')
            elif current_char == '/':
                self.current_position += 1
                return Token('DIV', '/')
            elif current_char == '(':
                self.current_position += 1
                return Token('LPAREN', '(')
            elif current_char == ')':
                self.current_position += 1
                return Token('RPAREN', ')')

            # Ignore whitespace
            elif current_char.isspace():
                self.current_position += 1
                continue

            else:
                raise Exception(f"Invalid character: {current_char}")

        return Token('EOF')

    def extract_integer(self):
        start_position = self.current_position
        while self.current_position < len(self.input_string) and self.input_string[self.current_position].isdigit():
            self.current_position += 1
        return self.input_string[start_position:self.current_position]

class Parser:
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = self.lexer.get_next_token()

    def eat(self, expected_token_type):
        if self.current_token.token_type == expected_token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            raise Exception(f"Unexpected token: {self.current_token.token_type}. Expected: {expected_token_type}")

    def factor(self):
        if self.current_token.token_type == 'INTEGER':
            value = self.current_token.value
            self.eat('INTEGER')
            return value
        elif self.current_token.token_type == 'LPAREN':
            self.eat('LPAREN')
            result = self.expr()
            self.eat('RPAREN')
            return result
        else:
            raise Exception(f"Unexpected token: {self.current_token.token_type}")

    def term(self):
        result = self.factor()
        while self.current_token.token_type in ('MULT', 'DIV'):
            if self.current_token.token_type == 'MULT':
                self.eat('MULT')
                result *= self.factor()
            elif self.current_token.token_type == 'DIV':
                self.eat('DIV')
                result /= self.factor()
        return result

    def expr(self):
        result = self.term()
        while self.current_token.token_type in ('PLUS', 'MINUS'):
            if self.current_token.token_type == 'PLUS':
                self.eat('PLUS')
                result += self.term()
            elif self.current_token.token_type == 'MINUS':
                self.eat('MINUS')
                result -= self.term()
        return result


def main():
    input_string = "4*2+3"
    lexer = Lexer(input_string)
    parser = Parser(lexer)
    result = parser.expr()
    print(f"Result: {result}")

if __name__ == "__main__":
    main()
