#include <iostream>
using namespace std;

struct task {
    int tid;
    string tName;
};

class Employee {
    private:
        int salary;
        int age;
        int ssid;
    
    public:
        string name;

        Employee() {
            salary = 0;
            ssid = 0;
            age = 0;
            name = "Unknown";
        }

        Employee(int s, int a, int ss, string n) { 
            name = n;
            salary = s;
            ssid = ss;
            age = a;
        }
        
        // Setters and Getters in public
        void setSalary(int s) {
            salary = s;
        }

        int getSalary() {
            return salary;
        }

};

int main() {

    Employee myObj;
    myObj.setSalary(50000);
    cout << myObj.getSalary();

    return 0;
}
