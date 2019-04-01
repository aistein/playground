#!/usr/local/bin/python3

operands = ['(',')','~','^','v']

def is_operator(literal):
    if literal in operands:
        return True
    return False

def postfix_expr_of(infix_expr):
    stack = []
    postfix_expr = ''
    for literal in infix_expr:
        # Non-Operator Literals outputted first
        if not is_operator(literal):
            postfix_expr += literal
        else:
        # Stack was just emptied, or Unary Operators onto the Stack
            if len(stack) == 0 or stack[-1] == '(':
                stack.append(literal)
        # Cycle Stack to evaluate () pair
            elif literal == ')':
                while stack[-1] != '(':
                    if len(stack) == 1:
                        exit("error: invalid infix_expr - missing \'(\'")
                    postfix_expr += stack.pop()
                stack.pop()
        # Enforce Operator Priority when packing the stack
            elif operands.index(literal) < operands.index(stack[-1]):
                stack.append(literal)
        # Enforce Operator Priority when un-packing the stack
            else:
                while len(stack) > 0 and operands.index(literal) > operands.index(stack[-1]) and literal not in ['(',')']:
                    postfix_expr += stack.pop()
                stack.append(literal)

    # If there's any stack left after processing literals.. pop, pop
    while len(stack) > 0:
        postfix_expr += stack.pop()

    return postfix_expr

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description='translate an infix expression to a postfix expression.')
    parser.add_argument('infix_expr', metavar='expr', type=str)
    args = parser.parse_args()

    print(postfix_expr_of(args.infix_expr))

