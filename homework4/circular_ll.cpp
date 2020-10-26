enum Status{ERROR, OK};
class CircularLinkedList;
class Node {
private:
    Node* next;
    int value;
public:
    friend class CircularLinkedList;
    Node(int value = 0) : value(value) {}
};
class CircularLinkedList {
private:
    Node* rear;
public:
    CircularLinkedList() {
        rear = new Node();
        rear->next = rear;
    }
    Status enqueue(int value) {
        Node* temp = new Node(value);
        if (!temp) return Status::ERROR;
        temp->next = rear->next; // connect temp to head
        rear->next = temp;
        rear = temp;
        return Status::OK;
    }
    Status dequeue(int& value) {
        if (rear->next == rear) return Status::ERROR;
        Node* head = rear->next;
        value = head->value;
        free(head->next);
        head->next = head->next->next;
        return Status::OK;
    }
};