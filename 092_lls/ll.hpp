#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class exception : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested item does not exist\n";
  }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T t, Node * n1, Node * n2) : data(t), next(n1), prev(n2) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * s = rhs.head;
    while (s != NULL) {
      addBack(s->data);
      s = s->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList tmp(rhs);
      Node * original_head = head;
      head = tmp.head;
      tmp.head = original_head;
      Node * original_tail = tail;
      tail = tmp.tail;
      tmp.tail = original_tail;
      size = tmp.size;
    }
    return *this;
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    size++;
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    size++;
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
  }
  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL && curr->data != item) {
      curr = curr->next;
    }
    if (curr == NULL) {
      return false;
    }
    if (curr->next != NULL) {
      curr->next->prev = curr->prev;
    }
    else {
      tail = curr->prev;
    }
    if (curr->prev != NULL) {
      curr->prev->next = curr->next;
    }
    else {
      head = curr->next;
    }
    size -= 1;
    delete curr;
    return true;
  }
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw exception();
    }
    else {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw exception();
    }
    else {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
  }

  int find(const T & item) const {
    int index = 0;
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      index++;
      curr = curr->next;
    }
    return -1;
  }

  int getSize() const { return size; }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  friend class Tester;
};
#endif
