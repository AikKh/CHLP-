# Grammar:
# E = iE'
# E' = +iE' I e

def E_prime(tokens):
    if tokens and tokens[0] == '+':
        tokens.pop(0)
        if tokens and tokens[0] == 'i':
            tokens.pop(0)
        else: raise SyntaxError
        
        return E_prime(tokens)
    elif not tokens:
        return
        
    raise SyntaxError("ss")

def E(tokens):
    if tokens:
        if tokens[0] == 'i':
            tokens.pop(0)
            E_prime(tokens)
        else: raise SyntaxError

input = "i+i+i+i+i+i+i+i+i+i+i"
tokens = list(input)
E(tokens)
print(tokens)