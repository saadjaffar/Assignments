#include <iostream>
#include <string>
using namespace std;

class Patient {
public:
    string name;
    int arrivalOrder;
    string condition;
    int priority;

    Patient(string n, int order, string cond, int pri)
        : name(n), arrivalOrder(order), condition(cond), priority(pri) {}
};

class PriorityQueue {
private:
    struct Node {
        Patient patient;
        Node* next;
        Node(Patient p) : patient(p), next(nullptr) {}
    };

    Node* front;

public:
    PriorityQueue() : front(nullptr) {}

    void enqueue(Patient newPatient) {
        Node* newNode = new Node(newPatient);

        if (!front || newPatient.priority < front->patient.priority) {
            newNode->next = front;
            front = newNode;
            return;
        }

        Node* current = front;
        while (current->next && current->next->patient.priority <= newPatient.priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    void displayQueue() {
        if (!front) {
            cout << "No patients in queue.\n";
            return;
        }

        cout << "\nCurrent Treatment Order:\n";
        cout << "------------------------\n";
        Node* current = front;
        while (current) {
            cout << current->patient.name << " - " << current->patient.condition
                 << " (Priority: " << current->patient.priority
                 << ", Arrival: " << current->patient.arrivalOrder << ")\n";
            current = current->next;
        }
    }
};

void addPatient(PriorityQueue& queue, int& arrivalCount) {
    string name, condition;
    cout << "Enter patient name: ";
    cin >> name;
    cout << "Enter emergency condition: ";
    cin.ignore();
    getline(cin, condition);

    int priority = 5;
    if (condition == "Heart Attack" || condition == "Stroke") {
    priority = 1;
    }

    else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm") {
    priority = 2;
    }

    else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine") {
    priority = 3;
    }

    else if (condition == "Small Cut" || condition == "Mild Cold") {
    priority = 4;
    }

    queue.enqueue(Patient(name, ++arrivalCount, condition, priority));
    cout << "Patient added successfully!\n";
}

int main() {
    PriorityQueue treatmentQueue;
    int arrivalOrder = 0, choice;

    do {
        cout << "\nHospital Treatment System\n"
             << "1. Add Patient\n"
             << "2. Show Treatment Order\n"
             << "3. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addPatient(treatmentQueue, arrivalOrder); break;
            case 2: treatmentQueue.displayQueue(); break;
            case 3: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
