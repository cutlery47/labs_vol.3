class TreeNode:
    def __init__(self, val: int = 0, left=None, right=None):
        self.left = left
        self.right = right
        self.val = val


class Tree:

    def __init__(self, string):
        self.root = treeTransform(string)

    def dfs(self):
        self.__traversal(self.root)

    def __traversal(self, node: TreeNode = None):
        if not node:
            return

        print(node.val)
        self.__traversal(node.left)
        self.__traversal(node.right)

        return

def inputCheck(tree_string):
    if tree_string.count("(") != tree_string.count(")"):
        raise Exception("Input String Error: Parentheses sequence is not valid")


def treeTransform(tree_string):

    """ Преобразование строки в бинарное дерево """

    # Ищем центральный элемент ноды
    top = findTopElement(tree_string)

    if top:
        node = TreeNode(top)
    else:
        return None

    # Отбрасываем внешние скобки и этот элемент
    tree_string = tree_string[2:-1]

    # Суть заключается в том, что мы разбиваем исходную строку на подстроки такого же вида, как исходная строка
    # Таким образом, если представить исходную строку, как бинарное дерево - все меньшие подстроки будут поддеревьями

    # Разбиваем строку на подстроки
    subtr_arr = findSubtrees(tree_string)

    # Если подстрок нет - возвращаем ноду
    if len(subtr_arr) == 0:
        return node

    # Первая подстрока - левое поддерево
    node.left = treeTransform(subtr_arr[0])

    # Вторая подстрока (если есть) - правое поддерево
    if len(subtr_arr) == 2:
        node.right = treeTransform(subtr_arr[1])

    return node

def findSubtrees(tree_string):
    res = []
    stack = 0
    new_str = ""

    for el in tree_string:
        if el == "(":
            stack += 1
        elif el == ")":
            stack -= 1

        new_str += el

        if stack == 0:
            res.append(new_str)

            if len(res) > 2:
                raise Exception("Input String Error: Some node has more than 2 children")

            new_str = ""

    return res

def findTopElement(tree_string):
    # Берем первый попавшийся после скобки элемент в строке
    # Это будет центральная нода

    if tree_string[1] == ")":
        return None
    else:
        return int(tree_string[1])

input_str = "(2(4(5(6(7(8))))))"

inputCheck(input_str)
smth = Tree(input_str)
smth.dfs()
