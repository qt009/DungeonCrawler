#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <exception>
using std::size_t;
class Level;
class List
{
private:
    struct Element{
        Element(Level* lvl, Element* Prev, Element* Next): currLevel(lvl), prev(Prev), next(Next){};
        Level* currLevel = nullptr;
        Element* prev = nullptr;
        Element* next  = nullptr;
    };
    Element* start = nullptr;
    int m_size;
public:
    List();
    Level* getNext(Level* lvl);
    Level* getPrev(Level* lvl);
    void push_back(Level* lvl);
    void push_front(Level* lvl);
    void pop_back();
    void pop_front();
    bool empty();
    std::size_t size();
    int& back();
    void remove(Level* lvl);
    friend class iterator;
    class iterator{
    private:
        Element* ptr = nullptr;
    public:

        iterator(Element* e) noexcept :
            ptr(e){}

        iterator& operator=(Element* pElem);
        iterator &operator++();
        //iterator& operator++(int);
        iterator& operator--() noexcept;
        Level*& operator*();
        bool operator==(const iterator& i);
        bool operator!=(const iterator& i);
        Level* getNextLevel(){
            if(ptr->next == nullptr){
                return nullptr;
            }
            return ptr->next->currLevel;
        }

        Element *getPtr() const;
        void setPtr(Element *newPtr);
    };
    iterator begin();
    iterator end();
};

#endif // LIST_H
