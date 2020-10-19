#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//ListNode: Employee Node
class Employee {
public:
    int id;
    double hourlyRate;
    string name;
    double hours;
    double wage;
    Employee *next;

    Employee() {
        this->next = NULL;
    }
    Employee(int id, double hourlyRate, string name) {
        int i = 0;
        //delete leading spaces in name
        while (i < name.length() && (name[i] == ' ' || name[i] == '\t'))
            i++;
        name = name.substr(i, name.length() - i);
        this->id = id;
        this->hourlyRate = hourlyRate;
        this->name = name;
        this->hours = 0;
        this->wage = 0;
        this->next = NULL;
    }
};
class EmployeeList{
public:
    EmployeeList();
    void push(Employee *new_node);
    Employee* mergeSort(Employee *head);
    void set_head(Employee* new_head);
    Employee* get_head();
    void printWage();

private:
    Employee* merge(Employee *node1, Employee *node2);
    Employee *dummy;
};

void EmployeeList::set_head(Employee* new_head) {
    dummy->next = new_head;
}
EmployeeList::EmployeeList() {
    dummy = new Employee(); //dummy->next = head
}


void EmployeeList::push(Employee *new_node) {
    new_node->next = dummy->next;
    dummy->next = new_node;
}
Employee* EmployeeList::mergeSort(Employee *head) {
    if(!head || !head->next)
        return head;
    Employee *slow = head, *fast = head, *pre = head;
    while(fast && fast->next) {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = NULL;
    return merge(mergeSort(head), mergeSort(slow));
}
Employee* EmployeeList::merge(Employee *node1, Employee *node2) {
    if(!node1) return node2;
    if(!node2) return node1;
    if(node1->wage > node2->wage) {
        node1->next = merge(node1->next, node2);
        return node1;
    }
    else {
        node2->next = merge(node1, node2->next);
        return node2;
    }
}

void EmployeeList::printWage() {

    cout << "*********Payroll Information*********" << endl;
    Employee *tmp = dummy->next;
    while(tmp != NULL) {
        cout << tmp->name << ", $" << tmp->wage << endl;
        tmp = tmp->next;
    }
    cout << "*********End payroll*********" << endl;
}

Employee* EmployeeList::get_head() {
    return dummy->next;
}

void openInputFile(ifstream &inFile) {
    string filename;
    cout << "What's the filename?" << endl;
    cin >> filename;
    inFile.open(filename);
    while(!inFile) {
        cout << "Cannot find " << filename << "; ";
        cout << "What's the filename?" << endl;
        cin >> filename;
        inFile.clear();
        inFile.open(filename);
    }
}




int main() {
    // Open and Read the first file
    cout << "Please open the first file:" << endl;
    ifstream inputFile;
    openInputFile(inputFile);
    int id;
    double rate;
    string name;
    EmployeeList *employeeList = new EmployeeList();
    while (inputFile >> id) {
        inputFile >> rate;
        inputFile.ignore(9999, ' ');
        getline(inputFile, name);
        Employee *new_node = new Employee(id, rate, name);
        employeeList->push(new_node);
    }

    //Open and Read the second file
    cout << "Please open the second file:" << endl;
    ifstream inputFile2;
    openInputFile(inputFile2);
    double hours;
    int ID;
    while (inputFile2 >> ID) {
        inputFile2 >> hours;
        Employee *node = employeeList->get_head();
        while(node != NULL) {
            if (node->id == ID) {
                node->hours += hours;
                break;
            }
            node = node->next;
        }
    }


    //Calculate wage
    Employee *e = employeeList->get_head();
    while(e != NULL) {
        e->wage = e->hours * e->hourlyRate;
        e = e->next;
    }


    // Output
    Employee *ee = employeeList->get_head();
    employeeList->set_head(employeeList->mergeSort(ee));
    employeeList->printWage();
    return 0;
}

