import sys

sys.setrecursionlimit(100_000)


class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


class Tree:
    def __init__(self, nodes) -> None:
        self.inline_nodes = [Node(0) for _ in range(len(nodes))]

        for i in range(len(nodes)):
            key, left_index, rihgt_index = nodes[i]

            self.inline_nodes[i].key = key
            
            if left_index != -1:
                self.inline_nodes[i].left = self.inline_nodes[left_index]
            
            if rihgt_index != -1:
                self.inline_nodes[i].right = self.inline_nodes[rihgt_index]

    def in_order(self, current, path):
        if not current:
            return
        
        self.in_order(current.left, path)
        path.append(current.key)
        self.in_order(current.right, path)

    def check(self):
        path = []
        self.in_order(self.inline_nodes[0], path)
        
        previous_key = path[0]
        for i in range(1, len(path)):
            current_key = path[i]
            if (current_key <= previous_key):
                return False
            previous_key = current_key
        
        return True
    
def main():
    n = int(input())
    if n == 0:
        print("CORRECT")
        return

    nodes = []
    for _ in range(n):
        nodes.append(list(map(int, input().split())))
    
    tree = Tree(nodes)
    if tree.check():
        print("CORRECT")
    else:
        print("INCORRECT")


main()
