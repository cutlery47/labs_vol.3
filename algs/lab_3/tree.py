import tools

class TreeNode:
    def __init__(self, val: int = 0, left=None, right=None):
        """ yessir """

        self.left = left
        self.right = right
        self.val = val

class AVLTreeNode(TreeNode):
    def __init__(self, val:  int = 0, height: int = 0, left=None, right=None):
        """ basically the same class besides that height attribute was added """

        super(AVLTreeNode, self).__init__(val, left, right)
        self.height = height


class Tree:
    def __init__(self, string):
        """ creates a tree from input string """

        self.root = parse(string)

    def traversal(self, mode):
        """ manager for traversal subfunctions """

        self.__dfs(mode, self.root)

    def __dfs(self, mode: int, node: TreeNode = None):
        """ depth-for-search tree traversal"""

        if not node:
            print("null")
            return

        # MLR
        if mode == 1:
            print(node.val)

        self.__dfs(mode, node.left)

        #LMR
        if mode == 2:
            print(node.val)

        self.__dfs(mode, node.right)

        #RML
        if mode == 3:
            print(node.val)

        return

class AVLTree(Tree):
    def __init__(self, string):
        # Array for storing elements of the binary tree given as input
        self.values = []

        # Value for storing tree height -_-
        self.tree_height = 0

        # Using default tree constructor to create a non-search binary tree
        super(AVLTree, self).__init__(string)

        # Collecting elements and sorting
        self.__buildAVL(self.root)
        self.values.sort()

        # Calculating AVL tree height
        self.getAVLHeight(self.root, 0)

        # Building a binary search tree
        self.root = self.binaryToAVL(self.values, 0)

    def __buildAVL(self, node: TreeNode = None):
        """ parsing the binary tree from input string --- collecting all the values """

        if not node:
            return

        self.values.append(node.val)
        self.__buildAVL(node.left)
        self.__buildAVL(node.right)
        return

    def getAVLHeight(self, node, height):
        """ going down the tree to calculate its depth """

        if not node:
            self.tree_height = max(self.tree_height, height)
            return

        self.getAVLHeight(node.left, height + 1)
        self.getAVLHeight(node.right, height + 1)

        return

    def binaryToAVL(self, nums, height):
        """ converting input binary tree values to an avl tree """

        if len(nums) == 0:
            return

        ind = (len(nums) - 1) // 2
        node = AVLTreeNode(nums[ind], self.tree_height - height)

        node.left = self.binaryToAVL(nums[:ind], height + 1)
        node.right = self.binaryToAVL(nums[ind + 1:], height + 1)

        return node

    def find(self, value):
        node = self.root

        while node and value != node.val:
            if node.val > value:
                node = node.left
            else:
                node = node.right

        return node

    def insert(self, value):
        pass

    def delete(self, value):
        pass

def parse(tree_string):
    """ Преобразование строки в бинарное дерево """

    # Ищем центральный элемент дерева (первый в строке)
    top = tools.findTopElement(tree_string)

    if top:
        node = TreeNode(top)
    else:
        return None

    # Отбрасываем внешние скобки и этот элемент
    tree_string = tree_string[2:-1]

    # Суть заключается в том, что мы разбиваем исходную строку на подстроки такого же вида, как исходная строка
    # Таким образом, если представить исходную строку, как бинарное дерево - все меньшие подстроки будут поддеревьями

    # Разбиваем строку на подстроки
    subtr_arr = tools.findSubtrees(tree_string)

    # Если подстрок нет - возвращаем ноду
    if len(subtr_arr) == 0:
        return node

    # Первая подстрока - левое поддерево
    node.left = parse(subtr_arr[0])

    # Вторая подстрока (если есть) - правое поддерево
    if len(subtr_arr) == 2:
        node.right = parse(subtr_arr[1])

    return node


input_str = "(8(9(5(2)))(1(5)(9)))"
tools.inputCheck(input_str)

smth = AVLTree(input_str)
print(smth.find(8))

