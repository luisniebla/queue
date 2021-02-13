import queue


def treeMatch(root1, root2):
    if root1 is None and root2 is not None:
        return False
    elif root2 is None and root1 is not None:
        return False
    elif root2 is None and root1 is None:
        return True
    elif root1.val != root2.val:
        return False
    else:
        return treeMatch(root1.right, root2.left) and treeMatch(root1.left, root2.right)


class Position:
    def __init__(self, element):
        self.element = element

    def __eq__(self, other):
        # print(self.element, other)
        return getattr(other, 'element', other) == self.element


class TreeNode:
    def __init__(self, val):
        self.p = Position(val)
        self.left = None
        self.right = None

    def root(self):
        return self.p

    def is_root(self, p):
        return self.root() == p

    def parent(self, node):
        if node is None:
            return None

        if self.left is node or self.right is node:
            return self
        else:
            left = self.left.parent(node) if self.left else None
            right = self.right.parent(node) if self.right else None
            return left or right

    def parent_of_element(self, e):
        if self.is_root(e):
            return None
        else:
            left = getattr(self.left, 'p', False) == e
            right = getattr(self.right, 'p', False) == e
            # print('LR', left, right)
            if not left or not right:
                left = self.left.parent_of_element(e) if self.left else None
                right = self.right.parent_of_element(e) if self.right else None
            if left or right:
                return self

    def element_count(self, e):
        if self is None:
            return 0
        else:
            leftSum = self.left.element_count(e) if self.left else 0
            rightSum = self.right.element_count(e) if self.right else 0
            if self.root().element == e:
                # print('Adding...')
                return 1 + leftSum + rightSum
            else:
                # print('nada', self.root().element, e)
                return leftSum + rightSum

    def is_same_tree(self, otherTree):
        if not self.root and not otherTree:
            return True
        elif not self.root and otherTree or self.root and not otherTree:
            return False
        elif (
            self.root().element == otherTree.root().element
            and self.left.is_same_tree(otherTree.left)
            and self.right.is_same_tree(otherTree.right)
        ):
            return True
        else:
            return False


def height(root):
    if root is None:
        return 0

    return 1 + max(height(root.left), height(root.right))


def diameter(root):
    if not root:
        return 0
    # print(root.p.element)
    return (
        max(
            1 + height(root.left) + height(root.right),
            max(diameter(root.left), diameter(root.right)),
        )
        - 1  # This double-counts the leaves
    )


# def diameterOfBinaryTree(self, root):
# Here's the idea
# diameter_root = diameter(left_tree) + diameter(right_tree) + 1 (root node)
# diameter_non_root = max(diameter(left_tree), diameter(right_tree))
# diameter = max(diameter_root, diameter_non_root)


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

assert diameter(T) == 4


assert T.left == T.left
assert T.left != T.right

assert T.is_root(T.root()) is True

assert T.parent(T.left.left) == T.left
assert T.parent(T.right.right) == T.right
assert T.parent(T.left.right) == T.left
assert T.parent(T.right) == T

assert T.element_count(1) == 1
assert T.element_count(2) == 2
assert T.element_count(9) == 0

# print(T.parent_of_element(3))

#       1
#      / \
#     2   3
#    / \
#   4   5

TT = TreeNode(1)
TT.left = TreeNode(2)
TT.right = TreeNode(3)
TT.left.left = TreeNode(4)
TT.left.right = TreeNode(5)

assert diameter(TT) == 3
assert T.is_same_tree(TT) is False