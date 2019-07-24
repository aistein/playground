#! /usr/local/bin/python3 -u

class ListNode:
    def __init__(self, val=0, nxt=None):
        self.val = val
        self.next = nxt

def addTwoNumbers(l1, l2):
    if not l1:
        return l2
    if not l2:
        return l1

    # addition results will be stored in list l1
    head = curr = l1
    carry = 0

    # add overlapping digits
    while l1.next and l2.next:
        print("BEFORE: curr, l1, l2 = {}, {}, {}".format(curr.val, l1.val, l2.val))
        curr.val, carry, curr, l1, l2 = (l1.val + l2.val + carry) % 10,\
                                        (l1.val + l2.val + carry) // 10,\
                                        curr.next, l1.next, l2.next
    curr.val, carry, l1, l2 = (l1.val + l2.val + carry) % 10,\
                              (l1.val + l2.val + carry) // 10,\
                              l1.next, l2.next

    # if there are more digits in either list, complete the addition on that list
    if l1 or l2:
        curr.next = l2 if l2 else l1
        curr = curr.next
        while curr.next:
            print("BEFORE: curr, rl = {}, {}".format(curr.val, rl.val))
            curr.val, carry, curr = (curr.val + carry) % 10,\
                                    (curr.val + carry) // 10,\
                                    curr.next
        curr.val, carry = (curr.val + carry) % 10,\
                          (curr.val + carry) // 10,\

    # if the carry is 1, we need to create a new digit at the end
    print(curr)
    if carry == 1:
        curr.next = ListNode(1, None)

    return head

if __name__ == '__main__':
    l1 = ListNode(0, ListNode(7, None))
    l2 = ListNode(8, ListNode(4, None))
    result = addTwoNumbers(l1, l2)
    while result:
        print(result.val)
        result = result.next

