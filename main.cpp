#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
struct Node {
    T data;
    shared_ptr<Node<T>> next;
    weak_ptr<Node<T>> prev;

    Node(const T& val) : data(val), next(nullptr) {}
};

template <typename T>
class SinglyLinkedList {
private:
    shared_ptr<Node<T>> head;
    size_t list_size;

public:
    SinglyLinkedList() : head(nullptr), list_size(0) {}

    void push_front(const T& val) {
        auto newNode = make_shared<Node<T>>(val);
        newNode->next = head;
        head = newNode;
        list_size++;
    }

    void push_back(const T& val) {
        auto newNode = make_shared<Node<T>>(val);
        if (!head) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        list_size++;
    }

    void pop_front() {
        if (empty()) throw runtime_error("List is empty. Cannot pop_front.");
        head = head->next;
        list_size--;
    }

    void pop_back() {
        if (empty()) throw runtime_error("List is empty. Cannot pop_back.");
        if (list_size == 1) {
            head = nullptr;
        } else {
            auto current = head;
            while (current->next->next) {
                current = current->next;
            }
            current->next = nullptr;
        }
        list_size--;
    }

    T& operator[](size_t index) {
        if (index >= list_size) throw out_of_range("Index out of bounds.");
        auto current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void insert(size_t index, const T& val) {
        if (index > list_size) throw out_of_range("Index out of bounds.");
        if (index == 0) {
            push_front(val);
            return;
        }
        auto newNode = make_shared<Node<T>>(val);
        auto current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        list_size++;
    }

    void erase(size_t index) {
        if (index >= list_size) throw out_of_range("Index out of bounds.");
        if (index == 0) {
            pop_front();
            return;
        }
        auto current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        current->next = current->next->next;
        list_size--;
    }

    size_t size() const { return list_size; }

    bool empty() const { return list_size == 0; }

    int find(const T& val) const {
        auto current = head;
        int index = 0;
        while (current) {
            if (current->data == val) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    friend ostream& operator<<(ostream& os, const SinglyLinkedList& list) {
        auto current = list.head;
        while (current) {
            os << current->data << " -> ";
            current = current->next;
        }
        os << "null";
        return os;
    }
};

template <typename T>

int main() {
    try {
        cout << "=== Singly Linked List Test (Int) ===\n";
        SinglyLinkedList<int> sList;
        
        sList.push_back(10);
        sList.push_back(20);
        sList.push_front(5);
        cout << "List after pushes: " << sList << " | Size: " << sList.size() << "\n";
        
        sList.insert(2, 15);
        cout << "List after inserting 15 at index 2: " << sList << "\n";
        
        sList.erase(1);
        cout << "List after erasing index 1: " << sList << "\n";
        
        sList.pop_front();
        sList.pop_back();
        cout << "List after pop_front and pop_back: " << sList << "\n";
        
        cout << "Element at index 0: " << sList[0] << "\n";
        cout << "Find '15' index: " << sList.find(15) << "\n\n";

        cout << "=== Doubly Linked List Test (String) ===\n";
        DoublyLinkedList<string> dList;
        
        dList.push_back("Hello");
        dList.push_back("World");
        dList.push_front("C++");
        cout << "List after pushes: " << dList << " | Size: " << dList.size() << "\n";
        
        dList.insert(1, "loves");
        cout << "List after inserting 'loves' at index 1: " << dList << "\n";
        
        dList.erase(2);
        cout << "List after erasing index 2: " << dList << "\n";
        
        cout << "Is list empty? " << (dList.empty() ? "Yes" : "No") << "\n";

        cout << "\n=== Testing Exceptions ===\n";
        cout << "Trying to access out of bounds...\n";
        cout << dList[100] << "\n";

    } catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
