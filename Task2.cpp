#include <iostream>
using namespace std;

template<typename Key, typename Info>
class BiRing {  //allowes duplicates
        struct Node;
    public:
        class const_iterator;
        class iterator;

        BiRing();
        BiRing(const BiRing&);
        ~BiRing();
        BiRing& operator=(const BiRing&);
        void clear(); //does not clear the sentinel
        iterator begin() const;
        iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
        void push_front(Key, Info);
        void push_back(Key, Info);
        void pop_front();
        void pop_back();
        iterator find_key(Key key, int pos = 1) const;
        iterator find_info(Info info, int pos = 1) const;
        iterator add(Key key, Info info, const iterator& after); //what we add and after what is in arguments
        iterator add(Key key, Info info, Key after, int pos = 1);
        iterator remove(Key key, int pos = 1); //returns iterator to next element after removed one, does nothing when the value is invalid
        iterator remove(const iterator&);
        template<typename K, typename I>
        friend std::ostream& operator<<(std::ostream&, const BiRing<K, I>&);

        class iterator { //when there is no arguments, begin() and end() points to themselves with next and previous iterators
            //after .end()++; goes to next first element
            friend class BiRing;
            Node* node;
            iterator(Node* node) { this->node = node; };
            public:
                iterator() { node = nullptr; };
                iterator& operator=(const iterator& s) { node = s.node; return *this; };
                iterator& operator++()       { node = node->next; return *this; };
                iterator& operator++(int)    { node = node->next; return *this; };
                iterator& operator--()       { node = node->prev; return *this; };
                iterator& operator--(int)    { node = node->prev; return *this; }
                iterator& operator+=(unsigned int n) { while(n--) { ++(*this);} return *this; };
                iterator& operator-=(unsigned int n) { while(n--) { --(*this);} return *this; };
                bool operator==(const iterator& x) const { return node == x.node; };
                bool operator!=(const iterator& x) const { return node != x.node; };
                iterator add(Key key, Info info); //what we add and after what in arguments
                iterator remove(); //what we add and after what in arguments
                const Key& key() const { return node->key; };
                Info& info() const { return node->info; };
        };
        class const_iterator {
            friend class BiRing;
            Node* node;
            const_iterator(Node* node) { this->node = node; };
            public:
                const_iterator() { node = nullptr; };
                const_iterator& operator=(const const_iterator& s) { node = s.node; return *this; };
                const_iterator& operator++() { node = node->next; return *this; };
                const_iterator& operator++(int) { node = node->next; return *this; };
                const_iterator& operator--() { node = node->prev; return *this; };
                const_iterator& operator--(int) { node = node->prev; return *this; }
                const_iterator& operator+=(unsigned int n) { for(;n--;) {++(*this);} return *this; };
                const_iterator& operator-=(unsigned int n) { for(;n--;) {--(*this);} return *this; };
                bool operator==(const const_iterator& x) const { return node == x.node; };
                bool operator!=(const const_iterator& x) const { return node != x.node; };
                const Key& key() const { return node->key; };
                const Info& info() const { return node->info; };
        };
    private:
        iterator sentinel;
        struct Node {
            Key key;
            Info info;
            Node* next;
            Node* prev;
            Node() : next(this), prev(this) {};
        };
};


template<typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const BiRing<Key, Info>& x) {
    os << "[";
    for(typename BiRing<Key, Info>::iterator i = x.begin(); i != x.end(); ++i) {
        os << "(" << i.key() << "," << i.info() << ")";
    }
    os << "]";
    return os;
}

template<typename Key, typename Info>
BiRing<Key, Info>::BiRing() {
    sentinel.node = new Node();
    sentinel.node->next = sentinel.node;
    sentinel.node->prev = sentinel.node;
}

template<typename Key, typename Info>
BiRing<Key, Info>::BiRing(const BiRing& toCopy) {
    sentinel = new Node();
    for(BiRing<Key, Info>::iterator i = toCopy.begin(); i != toCopy.end(); ++i) {
        push_back(i.key(), i.info());
    }
}

template<typename Key, typename Info>
BiRing<Key, Info>::~BiRing() {
    clear();
    delete sentinel.node;
}

template<typename Key, typename Info>
BiRing<Key, Info>& BiRing<Key, Info>::operator=(const BiRing<Key, Info>& toCopy) {
    if(this == &toCopy) return *this;
    clear();
    for(BiRing<Key, Info>::iterator i = toCopy.begin(); i != toCopy.end(); ++i) {
        push_back(i.key(), i.info());
    }
    return *this;
}

template<typename Key, typename Info>
void BiRing<Key, Info>::clear() {
    BiRing<Key, Info>::iterator i = begin();
    while(i != end()) {
        i = remove(i);
    }
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::begin() const {
    return iterator(sentinel.node->next);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::end() const {
    return sentinel;
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::const_iterator BiRing<Key, Info>::cbegin() const {
    return const_iterator(sentinel.node->next);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::const_iterator BiRing<Key, Info>::cend() const {
    return const_iterator(sentinel.node);
}

template<typename Key, typename Info>
void BiRing<Key, Info>::push_back(Key key, Info info) {
    add(key, info, --end());
}

template<typename Key, typename Info>
void BiRing<Key, Info>::push_front(Key key, Info info) {
    add(key, info, begin());
}

template<typename Key, typename Info>
void BiRing<Key, Info>::pop_back() {
    remove(--end());
}

template<typename Key, typename Info>
void BiRing<Key, Info>::pop_front() {
    remove(begin());
}

template<typename Key, typename Info>
typename BiRing<Key, Info>::iterator BiRing<Key, Info>::find_key(Key key, int pos) const {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.key() == key && !--pos) {
            return i;
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::find_info(Info info, int pos) const {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.info() == info && !--pos) {
            return i;
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::add(Key key, Info info, const BiRing<Key, Info>::iterator& after) {
    Node* tmp = new Node();
    tmp->info = info;
    tmp->key = key;
    tmp->next = after.node->next;
    tmp->prev = after.node;
    after.node->next->prev = tmp;
    after.node->next = tmp;
    return iterator(tmp);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::add(Key key, Info info, Key after, int pos) {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.key() == after && !--pos) {
            return add(key, info, i);
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::remove(Key key, int pos) {
    for(BiRing<Key, Info>::iterator i = begin(); i != end(); ++i) {
        if(i.key() == key && !--pos)  {
            return remove(i);
        }
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::remove(const iterator& x) {
    if(x != end()) {
        x.node->next->prev = x.node->prev;
        x.node->prev->next = x.node->next;
        iterator ret;
        ret.node = x.node->next;
        delete x.node;
        return ret;
    }
    return end();
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::iterator::add(Key key, Info info) {
    Node* tmp = new Node();
    tmp->info = info;
    tmp->key = key;
    tmp->next = node->next;
    tmp->prev = node;
    node->next->prev = tmp;
    node->next = tmp;
    return iterator(tmp);
}

template<typename Key, typename Info>
typename BiRing<Key,Info>::iterator BiRing<Key, Info>::iterator::remove() {
    if(this->node->prev == this->node) return iterator(this->node);
    this->node->next->prev = this->node->prev;
    this->node->prev->next = this->node->next;
    iterator ret;
    ret.node = this->node->next;
    delete this->node;
    return ret;
}

int main()//the main body is a rudimentary test
{
    BiRing<int, string> br1;
    cout << br1 << endl;

    br1.push_front(1, "one");
    cout << br1 << endl;

    br1.push_back(2, "two");
    cout << br1 << endl;

    br1.pop_front();
    cout << br1 << endl;

    br1.pop_back();
    cout << br1 << endl;

    BiRing<int, string>::iterator it = br1.begin();
    it = it.add(1, "uno");
    it = it.add(5, "cinque");
    it--;
    it.add(3, "tre");
    it.add(2, "due");
    it += 2;
    it = it.add(4, "quattro");
    cout << br1 << endl;

    BiRing<int, string> br2(br1);

    it -= 3;
    it = it.remove();
    it += 3;
    it = it.remove();
    it -= 2;
    it = it.remove();
    it--;
    it = it.remove();
    it.remove();
    cout << br1 << endl;

    BiRing<int, string>::iterator iv = br2.find_key(3);
    iv.remove();
    iv = br2.find_info("quattro");
    iv.remove();
    cout << br2 << endl;

    br1 = br2;
    cout << br1 << endl;

    return 0;
}
