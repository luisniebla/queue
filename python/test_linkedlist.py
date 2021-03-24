from .linkedlist import revere_list_recursive, LinkedList

def test_revere_list_recursive():
    assert str(revere_list_recursive(LinkedList([1,2,3]).head)) == str(LinkedList([3,2,1]).head)