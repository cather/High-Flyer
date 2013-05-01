#ifndef MyLIST_H
#define MyLIST_H
#include <stdexcept>
#include <iostream>
using namespace std;

/** An Item for each element stored in the linked list*/
template <typename T>
struct Item {
  T val;
  Item<T>* next;
};

/** A linked list data structure*/
template <typename T>
class MyList {
 public:
  MyList();
  T& operator[](int loc);
  ~MyList();
  bool empty() const;
  int size() const;
  void push_back(const T& new_val);
  void pop(int loc);
  
  void pop_front();
  T& peek_front() const;
  T& at(int loc) const;
  bool remove(const T& val);
  void clear();
  void insert(int loc, T val);
  
  int found(const T& val); // returns where the value was found in the list
  
 private:
  Item<T>* getNodeAt(int loc) const;

 private:
  /** The first item in the linked list*/
  Item<T>* head_;
};

/** Constructor*/
template <typename T>
MyList<T>::MyList()
{
    head_ = NULL;
}

/** Destructor*/
template <typename T>
MyList<T>::~MyList()
{
  clear();
}

/** Bracket operator serves as at() function*/
template <typename T>
T& MyList<T>::operator[](int loc)
{
    return at(loc);
}

/** Boolean function that returns true if list is empty, false otherwise*/
template <typename T>
bool MyList<T>::empty() const
{
    if (head_ == NULL)
        return true;
    else
        return false;
}

/** Function that returns how many elements are in the list*/
template <typename T>
int MyList<T>::size() const
{
    int counter = 0;
    if (head_ != NULL)
    {    
        Item<T>* copy = head_;
        while (copy->next != NULL)
        {
            copy = copy->next;
            counter++;
        }
        counter++;
    }
    return counter;
}

/** Function that returns the Item pointer at a specific location in the list
  @param loc the location in the list whose Item pointer will be returned
*/
template <typename T>
Item<T>* MyList<T>::getNodeAt(int loc) const
{

    if (loc < 0 || loc > size())
        throw std::invalid_argument("Bad location");
    Item<T>* copy = head_;
    while (copy->next != NULL && loc > 0)
    {
        copy = copy->next;
        loc--;
    }
    
    if (copy == NULL)
        throw std::invalid_argument("Bad location");
            
    return copy;
}

/** Fnction that adds an element to the end of the list
  @param new_val the value of the element to be added to the list
*/
template <typename T>
void MyList<T>::push_back(const T& new_val)
{
    Item<T>* newptr = new Item<T>;
    newptr->val =  new_val;
    newptr->next = NULL;
    
    // if the list is empty
    if (head_ == NULL)
        head_ = newptr;
        
    // if not empty
    else
    {
        Item<T>* copy = head_;
        while (copy->next != NULL)
            copy = copy->next;
            
        copy->next = newptr;
    }    
}

/** Function that removes the first element in the list*/
template <typename T>
void MyList<T>::pop_front()
{
    if ( !empty() )
    {
        Item<T>* copy = head_;
        head_ = head_->next;
        delete copy;
    }
}

/** Function that returns the value of the first element in the list
*/
template <typename T>
T& MyList<T>::peek_front() const
{
    if (head_ != NULL)
        return head_->val;
    else
        throw std::invalid_argument("List Empty");
}

/** Function that moves the first element with the given value in the list
  @param val the value that is searched for and whose Item will be removed from the lsit
*/
template <typename T>
bool MyList<T>::remove(const T& val)
{
    int loc = found(val);
    if (loc != -1)
    {
        pop(loc);
        return true;
    }
    else
        return false;
}

/** Function that returns the value at a specific location in the list
  @param loc the location in the list whose value will be returned
*/
template <typename T>
T& MyList<T>::at(int loc) const
{        
    Item<T>* copy = getNodeAt(loc);
    return copy->val;
}

/** Function that deletes all elements in the list*/
template <typename T>
void MyList<T>::clear()
{
  while(head_ != NULL){
    //cout << "Deleting node with value = " << head_->val << endl;
    Item<T> *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  
  head_ = NULL;
}

/** Function that inserts a specified value into a specified location in the list
  @param loc the location in the list where the value will be inserted
  @param val the value to be inserted
*/
template <typename T>
void MyList<T>::insert(int loc, T val)
{

    Item<T>* newptr = new Item<T>;
    newptr->val = val;
    
    if (loc >= size() )
    {
        push_back(val);
        delete newptr;
    }
    else if (loc == 0)
    {
        Item<T>* copy = head_;
        head_ = newptr;
        newptr->next = copy;
    }
    else
    {
        Item<T>* copy = head_;
        
        // moves to correct location in linked list
        while (loc > 0)
        {
            copy = copy->next;
            loc--;
        }
        
        // unless it's the last item in the ilst        
        if (copy != NULL)
        {
            Item<T>* temp = copy;
            copy = newptr;
            newptr->next = temp->next;
        }
    }
    
}

/** Function that removes the item at the given location in the list
  @param loc the location in the list whose Item to delete
*/
template <typename T>
void MyList<T>::pop(int loc)
{
    if (loc > size())
        throw std::invalid_argument("Invalid size");
    else if (loc == 0)
        pop_front();
    else
    {    
    Item<T>* temp = getNodeAt(loc-1);
    Item<T>* copy = temp->next;
    
    temp->next = temp->next->next;
    
    delete copy;
    }
}

/** Function that returns the location that a specified value is in the list
  @param val the value searched for in the list
*/
template <typename T>
int MyList<T>::found(const T& val)
{
    Item<T>* copy = head_;
    bool inList = false;
    int loc = 0;
    while (!inList && copy != NULL)
    {
        if (copy->val == val)
            inList = true;
        else
        {
            copy = copy->next;
            loc++;
        }
    }
    
    if (!inList) 
        return -1;    
    else
        return loc;

}

#endif
