#include "list.h"
#include "level.h"

List::List():m_size(0)
{}

Level *List::getNext(Level *lvl)
{
    auto currElem = start;
    while (currElem->currLevel != lvl && currElem->next != nullptr){
        currElem = currElem->next;
    }
    return currElem->next->currLevel;
}

Level *List::getPrev(Level *lvl)
{
    auto currElem = start;
    while (currElem->currLevel != lvl && currElem->next != nullptr){
        currElem = currElem->next;
    }
    return currElem->prev->currLevel;
}

void List::push_back(Level *lvl)
{
    Element* tmp = new Element{lvl, nullptr, nullptr};
    if(empty()){
        start = tmp;
        m_size++;
        return;
    }
    auto currElem = start;
    while (currElem->next != nullptr){
        currElem = currElem->next;
    }
    tmp->prev = currElem;
    currElem->next = tmp;
    m_size++;
}

void List::push_front(Level *lvl)
{
    Element* tmp = new Element{lvl, nullptr,nullptr};
    if (empty()){
        start = tmp;
        m_size++;
        return;
    }
    tmp->next = start;
    start->prev = tmp;
    start = tmp;
    m_size++;
}

void List::pop_back()
{
    if(empty()) return;
    if (start == nullptr)
    {
        throw std::invalid_argument("List is empty");
        return;
    }
    if (start->next==nullptr){
        delete start;
        start=nullptr;
        m_size--;
        return;
    }
    auto currElem = start;
    while(currElem->next->next != nullptr){
        currElem = currElem->next;
    }
    delete currElem->next;
    currElem->next = nullptr;
    m_size--;
}

void List::pop_front()
{
    if (empty()) return;
    if (start==nullptr){
        throw std::invalid_argument("List is empty");
        return;
    }
    auto tmp = start;
    start = start->next;
    start->prev = nullptr;
    delete tmp;
    m_size--;
}

bool List::empty()
{
    return m_size == 0;
}

std::size_t List::size()
{
    return m_size;
}

void List::remove(Level *lvl)
{
    if(empty()) return;
    if (start==nullptr){
        throw std::invalid_argument("List is empty");
        return;
    }

    auto currElem = start;
    while (currElem->next != nullptr){
        auto tmp = currElem->next;
        if (currElem->currLevel == lvl){
            currElem->prev->next = currElem->next;
            currElem->next->prev = currElem->prev;
            m_size--;
            delete currElem;
        }
        currElem = tmp;
    }

}

List::iterator List::begin()
{
    if(empty()) return iterator(nullptr);
    return iterator(start);
}

List::iterator List::end()
{
    return iterator(new Element{nullptr, nullptr, nullptr});
}



List::iterator &List::iterator::operator++()
{
    if(ptr->next == nullptr){
        throw std::invalid_argument("Error!");
    }
    else{
        ptr=ptr->next;
    }
    return *this;
}

List::iterator& List::iterator::operator--() noexcept
{

    if(ptr->prev == nullptr){
        throw std::invalid_argument("Error!");
    }
    else{
        ptr=ptr->prev;
    }
    return *this;
}

Level *&List::iterator::operator*()
{
    if(ptr->currLevel == nullptr){
        throw std::invalid_argument("Error!");
    }
    return ptr->currLevel;
}

bool List::iterator::operator==(const iterator &i)
{
    return ptr->currLevel == i.ptr->currLevel;
}

bool List::iterator::operator!=(const iterator &i)
{
    return ptr->currLevel != i.ptr->currLevel;
}
