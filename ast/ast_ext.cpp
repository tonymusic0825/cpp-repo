#include <iostream>
#include <string>
#include <memory>
#include <cassert>

using namespace std;

class Node {
    public:
        string name;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node (string n) : name(n), left(nullptr), right(nullptr) {}

        virtual ~Node() = default;

        virtual void display() const {
            cout << "Generic Node: " << name << endl;
        }

        virtual long evaluate() = 0;
        
        void printTree(int depth = 0) {
            for (int i = 0; i < depth; i++) cout << "  ";
            
            if (depth) {
                cout << "|--";
            }

            this->display();

            if (left) {left->printTree(depth + 1);}
            if (right) {right->printTree(depth + 1);}
        }
};

class InputNode : public Node {
    public:
        long value;
        InputNode(string n, long v) : Node(n), value(v) {}

        void display() const override {
            cout << "Input [" << name << "] Value: " << value << endl; 
        }

        long evaluate() {
            return value;
        }
};

class OpNode : public Node {
    public:
        string op;
        OpNode(string n, string o) : Node(n), op(o) {}

        void display() const override {
            cout << "Operation [" << name << "] Type: " << op << endl;
        }

        long evaluate() {
            if (op == "MUL") {
                return left->evaluate() * right->evaluate();
            }

            return left->evaluate() + right->evaluate();
        }
};


int main() {
    auto root = make_unique<OpNode>("Final_Mul", "MUL");

    auto add_branch = make_unique<OpNode>("Sub_Add", "ADD");
    add_branch->left = make_unique<InputNode>("Const_10", 10);
    add_branch->right = make_unique<InputNode>("Const_20", 20);

    auto const_5 = make_unique<InputNode>("Const_5", 5);

    root->left = move(add_branch);
    root->right = move(const_5);

    cout << "--- Tree Structure ---" << endl;
    root->printTree();

    cout << "\n--- Execution Result ---" << endl;
    long result = root->evaluate();
    cout << "Final Result: " << result << endl;

    // Final Check
    if (result == 150) {
        cout << "SUCCESS: Math is correct!" << endl;
    } else {
        cout << "FAILURE: Something went wrong in recursion." << endl;
    }

    return 0;
}