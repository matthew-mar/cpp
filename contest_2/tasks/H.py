import random

class Node:
    def __init__(self, value):
        self.value = value
        self.priority = random.randint(1, 10**9)
        self.size = 1
        self.left = None
        self.right = None

def update_size(node):
    if node:
        node.size = 1 + get_size(node.left) + get_size(node.right)

def merge(left, right):
    if not left or not right:
        return left or right

    if left.priority > right.priority:
        left.right = merge(left.right, right)
        update_size(left)
        return left
    else:
        right.left = merge(left, right.left)
        update_size(right)
        return right

def split(node, key):
    if not node:
        return None, None

    if get_size(node.left) >= key:
        left, node.left = split(node.left, key)
        update_size(node)
        return left, node
    else:
        node.right, right = split(node.right, key - get_size(node.left) - 1)
        update_size(node)
        return node, right

def insert(node, value, pos):
    left, right = split(node, pos)
    return merge(merge(left, value), right)

def get_size(node):
    return node.size if node else 0

def print_tree(node):
    if node:
        print_tree(node.left)
        print(node.value, end=' ')
        print_tree(node.right)

n, m = map(int, input().split())
tree = None

for i in range(n):
    tree = insert(tree, Node(i+1), i)

for _ in range(m):
    l, r = map(int, input().split())
    tree_left, tree = split(tree, l-1)
    tree_mid, tree_right = split(tree, r-l+1)
    tree = merge(tree_mid, merge(tree_left, tree_right))

print_tree(tree)
