/*******************************************************
 * Author: Youngsu Choi
 * Date: 2026-04-08
 * Description: Simple Hardware-Aware Memory Manager (SHAMM)
 *              For learning C++
 *******************************************************/
#include <iostream>
#include <cassert>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class BaseBlock {
    public:
        string name;

        BaseBlock(string n) : name(n) {}

        virtual ~BaseBlock() = default;

        virtual size_t getSize() const = 0;

        virtual void printInfo(int depth = 0) const = 0;

};


class DataBlock : public BaseBlock {
    public:
        size_t bytes;

        DataBlock(string n, size_t b) : BaseBlock(n), bytes(b) {}

        size_t getSize() const override {
            return bytes;
        }

        void printInfo(int depth = 0) const override {

            for (int i = 0; i < depth; i++) {
                cout << "  ";
            }
    
            cout << "[Data] Name: " << name << ", Size: " << bytes << " bytes" << endl;
        }
};

class SubGraph : public BaseBlock {
    public:
        vector<unique_ptr<BaseBlock>> children;

        SubGraph(string n) : BaseBlock(n) {}
    
        size_t getSize() const override {

            size_t total_bytes = 0;

            for (const unique_ptr<BaseBlock> &child : children) {
                total_bytes += child->getSize();
            }

            return total_bytes;
        }

        void printInfo(int depth = 0) const override {
            
            for (int i = 0; i < depth; i++) {
                cout << "  ";
            }

            cout << name << endl;

            for (const unique_ptr<BaseBlock> &child : children) {
                child ->printInfo(depth + 1);
            }
        }
};

BaseBlock* findInReg(const string& name, const vector<unique_ptr<BaseBlock>>& registry) {

    for (const auto &reg : registry) {
        // If current reg is a 'BaseBlock'
        if (reg->name == name) {
            return reg.get();
        }

        // If it's a subgraph then...
        // If casting fails dynamic_cast assigns nullptr
        SubGraph* sub = dynamic_cast<SubGraph*>(reg.get());

        if (sub) {
            BaseBlock* found = findInReg(name, sub->children);

            if (found) return found;
        }
    }

    return nullptr;
}


int main() {
    vector<unique_ptr<BaseBlock>> registry;

    auto core0 = make_unique<SubGraph>("NPU_Core_0");
    core0->children.emplace_back(make_unique<DataBlock>("Weights", 5000));
    core0->children.emplace_back(make_unique<DataBlock>("Bias", 1000));

    cout << "Before move: " << core0.get() << endl;

    auto core1 = make_unique<SubGraph>("System_Memory");
    core1->children.push_back(move(core0));
    core1->children.emplace_back(make_unique<DataBlock>("Input_Tensor", 2000));

    core1->printInfo();
    
    cout << "After move: " << core0.get() << endl;

    assert(core1->getSize() == 8000);

    // Test findInReg
    registry.push_back(move(core1));
    
    assert(findInReg("DoesNotExist", registry) == nullptr);
    cout << "DoesNotExist Passed!" << endl;
    assert(findInReg("NPU_Core_0", registry) != nullptr);
    cout << "Found NPU_Core_0!" << endl;


    return 0;
}