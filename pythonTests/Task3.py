import random

class Node:
    def __init__(self, value, children=None):
        self.value = value
        self.children = children if children else []

def print_ast(node: Node, level=0):
    if node is not None:
        print("  " * level + str(node.value))
        for child in node.children:
            print_ast(child, level + 1)

def match(tokens: list, c):
    if tokens[0] == c:
        return tokens.pop(0)
    raise Exception(f"Expected {c}")

def is_digit(value):
    return 0 <= (ord(value) - ord('0')) <= 9

def factor(tokens):
    if is_digit(tokens[0]):
        return Node(match(tokens, tokens[0]))
    
    elif tokens[0] == '(':
        match(tokens, '(')
        res = expr(tokens)
        match(tokens, ')')
        return res

def term(tokens):
    left = factor(tokens)

    while tokens and (tokens[0] in ['*', '/']):
        op = match(tokens, tokens[0])
        right = factor(tokens)
        left = Node(op, [left, right])
    
    return left

def expr(tokens):
    left = term(tokens) 

    while tokens and (tokens[0] in ['+', '-']):
        op = match(tokens, tokens[0])
        right = term(tokens)
        left = Node(op, [left, right])
    
    return left

tokens = list("4-3+3*4/(4-5)")
# expr_str = ''.join([str(random.randrange(1, 10)) + random.choice(['+', '-', '*', '/']) for i in range(1000)]) + '1'
# tokens = list(expr_str)


res = expr(tokens)
print(tokens)
print_ast(res)