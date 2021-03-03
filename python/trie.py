class Trie:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.val = None
        self.left = None
        self.right = None

    def insert(self, word: str) -> None:
        """
        Inserts a word into the trie.
        """
        print(f'Processing word: {word}')
        if len(word) == 0:
            return

        if not self.val:
            print('Value doesnt exist', word)
            self.val = word[0]
            word = word[1:]

        if len(word) == 0:
            return

        if word[0] < self.val:
            print('Inserting leftward')
            if self.left is None:
                self.left = Trie()
            return self.left.insert(word)

        if word[0] >= self.val:
            print('Inserting rightward')
            if self.right is None:
                self.right = Trie()
            return self.right.insert(word)

        print('DONE')

    def serailize(self, root):
        return (
            'X'
            if root is None
            else f'{root.val},{self.serailize(root.left)},{self.serailize(root.right)}'
        )

    def search(self, word: str) -> bool:
        """
        Returns if the word is in the trie.
        """
        for c in word:

            word = word[1:]

        return False

    def startsWith(self, prefix: str) -> bool:
        """
        Returns if there is any word in the trie that starts with the given prefix.
        """

    def __str__(self):
        return f'{self.val}{self.left if self.left else ""}{self.right if self.right else ""}'


obj = Trie()
obj.insert('apple')
# print(obj.right.right.val)
print(obj.serailize(obj))
print(obj)

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)