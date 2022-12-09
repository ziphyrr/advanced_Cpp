#pragma once // NOLINT
#include <memory>
#include <initializer_list>
#include <stdio.h>
#include <iostream>

template <class T>
class Set {
    class Node;
    public:
        class iterator;
        friend class iterator;

        // Описания согласно пунктам дз:
        // 1. Конструктор, оператор присваивания и деструктор

        Set();
        template <class InputIt>
        Set(InputIt begin, InputIt end);
        Set(std::initializer_list<T> l);
        Set(const Set &rhs);
        ~Set();
        Set &operator=(const Set &rhs);

        // 2. Итератор
        iterator begin() const;
        iterator end() const;

        class iterator {
            public:
                friend class Set;

                iterator();
                iterator(const iterator &);
                iterator(iterator &&);

                iterator &operator=(const iterator &);
                iterator &operator=(iterator &&);

                iterator &operator++();
                iterator operator++(int);

                iterator &operator--();
                iterator operator--(int);

                const T *operator->() const;
                const T &operator*() const;

                bool operator!=(const iterator &) const;
                bool operator==(const iterator &) const;

            private:
                const Node *_cur = nullptr;
                iterator(const Node *v);
        };

        // 3. методы insert и erase
        void insert(const T &key);
        void erase(const T &key);

        // 4. методы size, empty, find и lower_bound
        size_t size() const;
        bool empty() const;

        iterator find(const T &key) const;
        iterator lower_bound(const T &key) const;
    private:
        struct Node;
        struct KeyNode;

        Node *_root;
        Node past_the_last;
        size_t _size;

        struct Node {
            int height = 1;

            Node *prev = nullptr;
            Node *next = nullptr;

            Node *left = nullptr;
            Node *right = nullptr;
        };

        struct KeyNode : Node {
            T key;
            KeyNode(const T &input_key) : key(input_key) {}
        };

        void _delete_tree(Node *v);

        void _insert(Node *&v, const T &key);
        void _erase(Node *&v, const T &key, Node *p);

        void _fix_node_height(Node *v);
        int _get_node_balance(Node *v);
        void _balance_node(Node *&v);

        void _node_swap(Node *v1, Node *p1, Node *v2, Node *p2);
};

// конструктор по умолчанию
template <class T>
Set<T>::Set()
    : _root(nullptr)
    , _size(0) {

    past_the_last.next = &past_the_last;
    past_the_last.prev = &past_the_last;
}

// конструктор через пару итераторов
template <class T>
template <class InputIt>
Set<T>::Set(InputIt begin, InputIt end)
    : _root(nullptr)
    , _size(0) {

    past_the_last.next = &past_the_last;
    past_the_last.prev = &past_the_last;

    for (InputIt it = begin; it != end; ++it) {
        insert(*it);
    }
}

//конструктор через лист
template <class T>
Set<T>::Set(std::initializer_list<T> l)
    : _root(nullptr)
    , _size(0) {

    past_the_last.next = &past_the_last;
    past_the_last.prev = &past_the_last;

    for (const T &elem : l) {
        insert(elem);
    }
}

//конструктор копирования
template <class T>
Set<T>::Set(const Set &rhs)
    : _root(nullptr)
    , _size(0) {

    past_the_last.next = &past_the_last;
    past_the_last.prev = &past_the_last;

    for (const T &elem : rhs) {
        insert(elem);
    }
}

// деструктор
template <class T>
Set<T>::~Set() {
    _delete_tree(_root);
}

template <class T>
void Set<T>::_delete_tree(Node *v) {
    if (v == nullptr) {
        return;
    }

    _delete_tree(v->left);
    _delete_tree(v->right);

    delete static_cast<KeyNode *> (v);
}

// оператор присваивания
template <class T>
Set<T> &Set<T>::operator=(const Set &rhs) {
    if (this == &rhs) {
        return *this;
    }

    if (rhs.empty()) {
        _delete_tree(_root);
        _root = nullptr;
        _size = 0;

        past_the_last.next = &past_the_last;
        past_the_last.prev = &past_the_last;
        return *this;
    }

    Set tmp_set{ rhs };
    _delete_tree(_root);

    _root = tmp_set._root;
    _size = tmp_set._size;

    Node *first = tmp_set.past_the_last.next;
    Node *last = tmp_set.past_the_last.prev;

    past_the_last.next = first;
    past_the_last.prev = last;
    first->prev = &past_the_last;
    last->next = &past_the_last;

    tmp_set._root = nullptr;
    return *this;
}

// методы begin и end
template <class T>
typename Set<T>::iterator Set<T>::begin() const {
    return iterator(past_the_last.next);
}

template <class T>
typename Set<T>::iterator Set<T>::end() const {
    return iterator(&past_the_last);
}

// методы insert и erase
template <class T>
void Set<T>::insert(const T &key) {
    if (_root == nullptr) {
        _root = new KeyNode(key);
        _root->next = &past_the_last;
        _root->prev = &past_the_last;
        past_the_last.next = _root;
        past_the_last.prev = _root;

        _size++;
    } else {
        _insert(_root, key);
    }
}

template <class T>
void Set<T>::erase(const T &key) {
    _erase(_root, key, nullptr);
}

// методы size, empty, find и lower_bound
template <class T>
size_t Set<T>::size() const {
    return _size;
}

template <class T>
bool Set<T>::empty() const {
    return (_size == 0);
}

template <class T>
typename Set<T>::iterator Set<T>::find(const T &key) const {
    Node *v = _root;

    while (v != nullptr) {
        const T &current_key = static_cast<KeyNode *>(v)->key;
        if (key < current_key) {
            v = v->left;
        } else if (current_key < key) {
            v = v->right;
        } else {
            return iterator(v);
        }
    }
    return end();
}


template <class T>
typename Set<T>::iterator Set<T>::lower_bound(const T &key) const {
    Node *v = _root;
    Node *closest = nullptr;


    while (v != nullptr) {
        const T &current_key = static_cast<KeyNode *>(v)->key;

        if (key < current_key) {
            closest = v;
            v = v->left;
        } else if (current_key < key) {
            v = v->right;
        } else {
            return iterator(v);
        }
    }

    if (closest == nullptr) {
        return end();
    } else {
        return iterator(closest);
    }
}

// private методы
template <class T>
void Set<T>::_insert(Node *&v, const T &key) {
    const T &current_key = static_cast<KeyNode *>(v)->key;

    if (!(current_key < key) && !(key < current_key)) { // current_key == key
        return;
    }

    if (current_key < key) {
        if (v->right != nullptr) {
            _insert(v->right, key);
        } else {
            Node *new_node = new KeyNode(key);
            Node *new_node_prev = v;
            Node *new_node_next = v->next;

            v->right = new_node;

            new_node_prev->next = new_node;
            new_node->prev = new_node_prev;
            new_node->next = new_node_next;
            new_node_next->prev = new_node;

            _size++;
        }
    } else {
        if (v->left != nullptr) {
            _insert(v->left, key);
        } else {
            Node *new_node = new KeyNode(key);
            Node *new_node_prev = v->prev;
            Node *new_node_next = v;

            v->left = new_node;

            new_node_prev->next = new_node;
            new_node->prev = new_node_prev;
            new_node->next = new_node_next;
            new_node_next->prev = new_node;

            _size++;
        }

    }
    _fix_node_height(v);
    _balance_node(v);
}

template <class T>
void Set<T>::_erase(Node *&v, const T &key, Node *p) {
    Node *cur = v;

    if (cur == nullptr) {
        return;
    }

    T &current_key = static_cast<KeyNode *>(v)->key;

    if (!(current_key < key) && !(key < current_key)) {
        if (cur->left == nullptr) {
            v = cur->right;

            _fix_node_height(v);

            Node *cur_prev = cur->prev;
            Node *cur_next = cur->next;

            cur_prev->next = cur_next;
            cur_next->prev = cur_prev;

            _size--;

            delete cur;
            return;
        }
        if (cur->right == nullptr) {
            v = cur->left;

            _fix_node_height(v);

            Node *cur_prev = cur->prev;
            Node *cur_next = cur->next;

            cur_prev->next = cur_next;
            cur_next->prev = cur_prev;

            _size--;

            delete cur;
            return;
        }
        if (_get_node_balance(cur) > 0) {
            Node *to_swap = cur->right;
            Node *to_swap_parent = cur;

            while (to_swap->left != nullptr) {
                to_swap_parent = to_swap;
                to_swap = to_swap->left;
            }

            _node_swap(cur, p, to_swap, to_swap_parent);
            _erase(v->right, key, v);
            _fix_node_height(v);
            return;
        } else {
            Node *to_swap = cur->left;
            Node *to_swap_parent = cur;

            while (to_swap->right != nullptr) {
                to_swap_parent = to_swap;
                to_swap = to_swap->right;
            }

            _node_swap(cur, p, to_swap, to_swap_parent);
            _erase(v->left, key, v);
            _fix_node_height(v);
            return;
        }
    } else if (key < current_key) {
        _erase(cur->left, key, cur);
        _fix_node_height(cur);
    } else {
        _erase(cur->right, key, cur);
        _fix_node_height(cur);
    }
    _balance_node(v);
}

template <class T>
void Set<T>::_fix_node_height(Node *v) {
    if (v == nullptr)
        return;

    if (v->right == nullptr && v->left == nullptr) {
        v->height = 1;
    } else if (v->left != nullptr) {
        v->height = v->left->height + 1;
    } else if (v->right != nullptr) {
        v->height = v->right->height + 1;
    } else {
        v->height = std::max(v->left->height, v->right->height) + 1;
    }
}

template <class T>
int Set<T>::_get_node_balance(Node *v) {
    if (v == nullptr)
        return 0;

    if (v->right == nullptr && v->left == nullptr) {
        return 0;
    } else if (v->right != nullptr) {
        return v->right->height;
    } else if (v->left != nullptr) {
        return -(v->left->height);
    } else {
        return v->right->height - v->left->height;
    }
}

template <class T>
void Set<T>::_balance_node(Node *&v) {
    if (v == nullptr)
        return;

    Node *cur = v;

    if (_get_node_balance(cur) == -2) {
        Node *cur_left = cur->left;
        if (_get_node_balance(cur_left) > 0) {
            Node *cur_left_right = cur_left->right;

            v = cur_left_right;

            cur->left = cur_left_right->right;
            cur_left->right = cur_left_right->left;
            cur_left_right->left = cur_left;
            cur_left_right->right = cur;

            _fix_node_height(cur_left);
            _fix_node_height(cur);
            _fix_node_height(cur_left_right);
        } else {
            v = cur_left;

            Node *cur_left_right = cur_left->right;

            cur_left->right = cur;
            cur->left = cur_left_right;

            _fix_node_height(cur);
            _fix_node_height(cur_left);
        }
    } else if (_get_node_balance(cur) == 2) {
        Node *cur_right = cur->right;

        if (_get_node_balance(cur_right) < 0) {
            Node *cur_right_left = cur_right->left;

            v = cur_right_left;

            cur->right = cur_right_left->left;
            cur_right->left = cur_right_left->right;
            cur_right_left->right = cur_right;
            cur_right_left->left = cur;

            _fix_node_height(cur_right);
            _fix_node_height(cur);
            _fix_node_height(cur_right_left);
        } else {
            v = cur_right;

            Node *cur_right_left = cur_right->left;

            cur_right->left = cur;
            cur->right = cur_right_left;

            _fix_node_height(cur);
            _fix_node_height(cur_right);
        }
    }
}

template <class T>
void Set<T>::_node_swap(Node *v1, Node *p1, Node *v2, Node *p2) {
    if (p2 == nullptr || p1 == v2) {
        _node_swap(v2, p2, v1, p1);
        return;
    }

    if (p2 == v1) {
        bool flg1 = (p1 != nullptr) && (p1->left == v1);

        Node *v2_left = v2->left;
        Node *v2_right = v2->right;

        if (v1->right == v2) {
            Node *v1_left = v1->left;

            v2->left = v1_left;
            v2->right = v1;
            v1->left = v2_left;
            v1->right = v2_right;
        } else {
            Node *v1_right = v1->right;

            v1->left = v2_left;
            v1->right = v2_right;
            v2->left = v1;
            v2->right = v1_right;
        }
        if (p1 == nullptr) {
            _root = v2;
        } else {
            if (flg1 == 1) {
                p1->left = v2;
            } else {
                p1->right = v2;
            }
        }
    } else {
        Node *v1_left = v1->left;
        Node *v1_right = v1->right;
        Node *v2_left = v2->left;
        Node *v2_right = v2->right;

        bool flg2 = (p1 != nullptr) && (p1->left == v1);
        bool flg3 = (p2->left == v2);

        if (p1 == nullptr) {
            _root = v2;
        } else {
            if (flg2 == 1) {
                p1->left = v2;
            } else {
                p1->right = v2;
            }
        }

        if (flg3 == 1) {
            p2->left = v1;
        } else {
            p2->right = v1;
        }

        v2->left = v1_left;
        v2->right = v1_right;
        v1->left = v2_left;
        v1->right = v2_right;
    }
}

// методы итератора
template <class T>
Set<T>::iterator::iterator() = default;

template <class T>
Set<T>::iterator::iterator(const iterator &) = default;

template <class T>
Set<T>::iterator::iterator(iterator &&) = default;

template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator=(const iterator &) = default;

template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator=(iterator &&) = default;

template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator++() {
    _cur = _cur->next;
    return *this;
}

template <class T>
typename Set<T>::iterator Set<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <class T>
typename Set<T>::iterator  &Set<T>::iterator::operator--() {
    _cur = _cur->prev;
    return *this;
}

template <class T>
typename Set<T>::iterator Set<T>::iterator::operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
}

template <class T>
const T *Set<T>::iterator::operator->() const {
    return &**this;
}

template <class T>
const T &Set<T>::iterator::operator*() const {
    return static_cast<const KeyNode *>(_cur)->key;
}

template <class T>
Set<T>::iterator::iterator(const Node *v)
    : _cur(v)
{}

template <class T>
bool Set<T>::iterator::operator!=(const iterator &rhs) const {
    return (_cur != rhs._cur);
}

template <class T>
bool Set<T>::iterator::operator==(const iterator &rhs) const {
    return (_cur == rhs._cur);
}
