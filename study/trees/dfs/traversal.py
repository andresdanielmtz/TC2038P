class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


def preorder_traversal(root):
    if not root:
        return
    if root:
        print(root.val)
        preorder_traversal(root.left)
        preorder_traversal(root.right)


def inorder_traversal(root):
    if not root:
        return
    if root:
        inorder_traversal(root.left)
        print(root.val)
        inorder_traversal(root.right)

def postorder_traversal(root):
    if not root:
        return 
    if root:
        inorder_traversal(root.left)
        inorder_traversal(root.right)
        print(root.val)

def main():
    root = Node(1)
    root.left = Node(2)
    root.right = Node(3)
    root.left.left = Node(4)
    root.left.right = Node(5)
    root.right.left = Node(6)
    root.right.right = Node(7)
    postorder_traversal(root)


if __name__ == "__main__":
    main()
