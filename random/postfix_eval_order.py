#!/usr/local/bin/python3

import infix_to_postfix as pfx

"""
Take an infix expression, turn it into a postfix expression, and then
break the postfix into a list of instructions
"""

def eval_order(infix_expr):
    postfix_expr = pfx.postfix_expr_of(infix_expr)
    operations = []
    stack = []
    rcntr = 0
    for literal in postfix_expr:
        if not pfx.is_operator(literal):
            stack.append(literal)
        elif literal == '~':
            operations.append("R{}=~{}".format(rcntr, stack.pop()))
            stack.append("R{}".format(rcntr))
            rcntr += 1
        else: # 'v' '^'
            operands = [stack.pop(), stack.pop()]
            operations.append("R{}={}{}{}".format(rcntr, operands.pop(), literal, operands.pop()))
            stack.append("R{}".format(rcntr))
            rcntr += 1
    return operations

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(description='get operation order from infix expression.')
    parser.add_argument('infix_expr', metavar='expr', type=str)
    args = parser.parse_args()

    print(eval_order(args.infix_expr))

