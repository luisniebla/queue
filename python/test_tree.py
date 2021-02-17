from .tree import TreeNode, build_tree


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


def test_build_tree():
    T = build_tree([3, 9, 20, 15, 7], [9, 3, 15, 20, 7])
    TT = TreeNode(3)
    TT.left = TreeNode(9)
    TT.right = TreeNode(20)
    TT.right.left = TreeNode(15)
    TT.right.right = TreeNode(7)

    assert str(T) == str(TT)
