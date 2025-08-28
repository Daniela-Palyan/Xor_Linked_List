#ifndef XLL_HPP
#define XLL_HPP


#include <cstdint>
#include <initializer_list>
#include <iterator>


template <typename T>
struct XorLinkedList {
   class Node {
       T m_val;
       Node *m_both;


       explicit Node(const T &val = T(), Node *both = nullptr);
       explicit Node(T &&val, Node *both = nullptr) noexcept;
       ~Node();
   };
public:
   using value_type = T;
   using size_type = size_t;
   using reference = T&;
   using const_reference = const T&;
   using pointer = T*;
   using const_pointer = const T*;


   class iterator;
    class const_iterator;
   class reverse_iterator;
   class const_reverse_iterator;


   // static method for Node::m_both pointer
   static Node *XOR(const Node *rhs, const Node *lhs);


   // Ctors and Dtor
   XorLinkedList() noexcept;
   explicit XorLinkedList(size_type count, const T &val = T());
   template <typename InputIt>
   XorLinkedList(InputIt first, InputIt last);
   XorLinkedList(const XorLinkedList &other);
   XorLinkedList(XorLinkedList &&other) noexcept;
   XorLinkedList(std::initializer_list<T> init);


   ~XorLinkedList();


   // assignment operators
   XorLinkedList &operator=(const XorLinkedList &other);
   XorLinkedList &operator=(XorLinkedList &&other) noexcept;


   // element access
   reference front();
   const_reference front() const;
   reference back();
   const_reference back() const;


   // iterators
   iterator begin() noexcept;
   const_iterator begin() const noexcept;
   const_iterator cbegin() const noexcept;


   iterator end() noexcept;
   const_iterator end() const noexcept;
   const_iterator cend() const noexcept;


   reverse_iterator rbegin() noexcept;
   const_reverse_iterator rbegin() const noexcept;
   const_reverse_iterator crbegin() const noexcept;


   reverse_iterator rend() noexcept;
   const_reverse_iterator rend() const noexcept;
   const_reverse_iterator crend() const noexcept;


   // capacity
   bool empty() const noexcept;
   size_type size() const noexcept;
   size_type max_size() const noexcept;


   // modifiers
   void clear() noexcept;


   iterator insert(const_iterator pos, const T &val);
   iterator insert(const_iterator pos, T &&val);
   iterator insert(const_iterator pos, size_type count, const T &val);
   template <typename InputIt>
   iterator insert(const_iterator pos, InputIt first, InputIt last);
   iterator insert(const_iterator pos, std::initializer_list<T> ilist);
  
   template <typename ...Args>
   iterator emplace(const_iterator pos, Args &&...args);


   iterator erase(iterator pos);
   iterator erase(const_iterator pos);
   iterator erase(iterator first, iterator last);
   iterator erase(const_iterator first, const_iterator last);


   void push_back(const T &val);
   void push_back(T  &&val);


   template <typename ...Args>
   void emplace_back(Args &&...args);


   void pop_back();


   void push_front(const T &val);
   void push_front(T  &&val);


   template <typename ...Args>
   void emplace_front(Args &&...args);   


   void pop_front();


   void resize(size_type count);
   void resize(size_type count, const T &val);


   void swap(XorLinkedList &other) noexcept;


   class const_iterator {
        Node * m_prev;
        Node*m_cur;
    public: 
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = const T*;
      using referance = const T&;

      const_iterator(Node* prev = nullptr, Node* cur = nullptr) : m_prev(prev), m_cur(cur) {}
      //const_iterator(const iterator& other) : m_prev(other.m_prev), m_cur(other.m_cur) {}  

      referance operator*() const { return m_cur->m_val; }
      
      pointer operator->() const { return &m_cur->m_val; }

      const_iterator& operator++() {
        Node* next = XOR(m_prev, m_cur->both);
        m_prev = m_cur;
        m_cur = next;
        return *this;
      }

      const_iterator& operator--() {
        Node* next = XOR(m_cur, m_prev->both);
        m_cur = m_prev;
        m_prev = next;
        return *this;
      }

      const_iterator operator++(int) {
        const_iterator tmp = *this;
        ++(*this);
        return tmp;
      }

      const_iterator operator--(int) {
        const_iterator tmp = *this;
        --(*this);
        return tmp;
      }

      bool operator==(const const_iterator& other) {
        return m_prev == other.m_prev && m_cur == other.m_cur;
      }

      bool operator!=(const const_iterator& other) {
        return !(*this == other);
      }
    };


   class iterator {
      Node* m_prev;
      Node* m_cur;

   public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using referance = T&;

      iterator(Node* prev = nullptr, Node* cur = nullptr): m_prev(prev), m_cur(cur) {}
      //iterator(const iterator& other) : m_prev(other.m_prev), m_cur(other.m_cur) {}


      referance operator*() const { return m_cur->m_val; }

      pointer operator->() const { return &m_cur->m_val; }

      iterator& operator++() {
        Node* next = XOR(m_prev, m_cur->m_both);
        m_prev = m_cur;
        m_cur = next;
        return *this;
      }

      iterator& operator--() {
        Node* next = XOR(m_cur, m_prev->both);
        m_cur = m_prev;
        m_prev = next;
        return *this;
      }

      iterator operator++(int) {
        iterator tmp = *this;
        ++(*this);
        return tmp;
      }

      iterator operator--(int) {
        iterator tmp = *this;
        --(*this);
        return tmp;
      }

      bool operator==(const iterator& other) const {
        return m_cur == other.m_cur && m_prev == other.m_prev;
      }

      bool operator!=(const iterator& other) const {
        return !(*this == other);
      }



      
   };


    class reverse_iterator { 
        Node * m_prev;
        Node* m_cur;
    
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using referance = T&;

        reverse_iterator(Node* prev = nullptr, Node* cur = nullptr) : m_prev(prev), m_cur(cur) {}
        //reverse_iterator(const reverse_iterator& otehr) : m_prev(other.m_prev), m_cur(other.m_cur) {}

        referance operator*() const { return m_cur->m_val; }
        pointer operator->() const { return &m_cur->m_val; }
        
        reverse_iterator& operator++() {
            Node* next = XOR(m_cur, m_prev->m_both);
            m_cur = m_prev;
            m_prev = next;
            return *this;
        }

        reverse_iterator& operator--() {
            Node* next = XOR(m_prev, m_cur->m_both);
            m_prev = m_cur;
            m_cur = next;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator operator--(int) {
            reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const reverse_iterator& other) const {
            return m_prev == other.m_prev && m_cur == other.m_cur;
        }

        bool operator!=(const reverse_iterator& other) const{
            return !(*this == other);
        }
    };

    class const_reverse_iterator { 
        Node* m_prev;
        Node* m_cur;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using referance = const T&;

        const_reverse_iterator(Node* prev = nullptr, Node* cur = nullptr) : m_prev(prev), m_cur(cur) {}
        //const_reverse_iterator(const reverse_iterator& otehr) : m_prev(other.m_prev), m_cur(other.m_cur) {}

        referance operator*() const { return m_cur->m_val; }
        pointer operator->() const { return &m_cur->m_val; }
        
        const_reverse_iterator& operator++() {
            Node* next = XOR(m_cur, m_prev->m_both);
            m_cur = m_prev;
            m_prev = next;
            return *this;
        }

        const_reverse_iterator& operator--() {
            Node* next = XOR(m_prev, m_cur->m_both);
            m_prev = m_cur;
            m_cur = next;
            return *this;
        }

        const_reverse_iterator operator++(int) {
            const_reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_reverse_iterator operator--(int) {
            const_reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const const_reverse_iterator& other) const {
            return m_prev == other.m_prev && m_cur == other.m_cur;
        }

        bool operator!=(const const_reverse_iterator& other) const{
            return !(*this == other);
        }

    };



private:
   Node *m_head;
   Node *m_tail;
   size_type m_size;
};


template <typename T>
bool operator==(const XorLinkedList<T> &lhs, const XorLinkedList<T> &rhs);


template <typename T>
bool operator!=(const XorLinkedList<T> &lhs, const XorLinkedList<T> &rhs);


template <typename T>
bool operator<(const XorLinkedList<T> &lhs, const XorLinkedList<T> &rhs);


template <typename T>
bool operator<=(const XorLinkedList<T> &lhs, const XorLinkedList<T> &rhs);


template <typename T>
bool operator>(const XorLinkedList<T> &lhs, const XorLinkedList<T> &rhs);


template <typename T>
bool operator>=(const XorLinkedList<T> &lhs, const XorLinkedList<T> &rhs);


#endif //XLL_HPP