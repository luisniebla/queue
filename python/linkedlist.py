class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        temp = self
        s = ""
        while temp:
            s += str(temp.val) + '->'
            temp = temp.next
        return s

class LinkedList:
    def __init__(self, items):
        self.head = ListNode(items[0])
        curr = self.head
        for item in items[1:]:
            curr.next = ListNode(item)
            curr = curr.next
        self.next = self.head
        self.val = self.next.val 
        print(self.head)
        

L = LinkedList([1,2,3])

def reverseList(head: ListNode) -> ListNode:
    prev = None
    temp = head
    while temp:
        temp2 = temp.next
        temp.next = prev
        prev = temp
        temp = temp2
    return prev

def revere_list_recursive(head: ListNode):
    if (head == None or head.next == None):
        return head
    reversedHead = revere_list_recursive(head.next)
    head.next.next = head
    head.next = None
    return reversedHead


def has_cycle(head: ListNode):
    pos = head
    while (pos != None):
        temp = pos.next
        startingPoint = pos.next
        while (temp is not None and temp != pos):
            print('yo', startingPoint.val, temp.val)
            if temp.val == pos.val:
                return True
            else:
                temp = temp.next
                if (startingPoint == temp):
                    return True
        pos = pos.next
    return False

def remove(head, n):
    items = []
    while (head):
        items.append(head)
        head = head.next
    print()
    if n == 1 and len(items) == 1:
        items[0] = None
    elif n == 1:
        items[-n-1].next = None
    elif len(items) == n:
        return items[1]
    else:
        items[-n-1].next = items[-n+1]
    return items[0]

def reorderList(head: ListNode) -> None:
    """
    Do not return anything, modify head in-place instead.
    """
    print('Reordering', head)
    items = []
    while head:
        items.append(head)
        head = head.next
    if len(items) == 2:
        return items[0]
    if len(items) > 1:
        items[0].next = items[-1]
        items[-2].next = None
        if (items[0].next):
            items[0].next.next = reorderList(items[1])
    return items[0]
        

A = ListNode(1)
A.next = ListNode(2)
A.next.next = ListNode(3)
A.next.next.next = ListNode(4)
for i in range(100):

# A.next.next.next.next = ListNode(5)
print(reorderList(A))
print(A)
# print(has_cycle(A))
# print(L)
# rovo = reverseList(L)
# print(rovo)
