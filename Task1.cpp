#include <iostream>

using namespace std;

template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    Node<Key, Value>* next;
};

template <typename Key, typename Value>
class List
{
public:
    List();
    List(const List<Key, Value>& copied);
    List<Key, Value>& operator=(const List<Key, Value>& nval);
    ~List();

    void pushBack(Key key, Value value);
    void pushFront(Key key, Value value);
    void addAfter(Key newKey, Value newValue, Key key, int numb = 0);
    void removeFront();
    void removeBack();
    void removeNode(Key key, int numb = 0);

    int size() const;
    void clear();
    void print() const;
    void print(Key key) const;
    void separation();
    bool exists(Key key) const;
    Node<Key, Value>* getHead() const;
private:
    Node<Key, Value>* head;
};

template <typename Key, typename Value>
List<Key, Value>::List(): head(NULL)
{

}

template <typename Key, typename Value>
List<Key, Value>::List(const List<Key, Value>& copied): head(NULL)
{
    Node<Key, Value>* node = copied.head;
    while(node)
    {
        pushBack(node->key, node->value);
        node = node->next;
    }
}

template <typename Key, typename Value>
List<Key, Value>& List<Key, Value>::operator=(const List<Key, Value>& nval)
{
    if (this != &nval)
    {
        clear();
        Node<Key, Value>* node = nval.head;
        while(node)
        {
            pushFront(node->key, node->value);
            node = node->next;
        }
    }
}

template <typename Key, typename Value>
List<Key, Value>::~List()
{
    clear();
}

template <typename Key, typename Value>
void List<Key, Value>::pushBack(Key key, Value value)
{
     Node<Key, Value>* temp = new Node<Key, Value>;
     temp->key = key;
     temp->value = value;
     temp->next = head;
     head = temp;
}

template <typename Key, typename Value>
void List<Key, Value>::pushFront(Key key, Value value)
{
    Node<Key, Value>* currnt = head;
    if(currnt != NULL)
    {
        while(currnt->next)
        {
            currnt = currnt->next;
        }
        currnt->next = new Node<Key, Value>;
        currnt = currnt->next;
    }
    else
    {
        head = new Node<Key, Value>;
        currnt = head;
    }
    currnt->key = key;
    currnt->value = value;
    currnt->next = NULL;
}

template <typename Key, typename Value>
void List<Key, Value>::addAfter(Key newKey, Value newValue, Key key, int numb)
{
    Node<Key, Value>* currnt = head;
    int counter = 0;
    while (currnt)
    {
        if (currnt->key == key)
        {
            if (counter == numb)
            {
                Node<Key, Value>* temp = new Node<Key, Value>;
                temp->key = newKey;
                temp->value = newValue;
                temp->next = currnt->next;
                currnt->next = temp;
                return;
            }
            else
            {
                counter++;
            }
        }
        currnt = currnt->next;
    }
}

template <typename Key, typename Value>
void List<Key, Value>::removeFront()
{
    if (head != NULL)
    {
        Node<Key, Value>* temp = head;
        if(temp->next)
        {
            while(temp->next->next)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = NULL;
        }
        else
        {
            delete head;
            head = NULL;
        }
    }
}

template <typename Key, typename Value>
void List<Key, Value>::removeBack()
{
    if (head != NULL)
    {
        Node<Key, Value>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename Key, typename Value>
void List<Key, Value>::removeNode(Key key, int numb)
{
    Node<Key, Value>* currnt = head;
    int counter = 0;
    Node<Key, Value>* prev = NULL;
    while (currnt)
    {
        if (currnt->key == key)
        {
            if (counter == numb)
            {
                prev->next = currnt->next;
                delete currnt;
                return;
            }
            else
            {
                counter++;
            }
        }
        prev = currnt;
        currnt = currnt->next;
    }
}

template <typename Key, typename Value>
void List<Key, Value>::clear()
{
    while(head)
    {
       Node<Key, Value>* temp = head;
       head = head->next;
       delete temp;
    }
}

template <typename Key, typename Value>
void List<Key, Value>::print() const
{
    Node<Key, Value>* currnt = head;
    while(currnt)
    {
        cout << "Key: " << currnt->key << " Value: " << currnt->value << endl;
        currnt = currnt->next;
    }
    cout << endl;
}

template <typename Key, typename Value>
void List<Key, Value>::print(Key key) const
{
    Node<Key, Value>* currnt = head;
    while(currnt)
    {
        if (currnt->key == key)
        {
            cout << "Key: " << currnt->key << " Value: " << currnt->value << endl;
        }
        currnt = currnt->next;
    }
    cout << endl;
}

template <typename Key, typename Value>
int List<Key, Value>::size() const
{
    int counter = 0;
    Node<Key, Value>* currnt = head;
    while(currnt)
    {
        counter++;
        currnt = currnt->next;
    }
    return counter;
}

template <typename Key, typename Value>
bool List<Key, Value>::exists(Key key) const
{
    Node<Key, Value>* currnt = head;
    while(currnt)
    {
        if (currnt->key == key)
        {
            return true;
        }
    }
}

template <typename Key, typename Value>
Node<Key, Value>* List<Key, Value>::getHead() const
{
    return head;
}

template <typename Key, typename Value>
void interleave(const List<Key, Value>& first, int fcount, const List<Key, Value>& second, int scount, List<Key, Value>& result)
{
    result.clear();
    Node<Key, Value>* currnt;

    Node<Key, Value>* last1 = first.getHead();
    Node<Key, Value>* last2 = second.getHead();


    while (last1 || last2)
    {
        currnt = last1;
        for(int i = 0; i < fcount; ++i)
        {
            if (currnt == NULL)
            {
                last1 = currnt;
                break;
            }
            else
            {
                result.pushFront(currnt->key, currnt->value);
                currnt = currnt->next;
            }
        }
        last1 = currnt;
        if (last1 == first.getHead()) last1 = NULL;
        currnt = last2;
        for(int i = 0; i < scount; ++i)
        {
            if (currnt == NULL)
            {
                last2 = currnt;
                break;
            }
            else
            {
                result.pushFront(currnt->key, currnt->value);
                currnt = currnt->next;
            }
        }
        last2 = currnt;
        if (last2 == second.getHead()) last2 = NULL;
    }
}

void separation()
{
    for (int i=0;i<60;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    cout<<endl;
}

int main()
{

    cout << "The idea of the order: " << endl;
    cout<<endl;
    cout << "back " << endl;
    cout << "front " << endl;
    cout<<endl;
    separation();
    List<string, string> list;
    list.pushBack("G", "Germany");
    list.pushBack("P", "Poland");
    list.pushBack("F", "France");
    list.pushBack("S", "Sweden");
    list.pushBack("S", "Switzerland");
    cout << "5 added countries: " << endl;
    cout<<endl;

    list.print();

    separation();

    cout << "After removeNode: " << endl;
    cout<<endl;
    list.removeNode("F",0);
    list.print();
    separation();

    cout << "Countries only with key S: " << endl;
    cout<<endl;
    list.print("S");
    separation();

    list.removeBack();
    cout << "After removeBack: " << endl;
    cout<<endl;
    list.print();

    separation();

    list.removeFront();
    cout << "After removeFront: " << endl;
    cout<<endl;
    list.print();

    separation();

    cout << "Size of the list:" << endl;
    cout << list.size() << endl;

    list.clear();

    cout << "Size of the list after clear:" << endl;
    cout << list.size() << endl;

    separation();

    list.pushBack("C", "Czech Republic");
    list.pushBack("A", "Austria");
    list.pushFront("E", "Estonia");
    list.pushFront("P", "Portugal");

    cout << "After clear and adding 4 new countries: " << endl;
    cout<<endl;

    list.print();
    separation();

    list.removeBack();
    list.removeBack();
    cout << "After 2 times removeBack: " << endl;
    cout<<endl;
    list.print();
    separation();

    list.removeFront();
    cout << "After removeFront: " << endl;
    cout<<endl;
    list.print();
    separation();

    cout << "Size of the list:" << endl;
    cout << list.size() << endl;
    separation();

    list.addAfter("L", "Latvia", "E");
    list.addAfter("L", "Lithuania", "L");
    list.addAfter("S", "Spain", "L", 1);
    cout << "After 3 times addAfter: " << endl;
    cout<<endl;
    list.print();
    separation();

    list.pushFront("G", "Greece");
    list.pushBack("C", "Croatia");
    cout << "After one pushFront and one pushBack: " << endl;
    cout<<endl;
    list.print();
    separation();


    List<string, string> List2(list);
    cout << "List2: " << endl;
    cout<<endl;
    List2.print();
    separation();

    List2.removeFront();
    cout << "After one removeFront: " << endl;
    cout<<endl;
    List2.print();
    separation();

    cout << "After assignment List2 to list: " << endl;
    cout<<endl;
    List2 = list;
    List2.print();
    separation();

    List2.clear();

    List2.pushBack("N", "List2: Norway");
    List2.pushFront("D", "List2: Denmark");
    List2.pushBack("S", "List2: Scotland");
    List2.pushFront("S", "List2: Slovenia");
    cout << "After clear List2 and adding 4 new countries: " << endl;
    cout<<endl;
    List2.print();
    separation();

    List<string, string> List3;
    List3.pushFront("E", "List3: England");
    cout << "List3: " << endl;
    cout<<endl;
    List3.print();
    separation();

    cout << "List: " << endl;
    cout<<endl;
    list.print();
    separation();
    cout << "List2: " << endl;
    cout<<endl;
    List2.print();
    separation();

    interleave(list, 1, List2, 1, List3);
    cout << "List3 after using interleave (2 from the 1st list and 1 from the 2nd list): " << endl;
    cout<<endl;
    List3.print();
}
