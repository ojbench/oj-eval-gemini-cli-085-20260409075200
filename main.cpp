#include <iostream>
#include <cstdio>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool end_of_input = false;

inline int next_val() {
    if (end_of_input) return -1;
    int v = 0;
    int sign = 1;
    char c = getchar_unlocked();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) {
            end_of_input = true;
            return -1;
        }
        c = getchar_unlocked();
    }
    if (c == '-') {
        sign = -1;
        c = getchar_unlocked();
    }
    while (c >= '0' && c <= '9') {
        v = v * 10 + (c - '0');
        c = getchar_unlocked();
    }
    v *= sign;
    if (v == -2) {
        end_of_input = true;
        return -1;
    }
    return v;
}

Node* build_tree() {
    int v = next_val();
    if (v == -1) return nullptr;
    Node* node = new Node(v);
    node->left = build_tree();
    node->right = build_tree();
    return node;
}

bool prune_tree(Node*& node) {
    if (!node) return false;
    bool keep_left = prune_tree(node->left);
    bool keep_right = prune_tree(node->right);
    if (node->val == 0 && !keep_left && !keep_right) {
        delete node;
        node = nullptr;
        return false;
    }
    return true;
}

inline void print_int(int n) {
    if (n < 0) {
        putchar_unlocked('-');
        n = -n;
    }
    if (n == 0) {
        putchar_unlocked('0');
        return;
    }
    char buf[10];
    int i = 0;
    while (n > 0) {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }
    while (i > 0) {
        putchar_unlocked(buf[--i]);
    }
}

void print_tree(Node* node, bool& first) {
    if (!first) putchar_unlocked(' ');
    first = false;
    if (!node) {
        putchar_unlocked('-');
        putchar_unlocked('1');
        return;
    }
    print_int(node->val);
    print_tree(node->left, first);
    print_tree(node->right, first);
}

void delete_tree(Node* node) {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

int main() {
    Node* root = build_tree();
    prune_tree(root);
    
    bool first = true;
    print_tree(root, first);
    putchar_unlocked('\n');
    
    delete_tree(root);
    
    return 0;
}