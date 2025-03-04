#include <iostream>
#include <string>
using namespace std;

// Structure to represent a Task node in the linked list
struct Task {
    int id;             // Unique task ID
    string description; // Task description
    int priority;       // Task priority (higher values indicate higher priority)
    Task* next;         // Pointer to the next task
};

class TaskManager {
private:
    Task* head; // Pointer to the head of the linked list

public:
    // Constructor: Initializes an empty task list
    TaskManager() { head = nullptr; }

    // Function to add a new task based on priority
    void addTask(int id, string desc, int priority) {
        Task* newTask = new Task{id, desc, priority, nullptr};

        // If list is empty or new task has the highest priority, insert at head
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            // Traverse the list to find the correct position for insertion
            Task* temp = head;
            while (temp->next && temp->next->priority >= priority)
                temp = temp->next;

            // Insert the new task at the correct position
            newTask->next = temp->next;
            temp->next = newTask;
        }
        cout << "Task added successfully!\n";
    }

    // Function to remove the task with the highest priority (head of the list)
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head; // Store the current head
        head = head->next; // Move head to the next node
        cout << "Removed task with ID: " << temp->id << "\n";
        delete temp; // Free memory
    }

    // Function to remove a specific task by its ID
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }

        // If the task to remove is the head
        if (head->id == id) {
            removeHighestPriorityTask();
            return;
        }

        Task* temp = head;
        while (temp->next && temp->next->id != id)
            temp = temp->next;

        if (!temp->next) {
            cout << "Task ID not found.\n";
            return;
        }

        // Remove the task and free memory
        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        cout << "Removed task with ID: " << toDelete->id << "\n";
        delete toDelete;
    }

    // Function to display all tasks in the list
    void viewTasks() {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* temp = head;
        while (temp) {
            cout << "ID: " << temp->id << ", Description: " << temp->description << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    // Destructor: Deletes all tasks to free memory
    ~TaskManager() {
        while (head)
            removeHighestPriorityTask();
    }
};

int main() {
    TaskManager tm;
    int choice, id, priority;
    string desc;

    do {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n2. View Tasks\n3. Remove Highest Priority Task\n4. Remove Task by ID\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: "; cin >> id;
                cin.ignore(); // Ignore newline character
                cout << "Enter Description: "; getline(cin, desc);
                cout << "Enter Priority: "; cin >> priority;
                tm.addTask(id, desc, priority);
                break;
            case 2:
                tm.viewTasks();
                break;
            case 3:
                tm.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: "; cin >> id;
                tm.removeTaskByID(id);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
