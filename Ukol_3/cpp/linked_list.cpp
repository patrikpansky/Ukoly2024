#include <iostream>
#include <sstream>
#include <string>
#include <utility>

struct Node {
    int data;
    Node* next;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(Node** head, const int data) {
    Node* newNode = createNode(data);
    if (*head == nullptr) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtIndex(Node** head, int data, int index) {
    if (index == 0) {
        insertAtBeginning(head, data);
        return;
    }
    Node* newNode = createNode(data);
    Node* temp = *head;
    for (int i = 0; temp != nullptr && i < index - 1; i++) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        std::cout << "Index mimo rozsah\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteAtBeginning(Node** head) {
    if (*head == nullptr) return;
    Node* temp = *head;
    *head = (*head)->next;
    delete temp;
}

void deleteAtEnd(Node** head) {
    if (*head == nullptr) return;
    if ((*head)->next == nullptr) {
        delete* head;
        *head = nullptr;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

void deleteAtIndex(Node** head, int index) {
    if (*head == nullptr) return;
    if (index == 0) {
        deleteAtBeginning(head);
        return;
    }
    Node* temp = *head;
    for (int i = 0; temp != nullptr && i < index - 1; i++) {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr) {
        std::cout << "Index mimo rozsah\n";
        return;
    }
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
}

int findFirstOccurrence(Node* head, int value) {
    int index = 0;
    while (head != nullptr) {
        if (head->data == value) {
            return index;
        }
        head = head->next;
        index++;
    }
    return -1; 
}

void sortList(Node** head) {
    if (*head == nullptr) return;
    for (Node* i = *head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->data > j->data) {
                std::swap(i->data, j->data);
            }
        }
    }
}

void deleteList(Node** head) {
    while (*head != nullptr) {
        deleteAtBeginning(head);
    }
}

std::ostream& operator<<(std::ostream& os, Node* head) {
    while (head != nullptr) {
        os << head->data;
        if (head->next != nullptr) {
            os << " ";
        }
        head = head->next;
    }
    return os;
}

#ifndef __TEST__
int main() {
    Node* head = nullptr;
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 2);
    insertAtEnd(&head, 3);
    std::cout << "Seznam po vložení prvků: " << head << std::endl;

    std::cout << "První výskyt hodnoty 3 je na indexu: " << findFirstOccurrence(head, 3) << std::endl;
    sortList(&head);
    std::cout << "Seznam po třídění: " << head << std::endl;

    deleteAtBeginning(&head);
    deleteAtEnd(&head);
    std::cout << "Seznam po smazání prvků: " << head << std::endl;

    deleteList(&head);

    return 0;
}
#endif
