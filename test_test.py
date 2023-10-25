import random

class TreapNode:
    def __init__(self, key):
        self.key = key
        self.priority = random.random()
        self.size = 1
        self.left = None
        self.right = None

def update_size(node):
    if node is not None:
        node.size = 1 + get_size(node.left) + get_size(node.right)

def merge(left, right):
    if left is None:
        return right
    if right is None:
        return left

    if left.priority > right.priority:
        left.right = merge(left.right, right)
        update_size(left)
        return left
    else:
        right.left = merge(left, right.left)
        update_size(right)
        return right

def split(node, key):
    if node is None:
        return None, None

    if node.key < key:
        left, right = split(node.right, key)
        node.right = left
        update_size(node)
        return node, right
    else:
        left, right = split(node.left, key)
        node.left = right
        update_size(node)
        return left, node

def insert(root, key):
    left, right = split(root, key)
    new_node = TreapNode(key)
    return merge(merge(left, new_node), right)

def erase(root, key):
    left, right = split(root, key)
    _, right = split(right, key + 1)
    return merge(left, right)

def get_size(node):
    if node is None:
        return 0
    return node.size

def print_array(root):
    if root is None:
        return
    print_array(root.left)
    print(root.key, end=' ')
    print_array(root.right)

n0, m = map(int, input().split())
array = list(map(int, input().split()))

root = None
for num in array:
    root = insert(root, num)

for _ in range(m):
    query = input().split()
    if query[0] == 'add':
        i, x = map(int, query[1:])
        left, right = split(root, i)
        root = merge(merge(left, TreapNode(x)), right)
    elif query[0] == 'del':
        i = int(query[1]) - 1
        root = erase(root, i)

print(get_size(root))
print_array(root)
