
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def addTwoNumbers(l1, l2):
    nextLi1 = l1
    nextLi2 = l2
    solution = ''
    leftover = 0
    while (nextLi1 is not None):
        digitSum = nextLi1.val + nextLi2.val + leftover
        print('sum', digitSum)
        if digitSum > 9:
            solution = '0' + solution
            leftover = 1
        else:
            solution = str(digitSum) + solution
            leftover = 0
        print('soltuion', solution)
        nextLi1 = nextLi1.next
        nextLi2 = nextLi2.next
        
    reversedSolution = solution[::-1]
    listSolution = ListNode(int(reversedSolution[0]))
    
    head = listSolution
    for c in reversedSolution[1:]:
        listSolution.next = ListNode(int(c))
        listSolution = listSolution.next

    while (head is not None):
        print(head.val)
        head = head.next
    return head


l1 = ListNode(2)
l1.next = ListNode(4)
l1.next.next = ListNode(3)

l2 = ListNode(5)
l2.next = ListNode(6)
l2.next.next = ListNode(4)

print(addTwoNumbers(l1, l2))
