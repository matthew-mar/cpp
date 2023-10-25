def make_tree(nodes, tree, current_node, start, end):
    if start == end:
        tree[current_node] =  nodes[start]
    else:
        mid = (start + end) // 2
        make_tree(nodes, tree, 2 * current_node + 1, start, mid)
        make_tree(nodes, tree, 2 * current_node + 2, mid + 1, end)
        tree[current_node] = min(tree[2 * current_node + 1], tree[2 * current_node + 2])


def get_min(tree, node, start, end, left, right):
    if left > end or right < start:
        return 200_000
    if left <= start and right >= end:
        return tree[node]
    mid = (start + end) // 2
    return min(
        get_min(tree, 2 * node + 1, start, mid, left, right),
        get_min(tree, 2 * node + 2, mid + 1, end, left, right)
    )


def update_tree(tree, node, start, end, i, v):
    if start == end:
        tree[node] = v
    else:
        mid = (start + end) // 2
        if i <= mid:
            update_tree(tree, 2 * node + 1, start, mid, i, v)
        else:
            update_tree(tree, 2 * node + 2, mid + 1, end, i, v)
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2])


n = int(input())
tree = []
nodes = []
for _ in range(n):
    op, x, y = input().split()
    if op == "?":
        i, j = int(x), int(y)
        print(get_min(tree, 0, 0, len(nodes) - 1, i - 1, j - 1))
    else:
        i, x = int(x), int(y)
        nodes.insert(i, x)
        tree = [200_000] * (len(nodes) * 4)
        make_tree(nodes, tree, 0, 0, len(nodes) - 1)
