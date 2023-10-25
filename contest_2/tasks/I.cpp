#include <cmath>
#include <random>
#include <fstream>

class Node {

public:
    int key;
    int priority;
    long long sum;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int key): key(key), priority(rand()), sum(key) {}
};

class Treap {

public:
    Node* root = nullptr;

    static long long getSum(Node* node) {
        if (node != nullptr) {
            return node->sum;
        }
        return 0;
    }

    static void update(Node*& node) {
        if (node != nullptr) {
            node->sum = getSum(node->left) + node->key + getSum(node->right);
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

    static void split(Node* node, int key, Node*& a, Node*& b) {
        if (node == nullptr) {
            a = nullptr;
            b = nullptr;
            return;
        }

        if (node->key < key) {
            split(node->right, key, node->right, b);
            a = node;
        } else {
            split(node->left, key, a, node->left);
            b = node;
        }

        update(a);
        update(b);
    }

    void add(int key) {
        Node* less;
        Node* greater;
        split(root, key, less, greater);
        root = merge(merge(less, new Node(key)), greater);
    }

    bool search(int key) {
        Node* less;
        Node* equal;
        Node* greater;

        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        bool res = equal != nullptr;
        root = merge(merge(less, equal), greater);
        return res;
    }

    long long sum(int l, int r) {
        Node* less;
        Node* equal;
        Node* greater;
        
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);

        long long sum = getSum(equal);
        root = merge(merge(less, equal), greater);
        return sum;
    }
};

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    Treap treap;

    int n;
    inputFile >> n;

    long long previousSum = 0;
    for (int i = 0; i < n; i++) {
        std::string operation;
        inputFile >> operation;

        if (operation == "+") {
            int value;
            inputFile >> value;

            value = (value + previousSum) % ((int)std::pow(10, 9));
            if (! treap.search(value)) {
                treap.add(value);
            }

            previousSum = 0;
        } else {
            int l;
            int r;

            inputFile >> l >> r;

            previousSum = treap.sum(l, r);
            outputFile << previousSum << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
