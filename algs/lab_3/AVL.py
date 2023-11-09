from tree import TreeNode
from tree import Tree
import tools


class AVLTreeNode(TreeNode):
    def __init__(self, val: int = 0, height: int = 0, left=None, right=None):
        """ basically the same class besides that height attribute was added """

        super(AVLTreeNode, self).__init__(val, left, right)
        self.height = height


class AVLTree(Tree):
    def __init__(self, string):
        # Creating a binary from given data
        super().__init__(string)

        # Sorting tree values to convert BST to AVL BST
        self.values.sort()

        # Converting initial tree to AVL
        self.root = self.binaryToAVL(self.values, None)

        self.__adjustNodesHeight(self.root, 1)

    def __adjustNodesHeight(self, node, height):
        if not node:
            return

        node.height = self.tree_height - height + 1
        self.__adjustNodesHeight(node.left, height + 1)
        self.__adjustNodesHeight(node.right, height + 1)

    def binaryToAVL(self, nums, parent):
        """ converting input binary tree values to an avl tree """

        if len(nums) == 0:
            return

        ind = (len(nums) - 1) // 2
        node = AVLTreeNode(nums[ind])

        node.left = self.binaryToAVL(nums[:ind], node)
        node.right = self.binaryToAVL(nums[ind + 1:], node)

        return node

    def traversal(self, mode):
        """ manager for traversal subfunctions """

        if mode < 4:
            self._dfs(mode, self.root)
        else:
            self._bfs()

    def leftRotate(self, peak):
        new_peak = peak.right
        l_subroot = new_peak.left

        new_peak.left = peak
        peak.right = l_subroot

        peak.height = 1 + max(tools.getHeight(peak.left), tools.getHeight(peak.right))
        new_peak.height = 1 + max(tools.getHeight(new_peak.left), tools.getHeight(new_peak.right))

        return new_peak

    def rightRotate(self, peak):
        new_peak = peak.left
        r_subroot = new_peak.right

        new_peak.right = peak
        peak.left = r_subroot

        peak.height = 1 + max(tools.getHeight(peak.left), tools.getHeight(peak.right))
        new_peak.height = 1 + max(tools.getHeight(new_peak.left), tools.getHeight(new_peak.right))

        return new_peak

    def find(self, value):
        node = self.root

        while (node.left or node.right) and value != node.val:
            if node.val > value:
                node = node.left
            else:
                node = node.right

        if node.left or node.right:
            print("Node found at height: ", node.height)
        else:
            print("Node not found")

        return node

    def findReplacement(self, node):
        if not node or not node.left:
            return node
        else:
            return self.findReplacement(node.left)

    def insert(self, value):
        """ basically an interface for insertValue() function"""
        self.root = self.__insertValue(value, self.root)
        self.tree_height = self.root.height

        print("Value successfully inserted!")
        print("Updated tree height: " + str(self.tree_height))

    def __insertValue(self, value, node):
        # finding the parent node of the inserted one
        if node:
            if value > node.val:
                node.right = self.__insertValue(value, node.right)
            elif value < node.val:
                node.left = self.__insertValue(value, node.left)
        else:
            new_node = AVLTreeNode(value, height=1)
            self.values.append(value)

            return new_node

        node.height = 1 + max(tools.getHeight(node.left), tools.getHeight(node.right))

        if node.height < 3:
            return node

        diff = tools.getHeight(node.right) - tools.getHeight(node.left)

        if diff > 1 and value > node.right.val:
            node = self.leftRotate(node)

        elif diff > 1 and value < node.right.val:
            node.right = self.rightRotate(node.right)
            node = self.leftRotate(node)

        elif diff < -1 and value < node.left.val:
            node = self.rightRotate(node)

        elif diff < -1 and value > node.left.val:
            node.left = self.leftRotate(node.left)
            node = self.rightRotate(node)

        return node

    def __deleteValue(self, value, node):
        if node:
            if value > node.val:
                node.right = self.__deleteValue(value, node.right)
            elif value < node.val:
                node.left = self.__deleteValue(value, node.left)
            else:
                if not node.left:
                    node = node.right
                    return node
                elif not node.right:
                    node = node.left
                    return node
                replacement = self.findReplacement(node.right)
                node.val = replacement.val
                node.right = self.__deleteValue(node.right, node.val)
        else:
            print("Provided value hasn't been found...")
            return None

        node.height = 1 + max(tools.getHeight(node.left), tools.getHeight(node.right))

        if node.height < 3:
            return node

        diff = tools.getHeight(node.right) - tools.getHeight(node.left)

        if diff > 1 and value > node.right.val:
            node = self.leftRotate(node)

        elif diff > 1 and value < node.right.val:
            node.right = self.rightRotate(node.right)
            node = self.leftRotate(node)

        elif diff < -1 and value < node.left.val:
            node = self.rightRotate(node)

        elif diff < -1 and value > node.left.val:
            node.left = self.leftRotate(node.left)
            node = self.rightRotate(node)

        return node



    def delete(self, value):
        self.root = self.__deleteValue(value, self.root)
        self.tree_height = self.root.height

        print("Updated tree height: " + str(self.tree_height))


input_str = "(1)"
tools.inputCheck(input_str)

smth = AVLTree(input_str)
smth.insert(1)
smth.insert(10)
smth.insert(3)
smth.insert(8)
smth.insert(2)
smth.insert(4)
smth.insert(7)
smth.insert(6)
smth.insert(5)
smth.insert(9)
smth.delete(10)
smth.traversal(4)
