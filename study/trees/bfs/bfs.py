class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

def printCurrentLevel(root, level):
    if root is None:
        return
    if level == 1: 
        print(root.key, end = " ")
    elif level > 1: 
        printCurrentLevel(root.left, level - 1) 
        printCurrentLevel(root.right, level - 1)

def printLevelOrder(root): 
    h = height(root)
    for index in range(1, h + 1):
        printCurrentLevel(root, index)
    print("\n")

def height(node):
    if node is None:
        return 0
    lheight = height(node.left) 
    rheight = height(node.right)
    if lheight > rheight:
        return lheight + 1
    else:
        return rheight + 1

if __name__ == "__main__":
    root = Node(1)
    root.left = Node(2)
    root.right = Node(3)
    root.left.left = Node(4)
    root.left.right = Node(5)
    root.right.left = Node(6)
    root.right.right = Node(7)
    print("Heights:")
    print(f"Root: {height(root)}")
    print(f"Root -> Left: {height(root.left)}")
    print(f"Root -> Left -> Left: {height(root.left.left)}")
    printLevelOrder(root)
