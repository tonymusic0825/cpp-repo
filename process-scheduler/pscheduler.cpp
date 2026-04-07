#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Task {
    private:
        string name;
        int priority;
    
    public:
        // Slightly faster way to initialize
        Task(string n, int p) : name(n), priority(p) {} 

        int getPriority() const {
            return priority;
        }

        void display() const {
            cout << "PID: " << priority << ", " << "PName: " << name << '\n';
        }
};

int main() {

    vector<Task> tasks;

    // Add a few tasks
    // Use emplace_back instead of push_back
    // Thsi constructs the 'Task' directly into memory instead of temp 'Task'
    tasks.emplace_back("Fix Bug", 1);
    tasks.emplace_back("Fix Bug2", 42);
    tasks.emplace_back("Fix Bug3", 5612);
    tasks.emplace_back("Fix Bug4", 2);
    tasks.emplace_back("Fix Bug5", 10);


    // Sort the tasks in priority order
    sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
        {return a.getPriority() < b.getPriority();});

    // Print all tasks
    // for (Task task : tasks) { // Create full copies of task...
    //     task.display();
    // }
    for (const Task &task : tasks) {
        task.display();
    }

    return 0;
}