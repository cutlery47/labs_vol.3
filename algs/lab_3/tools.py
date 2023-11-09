def inputCheck(tree_string):
    if tree_string.count("(") != tree_string.count(")"):
        raise Exception("Input String Error: Parentheses sequence is not valid")

def getHeight(node):
    return 0 if not node else node.height

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