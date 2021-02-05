import queue


def treeMatch(root1, root2):
    if (root1 is None and root2 is not None):
        return False
    elif (root2 is None and root1 is not None):
        return False
    elif (root2 is None and root1 is None):
        return True
    elif root1.val != root2.val:
        return False
    else:
        return treeMatch(root1.right, root2.left) and treeMatch(root1.left, root2.right)

class Position:
    def __init__(self, element):
        self.element = element

    def __eq__(self, other):
        print(self.element, other)
        return other.element == self.element

class TreeNode:
    def __init__(self, val):
        self.p = Position(val)
        self.left = None
        self.right = None

    def root(self):
        return self.p

    def is_root(self, p):
        return self.root() == p

    def parent(self, p):
        print(p)
        if (self.left and self.left.root() is p):
            return self.root()
        if (self.right and self.right.root() is p):
            return self.root()
        if (self.left and self.right):
            return self.left.parent(p) or self.right.parent(p)
        if (self.left):
            return self.left.parent(p)
        if (self.right):
            return self.right.parent(p)
        # if (self.left == p or self.right == p):
        #     return self.p
        # elif self.right 
        #     return self.left.parent(p) or self.right.parent(p)

    def printNode(self, node):
        if (node):
            return f' {node.val} {self.printNode(node.left)} {self.printNode(node.right)}'
        return ''

    def __str__(self):
        return self.printNode(self)



#      1
#    /   \
#   2     2
#  / \   / \
# 3   4 4   3

T = TreeNode(1)
T.left = TreeNode(2)
T.right = TreeNode(2)
T.left.left = TreeNode(3)
T.left.right = TreeNode(4)
T.right.left = TreeNode(4)
T.right.right = TreeNode(3)

assert T.left == T.left
assert T.left != T.right
assert T.is_root(T.root()) is True
assert T.parent(T.left.left.p) == Position(2)
assert T.parent(T.right.right.p) == Position(2)
assert T.parent(T.left.right.p) == Position(2)
assert T.parent(T.right.p) == Position(1)