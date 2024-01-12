class Token:
    def __init__(self, token_type, value=None):
        self.token_type = token_type
        self.value = value

class Lexer:
    def __init__(self, input_string):
        self.input_string = input_string
        self.current_position = 0
        self.current_char = self.input_string[self.current_position]

    def advance(self):
        self.current_position += 1
        if self.current_position < len(self.input_string):
            self.current_char = self.input_string[self.current_position]
        else:
            self.current_char = None

    def get_next_token(self):
        while self.current_char is not None:
            if self.current_char.isspace():
                self.advance()
            elif self.current_char.isdigit():
                return Token('INTEGER', self.integer())
            elif self.current_char == '+':
                self.advance()
                return Token('PLUS')
            elif self.current_char == '-':
                self.advance()
                return Token('MINUS')
            elif self.current_char == '*':
                self.advance()
                return Token('MULT')
            elif self.current_char == '/':
                self.advance()
                return Token('DIV')
            elif self.current_char == '(':
                self.advance()
                return Token('LPAREN')
            elif self.current_char == ')':
                self.advance()
                return Token('RPAREN')
            else:
                raise Exception(f"Invalid character: {self.current_char}")

    def integer(self):
        result = ''
        while self.current_char is not None and self.current_char.isdigit():
            result += self.current_char
            self.advance()
        return int(result)


class LL1Parser:
    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = self.lexer.get_next_token()

    def match(self, expected_token_type):
        if self.current_token is not None and self.current_token.token_type == expected_token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            raise Exception(f"Unexpected token: {self.current_token.token_type}. Expected: {expected_token_type}")

    def expr(self):
        if self.current_token is not None:
            return self.term_tail(self.term(self.factor()))
        else:
            raise Exception("Unexpected end of input")

    def term_tail(self, result):
        if self.current_token is not None and self.current_token.token_type in ('PLUS', 'MINUS'):
            op = self.current_token.token_type
            self.match(op)
            term_result = self.term(self.factor())
            if op == 'PLUS':
                return self.term_tail(result + term_result)
            elif op == 'MINUS':
                return self.term_tail(result - term_result)
        else:
            return result

    def term(self, result):
        if self.current_token is not None and self.current_token.token_type in ('MULT', 'DIV'):
            op = self.current_token.token_type
            self.match(op)
            factor_result = self.factor()
            if op == 'MULT':
                return self.term(result * factor_result)
            elif op == 'DIV':
                return self.term(result / factor_result)
        else:
            return result

    def factor(self):
        if self.current_token is not None:
            if self.current_token.token_type == 'INTEGER':
                result = self.current_token.value
                self.match('INTEGER')
                return result
            elif self.current_token.token_type == 'LPAREN':
                self.match('LPAREN')
                result = self.expr()
                self.match('RPAREN')
                return result
            elif self.current_token.token_type in ('PLUS', 'MINUS'):
                op = self.current_token.token_type
                self.match(op)
                return self.apply_unary_op(op, self.factor())
            else:
                raise Exception(f"Unexpected token: {self.current_token.token_type}")
        else:
            raise Exception("Unexpected end of input")

    def apply_unary_op(self, op, value):
        if op == 'PLUS':
            return value
        elif op == 'MINUS':
            return -value

def main():
    input_string = "3 + (4 * 5) - 6"
    lexer = Lexer(input_string)
    parser = LL1Parser(lexer)
    result = parser.expr()
    print(f"Result: {result}")

if __name__ == "__main__":
    main()
