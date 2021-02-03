class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def allValuesMatchSubtree(s, t):
    if s is None and t is None:
        return True
    if s and t and s.val == t.val:
        return allValuesMatchSubtree(s.left, t.left) and allValuesMatchSubtree(s.right, t.right)
    else:
        return False

def isSubtree( s: TreeNode, t: TreeNode) -> bool:
    # [3, 4, 5, 1, 2, null, null, 0]
    if s is None:
        return False

    if allValuesMatchSubtree(s, t):
        return True
    else:
        return isSubtree(s.left, t) or isSubtree(s.right, t)

s = TreeNode(3)
s.left = TreeNode(4)
s.left.left = TreeNode(1)
s.left.right = TreeNode(2)
# s.left.left.left = TreeNode(0)
s.right = TreeNode(5)

t = TreeNode(4)
t.left = TreeNode(1)
t.right = TreeNode(2)

print(isSubtree(s, t))