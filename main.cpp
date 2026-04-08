#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

bool end_of_input = false;

int next_val() {
    if (end_of_input) return -1;
    int v;
    if (cin >> v) {
        if (v == -2) {
            end_of_input = true;
            return -1;
        }
        return v;
    }
    end_of_input = true;
    return -1;
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

void print_tree(Node* node, bool& first) {
    if (!first) cout << " ";
    first = false;
    if (!node) {
        cout << "-1";
        return;
    }
    cout << node->val;
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Node* root = build_tree();
    prune_tree(root);
    
    bool first = true;
    print_tree(root, first);
    cout << "\n";
    
    delete_tree(root);
    
    return 0;
}
