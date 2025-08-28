#ifndef XLL_TPP
#define XLL_TPP

#include "XLL.hpp"

template <typename T>
Node* XorLinkedList<T>::XOR(const Node *rhs, const Node *lhs) {
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(lhs)^reinterpret_cast<uintptr_t>(rhs));
}

template <typename T>
XorLinkedList<T>::Node::Node(const T &val, Node *both) : m_val(val), m_both(both) {}

template <typename T>
XorLinkedList<T>::Node::Node(T &&val, Node *both) noexcept : m_val(std::move(val)), m_both(both) {}

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
    m_tail = other.m_tail;
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
    return iterator (nullptr, m_head);
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::begin() const noexcept {
    return const_iterator (nullptr, m_head);
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::cbegin() const noexcept {
    return const_iterator (nullptr, m_head);
}



template <typename T>
typename XorLinkedList<T>::iterator XorLinkedList<T>::end() noexcept {
    return iterator (m_tail, nullptr);
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::end() const noexcept {
    return const_iterator (m_tail, nullptr);
}

template <typename T>
typename XorLinkedList<T>::const_iterator XorLinkedList<T>::cend() const noexcept {
    return const_iterator(m_tail, nullptr);
}



template <typename T>
typename XorLinkedList<T>::reverse_iterator XorLinkedList<T>::rbegin() noexcept {
    return reverse_iterator(nullptr, m_tail);
}

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::rbegin() const noexcept {
    return const_reverse_iterator(nullptr, m_tail);
}

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::crbegin() const noexcept {
    return const_reverse_iterator(nullptr, m_tail);
}



template <typename T>
typename XorLinkedList<T>::reverse_iterator XorLinkedList<T>::rend() noexcept {
    return reverse_iterator(m_head, nullptr);
}

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::rend() const noexcept {
    return const_reverse_iterator(m_head, nullptr);
}

template <typename T>
typename XorLinkedList<T>::const_reverse_iterator XorLinkedList<T>::crend() const noexcept {
    return const_reverse_iterator(m_head, nullptr);
}



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
typename XorLinkedList<T>::size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
}


//modifiers

template <typename T>
void XorLinkedList<T>::clear() noexcept {
    Node* prev = nullptr;
    Node* cur  = m_head;

    while (cur) {
        Node* next = XOR(prev, cur->m_both);
        delete cur;
        prev = cur;
        cur = next;
    }

    m_head = m_tail = nullptr;
    m_size = 0;
}

template <typename T>
typename XorLinkedList<T>::iterator XorLinkedList<T>::insert(XorLinkedList<T>::iterator pos, const T &val) {
    Node* prev = pos.m_prev;
    Node* cur  = pos.m_cur;

    Node* n = new Node(XOR(prev, cur), val);

    prev->m_both = XOR(XOR(prev->m_both, cur), n);

    cur->m_both = XOR(XOR(cur->m_both, prev), n);

    if (cur == m_head) m_head = n;
    if (!cur) m_tail = n;

    ++m_size;

    return iterator(prev, n);
}

template <typename T>
typename XorLinkedList<T>::iterator XorLinkedList<T>::insert(XorLinkedList<T>::iterator pos, T &&val) {
    Node* prev = pos.m_prev;
    Node* cur  = pos.m_cur;

    Node* n = new Node(XOR(prev, cur), std::move(val));

    prev->m_both = XOR(XOR(prev->m_both, cur), n);

    cur->m_both = XOR(XOR(cur->m_both, prev), n);

    if (cur == m_head) m_head = n;
    if (!cur) m_tail = n;

    ++m_size;

    return iterator(prev, n);
}

iterator insert(const_iterator pos, size_type count, const T &val);

template <typename InputIt>
iterator insert(const_iterator pos, InputIt first, InputIt last);

iterator insert(const_iterator pos, std::initializer_list<T> ilist);


#endif