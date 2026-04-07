#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Task {
    private:
        string name;
        int priority;
    
    public:
        // Slightly faster way to initialize
        Task(string n, int p) : name(n), priority(p) {} 

        void display() const {
            cout << "PID: " << priority << ", " << "PName: " << name << '\n';
        }
};

int main() {

    vector<Task> tasks;

    // Add a few tasks
    // Use emplace_back instead of push_back
    // Thsi constructs the 'Task' directly into memory instead of temp 'Task'
    tasks.emplace_back(Task("Fix Bug", 1));
    tasks.emplace_back(Task("Fix Bug2", 2));
    tasks.emplace_back(Task("Fix Bug3", 3));
    tasks.emplace_back(Task("Fix Bug4", 4));
    tasks.emplace_back(Task("Fix Bug5", 5));

    // Print all tasks
    // for (Task task : tasks) { // Create full copies of task...
    //     task.display();
    // }

    for (const Task &task : tasks) {
        task.display();
    }

    return 0;
}