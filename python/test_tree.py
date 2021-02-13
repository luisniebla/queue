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


def test_lowest_common_ancestor():
    T = tree_2()
    assert T.lowest_common_ancestor(T.left, T.right) == 1
    assert T.lowest_common_ancestor(T.left.left, T.left.right) == 2
    assert T.lowest_common_ancestor(T, T.right) == 1

    T = TreeNode(3)
    T.left = TreeNode(5)
    T.right = TreeNode(1)
    T.left.left = TreeNode(6)
    T.left.right = TreeNode(2)
    T.left.right.left = TreeNode(7)
    T.left.right.right = TreeNode(4)
    T.right.left = TreeNode(0)
    T.right.right = TreeNode(8)

    assert T.lowest_common_ancestor(T.left, T.right) == 3
    assert T.lowest_common_ancestor(T.left, T.left.right.right) == 5
