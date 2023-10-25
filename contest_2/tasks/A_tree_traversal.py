class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


def in_order(current, path):
    if not current:
        return
    
    in_order(current.left, path)
    path.append(str(current.key))
    in_order(current.right, path)


def pre_order(current, path):
    if not current:
        return
    
    path.append(str(current.key))
    pre_order(current.left, path)
    pre_order(current.right, path)


def post_order(current, path) -> None:
    if not current:
        return
    
    post_order(current.left, path)
    post_order(current.right, path)
    path.append(str(current.key))


def make_tree(nodes):
    tree = {}
    for i in range(len(nodes)):
        key, left_index, right_index = nodes[i]
        
        if i not in tree:
            tree[i] = Node(key)
        current = tree[i]

        if left_index != -1:
            if left_index not in tree:
                tree[left_index] = Node(nodes[left_index][0])
            current.left = tree[left_index]
        
        if right_index != -1:
            if right_index not in tree:
                tree[right_index] = Node(nodes[right_index][0])
            current.right = tree[right_index]
    
    return tree


def get_nodes():
    nodes = []
    n = int(input())
    for _ in range(n):
        nodes.append(list(map(int, input().split())))
    return nodes


def write_path(path):
    print(" ".join(path))


def main():
    nodes = get_nodes()
    tree = make_tree(nodes)

    in_order_path = []
    pre_order_path = []
    post_order_path = []

    in_order(tree[0], in_order_path)
    pre_order(tree[0], pre_order_path)
    post_order(tree[0], post_order_path)

    write_path(in_order_path)
    write_path(pre_order_path)
    write_path(post_order_path)


main()
