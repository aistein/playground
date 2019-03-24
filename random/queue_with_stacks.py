#!/usr/local/bin/python3

class Queue:

    def __init__(self, queue_type):
        self.qtype = queue_type
        self.fwd = []
        self.rev = []

    def __reverse__(self):
        for _ in range(len(self.fwd)):
            self.rev.append(self.fwd.pop())

    def pop_front(self):
        if len(self.rev) > 0:
            return self.rev.pop()
        if len(self.fwd) == 1:
            return self.fwd.pop()
        if len(self.fwd) > 1:
            self.__reverse__()
            return self.rev.pop()
        return self.qtype(None)

    def push_back(self, item):
        self.fwd.append(item)

    def front(self):
        if len(self.rev) > 0:
            return self.rev[-1]
        if len(self.fwd) == 1:
            return self.fwd[-1]
        if len(self.fwd) > 1:
            self.__reverse__()
            return self.rev[-1]
        return self.qtype(None)

q = Queue(int)
q.push_back(0)
q.push_back(1)
q.push_back(2)
print(q.front())
q.push_back(3)
q.push_back(4)
[print(q.pop_front()) for _ in range(5)]
