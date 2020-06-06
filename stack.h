#pragma once

#include <stdexcept>

template<typename T>
class LinkedList {
    struct Node {
        explicit Node(T aElement) : element(aElement) {};
        const T element;
        Node *nextNode = nullptr;
        Node *prevNode = nullptr;
    };

    Node *front = nullptr;
    Node *back = nullptr;
public:
    LinkedList() = default;

    LinkedList(const LinkedList &obj) {
        if (obj.empty()) return;

        Node *node = obj.front;
        push_back(node->element);

        while (node->nextNode != nullptr) {
            node = node->nextNode;
            push_back(node->element);
        }
    };

    void push_back(T element) {
        Node *newNode = new Node(element);

        if (empty()) {
            front = newNode;
            back = newNode;
            return;
        }

        Node *oldBack = back;
        oldBack->nextNode = newNode;
        newNode->prevNode = oldBack;
        back = newNode;
    };

    T pop_back() {
        if (empty()) {
            throw std::out_of_range("There are no elements in the list");
        }

        if (back->prevNode == nullptr) {
            front = nullptr;
        }

        T value = back->element;
        Node *newBack = back->prevNode;
        if (newBack != nullptr) newBack->nextNode = nullptr;
        delete back;
        back = newBack;
        return value;
    };

    [[nodiscard]] const T &peek_back() const {
        if (empty()) {
            throw std::out_of_range("There are no elements in the list");
        }

        return back->element;
    };

    [[nodiscard]] bool empty() const {
        return front == nullptr;
    }

    ~LinkedList() {
        if (empty()) return;
        Node *node = front;
        Node *next;
        while (node != nullptr) {
            next = node->nextNode;
            delete node;
            node = next;
        }
    }

};

template<typename T>
class Stack : private LinkedList<T> {
public:
    void push(T element) {
        this->push_back(element);
    };

    T pop() {
        return this->pop_back();
    };

    T peek() {
        return this->peek_back();
    };

    bool empty() {
        return LinkedList<T>::empty();
    }
};
