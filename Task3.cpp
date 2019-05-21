#include <iostream>
#include <iomanip>

using namespace std;

template<typename Key, typename Info>
class AVLTree {
    private:
        struct Node {
            Key key;
            Info info;
            short int balanceFactor;
            Node* right;
            Node* left;
            Node(const Key& _key, const Info& _info): key(_key), info(_info), balanceFactor(0), left(nullptr), right(nullptr) {};
            };
        Node* root;
        short int max(short int a, short int b) const;
        void rotateLeft(Node*& node);
        void rotateRight(Node*& node);
        short int rebalance(Node*& subtree);
        void clear(Node* toRemove);
        void graph(const Node* subgraph, int indent = 0) const;
        bool insert(Node*&, const Key&, const Info&);
        ostream& print(ostream& os, const Node*&) const;
        void print(const Node*&) const;
        bool remove(Node*, Node*);

    public:
        AVLTree();
        ~AVLTree();
        bool insert(const Key&, const Info&);
        bool remove(const Key&);
        const Info& operator[](const Key&) const;
        Info& operator[](const Key&);
        bool keyExists(const Key& key) const;
        void clear();
        void graph() const { graph(root); };
        void print() const { print(const_cast<const Node*&>(root)); cout << endl; };
        void separation();
        ostream& print(ostream& os) const { return print(os, const_cast<const Node*&>(root)); };

        template<typename K, typename I>
        friend ostream& operator<<(ostream&, const AVLTree<K, I>&);
};

template<typename Key, typename Info>
short int AVLTree<Key, Info>::rebalance(Node*& subtree) {
    if(!subtree) {
        return 0;
    }
    short int lheight = rebalance(subtree->left);
    short int rheight = rebalance(subtree->right);
    subtree->balanceFactor = rheight - lheight;
    if(subtree->balanceFactor == 2 && subtree->right->balanceFactor > -1) {
        rotateLeft(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == -2 && subtree->left->balanceFactor < 1) {
        rotateRight(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == 2 && subtree->right->balanceFactor == -1) {
        rotateRight(subtree->right);
        rotateLeft(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == -2 && subtree->left->balanceFactor == 1) {
        rotateLeft(subtree->left);
        rotateRight(subtree);
        return rebalance(subtree);
    }
    return max(lheight, rheight) + 1;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::rotateRight(Node*& node) {
    Node* tmp = node;
    Node* tmp2 = tmp->left;
    tmp->left = tmp->left->right;
    tmp2->right = tmp;
    node = tmp2;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::rotateLeft(Node*& node) {
    Node* tmp = node;
    Node* tmp2 = tmp->right;
    tmp->right = tmp->right->left;
    tmp2->left = tmp;
    node = tmp2;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::graph(const Node* subgraph, int indent) const {
    if(subgraph) {
        graph(subgraph->right, indent + 3);
        std::cout << setw(indent) << " " << subgraph->key<< endl;
        graph(subgraph->left, indent + 3);
    } else {
        std::cout << "\n";
    }
}

template<typename Key, typename Info>
AVLTree<Key, Info>::AVLTree() : root(nullptr) {

}

template<typename Key, typename Info>
AVLTree<Key, Info>::~AVLTree() {
    clear();
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::insert(const Key& key, const Info& info) {
    return insert(root, key, info);
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::insert(Node*& root, const Key& key, const Info& info) {
    if(!root) {
        root = new Node(key, info);
        rebalance(this->root);
        return true;
    }
    if(key > root->key){
        insert(root->right, key, info);
    } else if(key < root->key) {
        insert(root->left, key, info);
    } else {
        root->info = info;
        return true;
    }
    return false;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::clear() {
    clear(root);
    root = nullptr;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::clear(Node* node) {
    if(node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Info>
short int AVLTree<Key, Info>::max(short int a, short int b) const {
     if ( a < b )
        return b;
     return a;
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::keyExists(const Key& key) const {
    Node* node = root;
    while(node) {
        if(key == node->key) return cout<< "Exists" <<endl;
        else if(key > node->key) node = node->right;
        else if(key < node->key) node = node->left;
    }
    cout<< "Does not exist" <<endl;
    return 0;
}

template<typename Key, typename Info>
const Info& AVLTree<Key, Info>::operator[](const Key& key) const {
    Node* node = root;
    while(node) {
        if(key == node->key) return const_cast<const Info&>(node->info);
        else if(key > node->key) node = node->right;
        else if(key < node->key) node = node->left;
    }
    throw "Key Not Found";
}

template<typename Key, typename Info>
Info& AVLTree<Key, Info>::operator[](const Key& key) {
    Node* node = root;
    while(node) {
        if(key == node->key) return node->info;
        else if(key > node->key) node = node->right;
        else if(key < node->key) node = node->left;
    }
    throw "Key has not been found";
}

template<typename Key, typename Info>
ostream& AVLTree<Key, Info>::print(ostream& os, const Node*& node) const {
    if(node) {
        print(os, const_cast<const Node*&>(node->left));
        os << "(" << node->key << ", " << node->info << ")";
        print(os, const_cast<const Node*&>(node->right));
    }
    return os;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::print(const Node*& node) const {
    if(node) {
        print(const_cast<const Node*&>(node->left));
        cout << "(" << node->key << ", " << node->info << ")";
        print(const_cast<const Node*&>(node->right));
    }
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::remove(const Key& key) {
    Node* toDelete = root;
    Node* toDeleteParent = root;

    while(toDelete) {
        if(key < toDelete->key) {
            toDeleteParent = toDelete;
            toDelete = toDelete->left;
        } else if(key > toDelete->key) {
            toDeleteParent = toDelete;
            toDelete = toDelete->right;
        } else if(toDelete->key == key) {
            return remove(toDelete, toDeleteParent);
        }
    }
    return false;
};

template<typename Key, typename Info>
bool AVLTree<Key, Info>::remove(Node* toDelete, Node* toDeleteParent) {
    if(toDelete->left && toDelete->right) {
        Node* toSwap = toDelete->right;
        toDeleteParent = toDelete;
        while (toSwap->left != nullptr) {
            toDeleteParent = toSwap;
            toSwap = toSwap->left;
        }
        toDelete->key = toSwap->key;
        toDelete->info = toSwap->info;
        toDelete = toSwap;
    }

    Node* subtree = toDelete->left;
    if(!subtree)
        subtree = toDelete->right;
    if(!toDeleteParent)
        root = subtree;
    else if(toDeleteParent->left == toDelete)
        toDeleteParent->left = subtree;
    else
        toDeleteParent->right = subtree;

    delete toDelete;
    rebalance(root);
    return true;
};

template<typename Key, typename Info>
ostream& operator<<(ostream& os, const AVLTree<Key, Info>& tree) {
    return tree.print(os);
}

void separation()
{
    for (int i=0;i<100;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    cout<<endl;
}

int main()
{
    AVLTree<int, string> Tree1;
    Tree1.insert(1, "one");
    Tree1.insert(2, "two");
    Tree1.insert(3, "three");
    Tree1.insert(4, "four");
    Tree1.insert(5, "five");
    Tree1.insert(6, "six");
    Tree1.insert(7, "seven");
    Tree1.insert(8, "eight");
    Tree1.insert(9, "nine");
    Tree1.insert(10, "ten");
    Tree1.insert(11, "eleven");
    Tree1.insert(12, "twelve");
    Tree1.insert(13, "thirteen");
    Tree1.insert(14, "fourteen");
    Tree1.insert(15, "fifteen");
    Tree1.insert(16, "sixteen");
    Tree1.insert(17, "seventeen");
    Tree1.insert(18, "eighteen");
    Tree1.insert(19, "nineteen");
    Tree1.insert(20, "twenty");

    cout << "Tree1 graph:" << endl;

    Tree1.graph();

    cout << "Tree1 (print function):" << endl;

    Tree1.print();

    separation();

    Tree1.remove(8);
    Tree1.remove(4);
    Tree1.remove(6);
    Tree1.remove(9);
    Tree1.remove(18);
    Tree1.remove(12);

    cout << "Tree1 graph after some removes:" << endl;

    Tree1.graph();

    cout << "Tree1 (print function):" << endl;

    Tree1.print();

    separation();

    AVLTree<string, string> Tree2;

    Tree2.insert("P","Poland" );
    Tree2.insert("G", "Germany");
    Tree2.insert("I", "Italy");
    Tree2.insert("F", "France");
    Tree2.insert("S", "Spain");
    Tree2.insert("A", "Austria");
    Tree2.insert("E", "Estonia");
    Tree2.insert("C", "Croatia");

    cout << "Tree2 graph:" << endl;

    Tree2.graph();

    cout << "Tree2 (print function):" << endl;

    Tree2.print();

    separation();

    Tree2.clear();

    Tree2.print();

    cout << "Tree2 (after using function clear):" << endl;

    cout<<endl;

    separation();

    cout << "Existing of specific keys in Tree1 (5 which should exists and 50 which should not exist):" << endl;

    cout<<endl;

    cout<< "Key 5" <<endl;

    cout << Tree1.keyExists(5) << endl;

    cout<<endl;

    cout<< "Key 50" <<endl;

    cout << Tree1.keyExists(50) << endl;

    return 0;
}
