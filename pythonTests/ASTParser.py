class Token:
    def __init__(self, token_type, value=None):
        self.token_type = token_type
        self.value = value

class Node:
    def __init__(self, left = None, value = None, right = None):
        self.left = left
        self.right = right
        self.value = value

    def to_str(self):
        if type(self.value) == int:
            return str(self.value)
        
        return self.to_str() + f" {self.value} " + self.right.to_str()

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
        self.ast = Node()
        self.currNode = self.ast

        self.lexer = lexer
        self.current_token = self.lexer.get_next_token()

    def match(self, expected_token_type):
        if self.current_token.token_type == expected_token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            raise Exception(f"Unexpected token: {self.current_token.token_type}. Expected: {expected_token_type}")

    def factor(self):
        pass

    def term(self):
        pass

    def expr(self):
        self.term()

            
def print_ast(node, indent=0):
    print(' ' * indent + "Node:", end=' ')
    
    # Check if the node is an instance of ASTNode
    if isinstance(node, Node):
        if node.value is not None:
            print(node.value)
        else:
            print()

        if node.left is not None:
            print(' ' * (indent + 2) + "Left:")
            print_ast(node.left, indent + 4)

        if node.right is not None:
            print(' ' * (indent + 2) + "Right:")
            print_ast(node.right, indent + 4)
    else:
        print(node)

def main():
    # ast = Node(Node(2, '+', 3), "*", 5)
    # print_ast(ast)

    input_string = "5 * (7 - 2)"
    lexer = Lexer(input_string)
    parser = Parser(lexer)
    parser.expr()
    parser.ast = parser.ast.left
    print_ast(parser.ast)

if __name__ == "__main__":
    main()
