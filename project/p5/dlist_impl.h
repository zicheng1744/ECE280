#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

#include "dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const
{
    return first == nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op)
{
    node *np = new node;
    np->op = op;
    np->prev = nullptr;
    np->next = first;
    if (first == nullptr)
    {
        first = np;
        last = np;
    }
    else
    {
        first->prev = np;
        first = np;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *np = new node;
    np->op = op;
    np->prev = last;
    np->next = nullptr;
    if (last == nullptr)
    {
        first = np;
        last = np;
    }
    else
    {
        last->next = np;
        last = np;
    }
}

template <class T>
T *Dlist<T>::removeFront()
{
    if (isEmpty())
    {
        throw emptyList();
    }
    node *victim = first;
    T *result = victim->op;
    first = victim->next;
    if (first == nullptr)
    {
        last = nullptr;
    }
    else
    {
        first->prev = nullptr;
    }
    delete victim;
    return result;
}

template <class T>
T *Dlist<T>::removeBack()
{
    if (isEmpty())
    {
        throw emptyList();
    }
    node *victim = last;
    T *result = victim->op;
    last = victim->prev;
    if (last == nullptr)
    {
        first = nullptr;
    }
    else
    {
        last->next = nullptr;
    }
    delete victim;
    return result;
}

template <class T>
Dlist<T>::Dlist()
{
    first = nullptr;
    last = nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l)
{
    first = nullptr;
    last = nullptr;
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l)
{
    if (this != &l)
    {
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

template <class T>
void Dlist<T>::removeAll()
{
    while (!isEmpty())
    {
        delete removeFront();
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l)
{
    node *np = l.first;
    while (np != nullptr)
    {
        T *op = new T(*np->op);
        insertBack(op);
        np = np->next;
    }
}

#endif // __DLIST_IMPL_H__