#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#pragma once

#include <string>
#include <sstream>

/**
 * @mainpage Introduction

This is a realization of deque on doubly linked list.

*/

template<class data_t, class MemStrategy>
class Deque {


private:

  // Class for deque elements.
  class elem {
  public:
    data_t data;    // Stored data
    elem* next;     // Pointer to the next element in deque
    elem* prev;     // Pointer to the previous element in deque
  };


  // Attributes of the deque.
  elem* head;      // Pointer to the first element in deque
  elem* tail;      // Pointer to the last element in deque
  MemStrategy ms;  // Class, that provides memory management methods

public:

  /**
  * @defgroup Ctors_group Constructors
  * @{
  */

  /**
  * @brief Default constructor (without parameters).
  */
  Deque() : head(nullptr), tail(nullptr) { }

  /**
  * @brief Initializer list constructor.
  * @param elems - initializer list of data for deque elements
  */
  Deque(const std::initializer_list<data_t> elems) : head(nullptr), tail(nullptr) {

    for (auto& elem : elems) {
      try {
        pushTail(elem);
      }
      catch (int) {
        return;
      }
    }
  }

  /**
  * @brief Copy constructor.
  * @param other - constant reference to another deque
  */
  Deque(Deque const& other) : head(nullptr), tail(nullptr) {
    elem* tmp = other.head;
    while (tmp != nullptr) {
      try {
        pushTail(tmp->data);
      }
      catch (int ex) {
        return;
      }
      tmp = tmp->next;
    }
  }

  /**
  * @brief Move constructor.
  * @param other - r-value reference to another deque
  */
  Deque(Deque&& other) : head(nullptr), tail(nullptr) {
    this->head = other.head;
    this->tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
  }

  /**@}*/

  /**
  * @defgroup Dtor_group Destructor
  * @{
  */

  /**
  * @brief Destructor.
  */
  ~Deque() { clear(); }

  /**
  * @brief Free memory allocated for all of the deque elements.
  */
  void clear() {
    elem* tmp;

    while (head != nullptr) {
      tmp = head->next;
      ms.memFree(head);
      head = tmp;
    }

    tail = nullptr;
  }

  /**@}*/


  /**
  * @defgroup Push_group Push Methods
  * @{
  */

  /**
  * @brief Push element with given data to the head of deque (using copy semantics).
  * 
  * ! Throws an exception of int (-1) in case there's not enough memory.
  * 
  * @param data - constant reference to data that needs to be stored in a new deque element
  */
  void pushHead(data_t const& data) {
    elem* newElem;

    newElem = (elem*)ms.memMalloc(sizeof(elem));
    if (newElem == nullptr) {
      std::cerr << "Cannot push head element: not enough memory.\n";
      throw -1;
      return;
    }

    newElem->data = data;
    newElem->next = head;
    newElem->prev = nullptr;

    if (head == nullptr)
      head = tail = newElem;
    else {
      head->prev = newElem;
      head = newElem;
    }
  }

  /**
  * @brief Push element with given data to the head of deque (using move semantics).
  *
  * ! Throws an exception of int (-1) in case there's not enough memory.
  *
  * @param data - r-value reference to data that needs to be stored in a new deque element
  */
  void pushHead(data_t&& data) {
    elem* newElem;

    newElem = (elem*)ms.memMalloc(sizeof(elem));
    if (newElem == nullptr) {
      std::cerr << "Cannot push head element: not enough memory.\n";
      throw - 1;
      return;
    }

    newElem->data = std::move(data);
    newElem->next = head;
    newElem->prev = nullptr;
    

    if (head == nullptr)
      head = tail = newElem;
    else {
      head->prev = newElem;
      head = newElem;
    }
  }

  /**
  * @brief Push element with given data to the tail of deque (using copy semantics).
  *
  * ! Throws an exception of int (-1) in case there's not enough memory.
  *
  * @param data - constant reference to data that needs to be stored in a new deque element
  */
  void pushTail(data_t const& data) {
    elem* newElem;

    newElem = (elem*)ms.memMalloc(sizeof(elem));
    if (newElem == nullptr) {
      std::cerr << "Cannot push tail element: not enough memory.\n";
      throw - 1;
      return;
    }

    newElem->data = data;
    newElem->next = nullptr;
    newElem->prev = tail;

    if (tail == nullptr)
      head = tail = newElem;
    else {
      tail->next = newElem;
      tail = newElem;
    }   
  }

  /**
  * @brief Push element with given data to the tail of deque (using move semantics).
  *
  * ! Throws an exception of int (-1) in case there's not enough memory.
  *
  * @param data - r-value reference to data that needs to be stored in a new deque element
  */
  void pushTail(data_t&& data) {
    elem* newElem;

    newElem = (elem*)ms.memMalloc(sizeof(elem));
    if (newElem == nullptr) {
      std::cerr << "Cannot push tail element: not enough memory.\n";
      throw - 1;
      return;
    }

    newElem->data = std::move(data);
    newElem->next = nullptr;
    newElem->prev = tail;

    if (tail == nullptr)
      head = tail = newElem;
    else {
      tail->next = newElem;
      tail = newElem;
    }
  }

  /**@}*/

  /**
  * @defgroup Pop_group Pop Methods
  * @{
  */

  /**
  * @brief Remove the element from the head of deque.
  */
  void popHead(void) {
    if (head == nullptr)
      std::cerr << "Cannot pop head element: deque is empty.\n";

    elem* tmp = head->next;
    ms.memFree(head);
    tmp->prev = nullptr;
    head = tmp;
  }

  /**
  * @brief Remove the element from the tail of deque.
  */
  void popTail(void) {
    if (tail == nullptr)
      std::cerr << "Cannot pop tail element: deque is empty.\n";

    elem* tmp = tail->prev;
    ms.memFree(tail);
    tmp->next = nullptr;
    tail = tmp;
  }

  /**@}*/

  /**
  * @defgroup Get_group Get Methods
  * @{
  */

  /**
  * @brief Get the element from the head of deque.
  * @return constant reference to data stored in the head element of deque
  */
  data_t const& getHead(void) {
    if (head == nullptr)
      std::cerr << "Cannot get tail element: deque is empty.\n";
    return head->data;
  }

  /**
  * @brief Get the element from the tail of deque.
  * @return constant reference to data stored in the tail element of deque
  */
  data_t const& getTail(void) {
    if (tail == nullptr)
      std::cerr << "Cannot get tail element: deque is empty.\n";
    return tail->data;
  }

  /**@}*/

  /**
  * @defgroup Other_group Other Methods
  * @{
  */

  /**
  * @brief Check whether deque contains any elements or not.
  * @return true, if deque is empty; otherwise - false
  */
  bool isEmpty(void) { return head == nullptr; }

  /**
  * @brief Get number of elements that deque consists of.
  * @return number of deque elements
  */
  int size(void) {
    elem* tmp = head;
    int count = 0;

    while (tmp != nullptr) {
      count++;
      tmp = tmp->next;
    }

    return count;
  }

  /**
  * @brief Print all elements of deque according to format: "< data_1 data_2 ... data_n >".
  */
  void print(void) {
    elem* tmp = head;
      
    std::cout << "< ";

    while (tmp != nullptr) {
      std::cout << tmp->data << " ";
      tmp = tmp->next;
    }

    std::cout << ">" << std::endl;
  }

  /**
  * @brief Get a string of all deque elements according to format: "< data_1 data_2 ... data_n >".
  * 
  * This one is weird, but I needed it for testing.
  * 
  * @return string made of data of deque elements
  */
  std::string str(void) {
    std::stringstream ss;

    elem* tmp = head;

    ss << "< ";
    while (tmp != nullptr) {
      ss << tmp->data << " ";
      tmp = tmp->next;
    }
    ss << ">";

    return ss.str();
  }

  /**@}*/

  /**
  * @defgroup Operators_group Operators
  * @{
  */

  /**
  * @brief Assignment operator, that uses copy semantics.
  * @param other - constant reference to a another deque
  */
  Deque& operator=(Deque const& other) {

    if (&other == this)
      return *this;

    clear();

    elem* tmp = other.head;
    while (tmp != nullptr) {      
      try {
        pushTail(tmp->data);
      }
      catch (int) {
        return *this;
      }
      tmp = tmp->next;
    }

    return *this;
  }

  /**
  * @brief Assignment operator, that uses move semantics.
  * @param other - constant reference to another deque
  */
  Deque& operator=(Deque&& other) {

    if (&other == this)
      return *this;

    clear();

    this->head = other.head;
    this->tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;

    return *this;
  }

  /**@}*/
};

#endif // DEQUE_H_INCLUDED