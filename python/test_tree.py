from .tree import TreeNode


# TODO: Create generator for trees
def tree_1():
    T = TreeNode(1)
    T.left = TreeNode(2)
    T.right = TreeNode(2)
    T.left.left = TreeNode(3)
    T.left.right = TreeNode(4)
    T.right.left = TreeNode(4)
    T.right.right = TreeNode(3)
    return T


def tree_2():
    TT = TreeNode(1)
    TT.left = TreeNode(2)
    TT.right = TreeNode(3)
    TT.left.left = TreeNode(4)
    TT.left.right = TreeNode(5)
    return TT


def test_is_same_tree():
    assert tree_1().is_same_tree(tree_2()) is False