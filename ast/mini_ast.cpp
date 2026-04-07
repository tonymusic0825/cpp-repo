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
    auto child3 = make_unique<Node>("Input_A.2");
    auto child4 = make_unique<Node>("Input_A.3");

    auto child2 = make_unique<Node>("Input_B");
    auto child5 = make_unique<Node>("Input_B.2");
    auto child6 = make_unique<Node>("Input_B.3");

    // Attach
    child2->left = move(child5);
    child2->right = move(child6);

    child1->left = move(child3);
    child1->right = move(child4);

    root->left = move(child1);
    root->right = move(child2);


    root -> printTree();

    return 0;
}