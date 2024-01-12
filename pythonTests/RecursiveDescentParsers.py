# a) Grammar: S -> + S S | - S S | a
def parse_S(tokens):
    if tokens[0] == '+':
        tokens.pop(0)  # Consume '+'
        parse_S(tokens)
        parse_S(tokens)
    elif tokens[0] == '-':
        tokens.pop(0)  # Consume '-'
        parse_S(tokens)
        parse_S(tokens)
    elif tokens[0] == 'a':
        tokens.pop(0)  # Consume 'a'
    else:
        raise SyntaxError("Invalid expression")

# b) Grammar: S -> S ( S ) S | None
def parse_S(tokens):
    if tokens and tokens[0] == '(':
        tokens.pop(0)  # Consume '('
        parse_S(tokens)
        if tokens and tokens[0] == ')':
            tokens.pop(0)  # Consume ')'
            parse_S(tokens)
        else:
            raise SyntaxError("Missing closing parenthesis")
    # No production for 'None', as it means the end of the recursion


