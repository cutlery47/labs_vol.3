from tree import TreeNode
from tree import Tree
import tools


class AVLTreeNode(TreeNode):
    def __init__(self, val: int = 0, height: int = 0, left=None, right=None, parent=None):
        """ basically the same class besides that height attribute was added """

        super(AVLTreeNode, self).__init__(val, left, right)
        self.parent = parent
        self.height = height


class AVLTree(Tree):
    def __init__(self, string):
        # Creating a binary from given data
        super().__init__(string)

        # Array for storing elements of the binary tree given as input
        self.values = []

        # Value for storing tree height
        self.tree_height = 0

        # Collecting elements from initial tree
        self.__collectValues(self.root)
        self.values.sort()

        # Calculating AVL tree height
        self.__getAVLHeight(self.root, 0)

        # Converting initial tree to AVL
        self.root = self.binaryToAVL(self.values, None)

        self.__adjustNodesHeight(self.root, 1)

    def __collectValues(self, node: TreeNode = None):
        """ parsing the binary tree from input string --- collecting all the values """

        if not node:
            return

        self.values.append(node.val)
        self.__collectValues(node.left)
        self.__collectValues(node.right)
        return

    def __getAVLHeight(self, node, height):
        """ going down the tree to calculate its depth """

        if not node:
            self.tree_height = max(self.tree_height, height)
            return

        self.__getAVLHeight(node.left, height + 1)
        self.__getAVLHeight(node.right, height + 1)
        return

    def __adjustNodesHeight(self, node, height):
        if not node:
            return

        node.height = height
        self.__adjustNodesHeight(node.left, height + 1)
        self.__adjustNodesHeight(node.right, height + 1)

    def binaryToAVL(self, nums, parent):
        """ converting input binary tree values to an avl tree """

        if len(nums) == 0:
            return

        ind = (len(nums) - 1) // 2
        node = AVLTreeNode(nums[ind])

        node.parent = parent
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

        peak.height = 1 + max(peak.left.height, peak.right.height)
        new_peak.height = 1 + max(new_peak.left.height, new_peak.right.height)

        return new_peak

    def rightRotate(self, peak):
        new_peak = peak.left
        r_subroot = new_peak.right

        new_peak.right = peak
        peak.left = r_subroot

        peak.height = 1 + max(peak.left.height, peak.right.height)
        new_peak.height = 1 + max(new_peak.left.height, new_peak.right.height)

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

    def insert(self, value):
        if not self.root:
            return

        """ basically an interface for insertValue() function"""
        self.__insertValue(value, self.root)

    def __insertValue(self, value, node):
        # finding the parent node of the inserted one
        if node.left or node.right:
            if value > node.val:
                self.__insertValue(value, node.right)
            elif value > node.val:
                self.__insertValue(value, node.left)
        else:
            new_node = AVLTreeNode(value, height=node.height + 1, parent=node)
            self.tree_height += 1

            if value < node.val:
                node.left = new_node
            else:
                node.right = new_node

        node.height += 1

        if not (node.left and node.right) or (self.tree_height - node.height) < 2:
            return

        diff = node.right.height - node.left.height

        if diff > 2 and value > node.right.val:
            node = self.leftRotate(node)

        if diff > 2 and value < node.right.val:
            node.left = self.leftRotate(node)
            node = self.rightRotate(node)

        if diff < 2 and value < node.right.val:
            node.right = self.rightRotate(node)
            node = self.leftRotate(node)

        return

    def delete(self, value):
        pass


input_str = "(5(3(2(1)(4))))"
tools.inputCheck(input_str)

smth = AVLTree(input_str)
print(smth.insert(10))
