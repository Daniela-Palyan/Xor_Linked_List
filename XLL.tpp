#ifndef XLL_TPP
#define XLL_TPP

#include "XLL.hpp"

template <typename T>
T* XorLinkedList::XOR(const Node *rhs, const Node *lhs) {
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(rhs)^reinterpret_cast<uintptr_t>(rhs));
}

template <typename T>
XorLinkedList<T>::Node::Node(const T &val, T *both) : m_val(val), m_both(both) {}

template <typename T>
XorLinkedList<T>::Node::Node(T &&val, T *both) noexcept : m_val(std::move(val)), m_both(both) {}

template <typename T>
XorLinkedList<T>::Node::~Node() {}

template <typename T>
XorLinkedList<T>::XorLinkedList(size_type count, const T &val = T()): m_size(count) {
    for (int i = 0; i < count; ++i) {
        push_back(val);
    }
}

template <typename T>
template <typename InputIt>
XorLinkedList<T>::XorLinkedList(InputIt first, InputIt last): XorLinkedList() {
    while (first != last) {
        push_back(*first);
        ++first;
    }
}

template <typename T>
XorLinkedList<T>::XorLinkedList(const XorLinkedList &other): XorLinkedList() {
    for (const_referance v: other) {
        push_back(v);
    }
}

template <typename T>
XorLinkedList<T>::XorLinkedList(XorLinkedList &&other) noexcept : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template <typename T>
XorLinkedList<T>::XorLinkedList(std::initializer_list<T> init) {
    for (const T &v : init) {
        push_back(v);
    }
}

template <typename T>
XorLinkedList<T>::~XorLinkedList() {
    clear();
}


template <typename T>
XorLinkedList<T>& XorLinkedList<T>::operator=(const XorLinkedList<T> &other) {
    if (this == &other) return *this;
    XorLinkedList tmp(other);
    swap(tmp);
    return *this;
}

template <typename T>
XorLinkedList<T>& XorLinkedList<T>::operator=(XorLinkedList<T> &&other) noexcept {
    if (this == &other) return *this;
    clear();
    m_head = other.m_head;
    m_tail = other.m_head;
    m_size = other.m_size;
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;

    return *this;
}


   // element access
template <typename T>
typename XorLinkedList<T>::reference XorLinkedList<T>::front() {
    return m_head->m_val;
}

template <typename T>
typename XorLinkedList<T>::const_reference XorLinkedList<T>::front() const {
    return m_head->m_val;
}
   
template <typename T>
typename XorLinkedList<T>::reference XorLinkedList<T>::back() {
    return m_tail->m_val;
}
   
template <typename T>
typename XorLinkedList<T>::const_reference XorLinkedList<T>::back() const {
    return m_tail->m_val;
}



template <typename T>
typename XorLinkedList<T>::iterator XorLinkedList<T>::begin() noexcept {
    iterator it(nullptr, m_head);
    return it;
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::begin() const noexcept {
    const_iterator it(nullptr, m_head);
    return it;
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::cbegin() const noexcept {
    const_iterator it(nullptr, m_head);
    return it;
}



template <typename T>
typename XorLinkedList<T>::iterator XorLinkedList<T>::end() noexcept {
    iterator it(m_tail, nullptr);
    return it;
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::end() const noexcept {
    const_iterator it(m_tail, nullptr);
    return it;
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::cend() const noexcept {
    const_iterator it(m_tail, nullptr);
    return it;
}



template <typename T>
typename XorLinkedList<T>::reverse_iterator XorLinkedList<T>::rbegin() noexcept {
    
}

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::rbegin() const noexcept;

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::crbegin() const noexcept;



template <typename T>
typename XorLinkedList<T>::reverse_iterator XorLinkedList<T>::rend() noexcept;

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::rend() const noexcept;

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::crend() const noexcept;



//NE DODELANNO
template <typename T>
bool XorLinkedList<T>::empty() const noexcept {
    return m_size == 0;
}

template <typename T>
typename XorLinkedList<T>::size_type XorLinkedList<T>::size() const noexcept {
    return m_size;
}

template <typename T>
typename XorLinkedList<T>::size_type XorLinkedList<T>::max_size() const noexcept {}


template <typename T>
void clear() noexcept;

#endif