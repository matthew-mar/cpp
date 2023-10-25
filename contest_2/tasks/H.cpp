#include <random>
#include <fstream>
#include <iostream>

class Node {

public:
    int key;
    int priority;
    int size = 1;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int key) : key(key), priority(rand()) {}
}; 

class Treap {

public:
    Node* root = nullptr;

    static int getSize(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->size;
    }

    static void update(Node*& node) {
        if (node != nullptr) {
            node->size = getSize(node->left) + 1 + getSize(node->right);
        }
    }

    static Node* merge(Node* a, Node* b) {
        if (a == nullptr || b == nullptr) {
            if (a != nullptr) {
                return a;
            }
            return b;
        }

        if (a->priority > b->priority) {
            a->right = merge(a->right, b);
            update(a);
            return a;
        } else {
            b->left = merge(a, b->left);
            update(b);
            return b;
        }
    }

    static void split(Node* node, int k, Node*& a, Node*& b) {
        if (node == nullptr) {
            a = nullptr;
            b = nullptr;
            return;
        }

        if (getSize(node->left) < k) {
            split(node->right, k - getSize(node->left) - 1, node->right, b);
            a = node;
        } else {
            split(node->left, k, a, node->left);
            b = node;
        }

        update(a);
        update(b);
    }

    void add(int key) {
        root = merge(root, new Node(key));
    }

    void insert(int i, int x) {
        Node* less;
        Node* greater;
        split(root, i, less, greater);
        root = merge(merge(less, new Node(x)), greater);
    }

    int get(int i) {
        Node* less;
        Node* equal;
        Node* greater;

        split(root, i, less, greater);
        split(greater, 1, equal, greater);
        int value = equal->key;
        root = merge(merge(less, equal), greater);
        return value;
    }

    void remove(int index) {
        Node* less;
        Node* equal;
        Node* greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        root = merge(less, greater);
    }

    void inorderTraversal(Node* node, std::vector<int>& arr) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left, arr);
        arr.push_back(node->key);
        inorderTraversal(node->right, arr);
    }

    void printArray() {
        std::vector<int> arr;
        inorderTraversal(root, arr);
        std::cout << arr.size() << std::endl;
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    int size() {
        return getSize(root);
    }

    void shift(int l, int r) {
        Node* less;
        Node* equal;
        Node* greater;

        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(merge(equal, less), greater); 
    }
};

int main() {
    Treap treap;

    int n;
    int m;

    std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        treap.add(i + 1);
    }

    for (int i = 0; i < m; i++) {
        int l;
        int r;

        std::cin >> l >> r;
        treap.shift(l - 1, r - 1);
    }

    for (int i = 0; i < treap.size(); i++) {
        std::cout << treap.get(i) << " ";
    }

    return 0;
}
