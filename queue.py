# Create the object type 'queue'
class Queue:
    def __init__(self, n):
        self.Q = [0] * n
        self.tail = 0
        self.head = 0
        self.length = n

    def enqueue(self, x):
        self.Q[self.tail] = x
        if self.tail == self.length:
            self.tail = 0
        else:
            self.tail += 1

    def dequeue(self):
        x = self.Q[self.head]
        self.Q[self.head] = 0
        if self.head == self.length:
            self.head = 0
        else:
            self.head += 1
        return x

    # TODO: Remove extra 0s
    def __str__(self):
        return print(self.Q)

# Move to seperate file if this gets too big
def test_queue():
    q = Queue(3)
    
    assert q.Q == [0,0,0]
    q.enqueue(1)
    q.enqueue(2)
    assert q.Q == [1, 2, 0]
    q.dequeue()
    assert q.Q == [0, 2, 0]
    q.enqueue(3)
    assert q.Q == [0, 2, 3]
        
if __name__ == '__main__':
    test_queue()
