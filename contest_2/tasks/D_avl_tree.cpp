#include <fstream>

class Node {

public:
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    int height;

    Node(int k) : key(k), height(1) {}
};

class Tree {
public:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if (leftHeight > rightHeight) {
            node->height = leftHeight + 1;
        } else {
            node->height = rightHeight + 1;
        }
    }

    Node* rotateRight(Node* node) {
        Node* left = node->left;
        Node* right = left->right;

        left->right = node;
        node->left = right;

        updateHeight(node);
        updateHeight(left);

        return left;
    }

    Node* rotateLeft(Node* node) {
        Node* right = node->right;
        Node* left = right->left;

        right->left = node;
        node->right = left;

        updateHeight(node);
        updateHeight(right);

        return right;
    }

    Node* insertNode(Node* node, int key) {
        Node* newNode = new Node(key);

        if (node == nullptr) {
            return newNode;
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key);
        } else {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* getMinNode() {
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        } 
        return current;
    }

    Node* deleteNode(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* tmp;
                if (node->left != nullptr) {
                    tmp = node->left;
                } else {
                    tmp = node->right;
                }

                if (tmp == nullptr) {
                    tmp = node;
                    node = nullptr;
                } else {
                    *node = *tmp;
                }
                delete tmp;
            } else {
                Node* tmp = getMinNode();
                node->key = tmp->key;
                node->right = deleteNode(node->right, tmp->key);
            }
        }

        if (node == nullptr) {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return nullptr;
    }
    
    bool search(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node != nullptr;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }
};

int main() {
    Tree tree = Tree();

    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    while (! inputFile.eof()) {
        std::string commnad;
        int value;

        inputFile >> commnad;
        inputFile >> value;

        if (commnad == "insert") {
            tree.root = tree.insertNode(tree.root, value);
        } else if (commnad == "exists") {
            if (tree.search(tree.root, value)) {
                outputFile << "true" << std::endl;
            } else {
                outputFile << "false" << std::endl;
            }
        } else if (commnad == "delete") {
            tree.root = tree.deleteNode(tree.root, value);
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
