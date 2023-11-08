import tools

class TreeNode:
    def __init__(self, val: int = 0, left=None, right=None):
        """ yessir """

        self.left = left
        self.right = right
        self.val = val


class Tree:
    def __init__(self, string):
        """ creates a tree from input string """
        self.root = self.parse(string)

    def traversal(self, mode):
        """ manager for traversal subfunctions """

        if mode < 4:
            self._dfs(mode, self.root)
        else:
            self._bfs()

    def _dfs(self, mode: int, node: TreeNode = None):
        """ depth-for-search tree traversal"""

        if not node:
            print("null", end=" ")
            return

        # MLR
        if mode == 1:
            print(node.val, end=" ")

        self._dfs(mode, node.left)

        #LMR
        if mode == 2:
            print(node.val, end=" ")

        self._dfs(mode, node.right)

        #RML
        if mode == 3:
            print(node.val, end=" ")

        return

    def _bfs(self):
        if not self.root:
            return

        q = []

        q.append(self.root)

        while len(q) != 0:
            cur_node = q.pop(0)

            if cur_node != "null":
                print(cur_node.val, end=" ")
            else:
                print("null", end=" ")
                continue

            if cur_node.left:
                q.append(cur_node.left)

            if cur_node.right:
                q.append(cur_node.right)

    def parse(self, tree_string):
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
        node.left = self.parse(subtr_arr[0])

        # Вторая подстрока (если есть) - правое поддерево
        if len(subtr_arr) == 2:
            node.right = self.parse(subtr_arr[1])

        return node





