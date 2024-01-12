class Node:
    def __init__(self, value, children=None):
        self.value = value
        self.children = children if children else []

def parse_S(tokens):
    if tokens and tokens[0] == '+':
        tokens.pop(0)  # Consume '+'
        left_child = parse_S(tokens)
        right_child = parse_S(tokens)
        return Node('+', [left_child, right_child])
    
    elif tokens and tokens[0] == '-':
        tokens.pop(0)  # Consume '-'
        left_child = parse_S(tokens)
        right_child = parse_S(tokens)
        return Node('-', [left_child, right_child])
    
    elif tokens and tokens[0] == 'a':
        token = tokens.pop(0)  # Consume 'a'
        return Node(token)
    
    else:
        raise SyntaxError("Invalid expression")

def print_ast(node, level=0):
    if node is not None:
        print("  " * level + str(node.value))
        for child in node.children:
            print_ast(child, level + 1)

