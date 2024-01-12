# S -> cAd
# A -> a b I a

def match(tokens: list, c):
    if tokens[0] == c:
        tokens.pop(0)
        return
    raise Exception(f"Expected {c}")

def A(tokens: list):
    match(tokens, 'a')
    if tokens[0] == 'b':
        match(tokens, 'b')

def S(tokens: list):
    match(tokens, 'c')
    A(tokens)
    match(tokens, 'd')

tokens = list("cad")
S(tokens)
print(tokens)
