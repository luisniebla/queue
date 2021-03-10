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


def inBounds(board, i, j):
    return i >= 0 and j >= 0 and i < len(board) and j < len(board[0])


def findWord(board, visited, i, j, word, ind, mustExist):
    if len(word) <= ind:
        return False

    if not inBounds(board, i, j) or visited.get(f'{i}{j}'):
        # print('visited', visited)
        print('OUT OF BOUNDS', i, j)
        return False

    print('Testing', i, j, board[i][j], word)
    visited[f'{i}{j}'] = True
    if board[i][j] == word[ind]:
        print('FOUND', word[ind])
        if len(word) == ind + 1:
            print('RETURNING TRUE', board[i][j], word)
            return True
        return (
            findWord(board, visited, i + 1, j, word, ind + 1, True)
            or findWord(board, visited, i - 1, j, word, ind + 1, True)
            or findWord(board, visited, i, j + 1, word, ind + 1, True)
            or findWord(board, visited, i, j - 1, word, ind + 1, True)
        )
    elif mustExist and board[i][j] != word[ind]:
        print('FALSE')
        return False
    else:
        print("NOT FOUND")
        return (
            findWord(board, visited, i + 1, j, word, 0, False)
            or findWord(board, visited, i - 1, j, word, 0, False)
            or findWord(board, visited, i, j + 1, word, 0, False)
            or findWord(board, visited, i, j - 1, word, 0, False)
        )


def findWords(board, words):
    found = []
    for word in words:
        print('Testing ', word)
        if findWord(board, {}, 0, 0, word, 0, False) or findWord(
            board, {}, 1, 0, word, 0, False
        ):
            found.append(word)
    return found


assert (
    findWords(
        [
            ["o", "a", "a", "n"],
            ["e", "t", "a", "e"],
            ["i", "h", "k", "r"],
            ["i", "f", "l", "v"],
        ],
        ["oath", "pea", "eat", "rain"],
    )
    == ['oath', 'eat']
)

assert findWords([["a", "a"]], ["aa"]) == ['aa']

print(findWords([['a', 'a']], ['aaa']))
# print(
#     findWords(
#         [
#             ["o", "a", "b", "n"],
#             ["o", "t", "a", "e"],
#             ["a", "h", "k", "r"],
#             ["a", "f", "l", "v"],
#         ],
#         ["oa", "oaa"],
#     )
# )


# obj = Trie()
# obj.insert('apple')
# # print(obj.right.right.val)
# print(obj.serailize(obj))
# print(obj)

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)


# class Solution:
#     def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
#         WORD_KEY = '$'

#         trie = {}
#         for word in words:
#             node = trie
#             for letter in word:
#                 # retrieve the next node; If not found, create a empty node.
#                 node = node.setdefault(letter, {})
#             # mark the existence of a word in trie node
#             node[WORD_KEY] = word

#         rowNum = len(board)
#         colNum = len(board[0])

#         matchedWords = []

#         def backtracking(row, col, parent):

#             letter = board[row][col]
#             currNode = parent[letter]

#             # check if we find a match of word
#             word_match = currNode.pop(WORD_KEY, False)
#             if word_match:
#                 # also we removed the matched word to avoid duplicates,
#                 #   as well as avoiding using set() for results.
#                 matchedWords.append(word_match)

#             # Before the EXPLORATION, mark the cell as visited
#             board[row][col] = '#'

#             # Explore the neighbors in 4 directions, i.e. up, right, down, left
#             for (rowOffset, colOffset) in [(-1, 0), (0, 1), (1, 0), (0, -1)]:
#                 newRow, newCol = row + rowOffset, col + colOffset
#                 if newRow < 0 or newRow >= rowNum or newCol < 0 or newCol >= colNum:
#                     continue
#                 if not board[newRow][newCol] in currNode:
#                     continue
#                 backtracking(newRow, newCol, currNode)

#             # End of EXPLORATION, we restore the cell
#             board[row][col] = letter

#             # Optimization: incrementally remove the matched leaf node in Trie.
#             if not currNode:
#                 parent.pop(letter)

#         for row in range(rowNum):
#             for col in range(colNum):
#                 # starting from each of the cells
#                 if board[row][col] in trie:
#                     backtracking(row, col, trie)

#         return matchedWords
