from collections import deque


class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def bfs(root):
    if not root:
        return
    queue = [root]
    l = [[root.val]]
    
    while queue:
        s = queue.pop(0)
        la = []
        if s.left:
            queue.append(s.left)
        if s.right:
            queue.append(s.right)
        
    print(l)


def main():
    root = Node(1)
    root.left = Node(2)
    root.right = Node(3)
    root.right.left = Node(6)
    root.right.right = Node(7)
    root.left.left = Node(4)
    root.left.right = Node(5)
    bfs(root)


if __name__ == "__main__":
    main()
