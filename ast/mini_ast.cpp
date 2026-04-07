#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Node {
    public:
        string name;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node (string n) : name(n), left(nullptr), right(nullptr) {}

        // We assume depth will be 0 for roots
        void printTree(int depth = 0) {
            for (int i = 0; i < depth; i++) cout << "  ";
            
            if (depth) {
                cout << "|--";
            }

            cout << name << endl;

            if (left) {left->printTree(depth + 1);}
            if (right) {right->printTree(depth + 1);}
        }
};



int main() {

    // Root + Children
    auto root = make_unique<Node>("Add_Op");

    auto child1 = make_unique<Node>("Input_A");
    child1->left = make_unique<Node>("Input_A.2");
    child1->right = make_unique<Node>("Input_A.3");

    auto child2 = make_unique<Node>("Input_B");
    child2->left = make_unique<Node>("Input_B.2");
    child2->right = make_unique<Node>("Input_B.3");

    // Attach
    root->left = move(child1);
    root->right = move(child2);


    root -> printTree();

    return 0;
}