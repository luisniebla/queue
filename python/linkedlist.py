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



print(L)
rovo = reverseList(L)
print(rovo)