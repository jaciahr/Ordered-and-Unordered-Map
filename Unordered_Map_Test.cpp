#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <chrono>
#include <unordered_map>
using namespace std::chrono;
using namespace std;

typedef high_resolution_clock Clock;

class LinkedList {
public:
    struct Node {
        string name;
        string gatorId;
        Node* next;
        Node* prev;
    };

    LinkedList(const LinkedList& list);
    const LinkedList& operator=(const LinkedList& rhs);

    //Ways to add information to the container
    void AddHead(const string& gatorId, const string& name);
    void AddTail(const string& gatorId, const string& name);
    //void AddNodesHead(const string* data, unsigned int count);
    //void AddNodesTail(const string* data, unsigned int count);
    void PrintForwardRecursive(const Node* node) const;

    //A way to get some information about the container
    unsigned int NodeCount() const;

    //Some essentials for any class
    LinkedList();
    ~LinkedList();

    //Getting the head and tail nodes:
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    //Finding the FIRST node based on a value
    Node* Find(const string& gatorId);
    const Node* Find(const string& gatorId) const;

    //Insert elements into the linked list
    void InsertAt(const string& data, unsigned int index);
    void InsertBefore(Node* node, const string& data);

    //Removal functions
    unsigned int Remove(const string& data);
    bool RemoveHead();
    bool RemoveTail();
    void Clear();

private:
    Node* head;
    Node* tail;
    unsigned int count;
};

const LinkedList& LinkedList::operator=(const LinkedList& rhs) {
    Node* temp = head;
    while (temp != nullptr) {
        head = head->next;
        delete temp;
        temp = head;
    }
    count = 0;
    head = nullptr;
    tail = nullptr;
    Node* n = rhs.head;
    while (n != nullptr) {
        AddTail(n->gatorId, n->name);
        n = n->next;
    }
    return *this;
}

//Create a new Node at the front of the list to store the passed in parameter.
void LinkedList::AddHead(const string& gatorId, const string& name) {
    Node* n = new Node;
    n->gatorId = gatorId;
    n->name = name;
    n->next = nullptr;
    n->prev = nullptr;

    if (head == nullptr) {
        head = n;
        tail = n;
    }
    else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    count++;
}

//Create a new Node at the end of the list to store the passed in parameter.
void LinkedList::AddTail(const string& gatorId, const string& name) {
    if (count == 0)
        AddHead(gatorId, name);
    else {
        Node* n = new Node;
        n->gatorId = gatorId;
        n->name = name;
        tail->next = n;
        n->prev = tail;
        tail = n;
        tail->next = nullptr;
        count++;
    }
}

//How many things are stored in this list?
unsigned int LinkedList::NodeCount() const {
    return count;
}

//Default constructor. How many nodes in an empty list? What is head pointing to? What is tail pointing to? 
//Initialize your variables!
LinkedList::LinkedList() {
    count = 0;
    head = nullptr;
    tail = nullptr;
}

//The usual. Clean up your mess. (Delete all the nodes created by the list.)
LinkedList::~LinkedList() {
    Node* n = head;
    while (n != nullptr) {
        head = head->next;
        delete n;
        n = head;
    }
    count = 0;
    head = nullptr;
    tail = nullptr;
}

//Returns the head pointer (non-const version).
LinkedList::Node* LinkedList::Head() {
    return head;
}

//Returns the head pointer (const version).
const LinkedList::Node* LinkedList::Head() const {
    return head;
}

//Returns the tail pointer (non-const version).
LinkedList::Node* LinkedList::Tail() {
    return tail;
}

//Returns the tail pointer (const version).
const LinkedList::Node* LinkedList::Tail() const {
    return tail;
}

//Find the first node with a data value matching the passed in parameter, returning a pointer to that node. 
//Returns nullptr if no matching node found (non-const version).
LinkedList::Node* LinkedList::Find(const string& gatorId) {
    Node* n = head;
    for (unsigned int i = 0; i < count; i++) {
        if (n->gatorId == gatorId) {
            return n;
        }
        n = n->next;
    }
    return nullptr;
}

//Find the first node with a data value matching the passed in parameter, returning a pointer to that node. 
//Returns nullptr if no matching node found (const version).
const LinkedList::Node* LinkedList::Find(const string& gatorId) const {
    Node* n = head;
    for (unsigned int i = 0; i < count; i++) {
        if (n->gatorId == gatorId) {
            return n;
        }
        n = n->next;
    }
    return nullptr;
}

//Sets "this" to a copy of the passed in LinkedList. 
//For example, if the other list has 10 nodes, with values of 1-10? "this" should have a copy of that same data.
LinkedList::LinkedList(const LinkedList& list) {
    count = 0;
    head = nullptr;
    tail = nullptr;
    Node* n = list.head;
    AddHead(n->gatorId, n->name);
    n = n->next;
    while (n != nullptr) {
        this->AddTail(n->gatorId, n->name);
        n = n->next;
    }
}

//Inserts a new Node to store the first parameter, at the indexth location. So if you specified 3 as the index, 
//the new Node should have 3 Nodes before it. Throws an out_of_range exception if given an invalid index.
void LinkedList::InsertAt(const string& data, unsigned int index) {
    Node* n = head;
    if (index > count)
        throw out_of_range("Invalid index.");
    else if (index == count)
        AddTail(n->gatorId, n->name);
    else {
        for (unsigned int i = 0; i < index; i++)
            n = n->next;
        InsertBefore(n, data);
    }
}

void LinkedList::InsertBefore(Node* node, const string& data) {
    if (node->prev == nullptr) {
        AddHead(node->gatorId, node->name);
    }
    else {
        Node* n = new Node;
        n->gatorId = data;
        n->prev = node->prev;
        node->prev->next = n;
        n->next = node;
        node->prev = n;
        count++;
    }
}

bool LinkedList::RemoveHead() {
    if (count == 0)
        return false;
    Node* n = head;
    head = head->next;
    delete n;
    count--;
    if (head != nullptr)
        head->prev = nullptr;
    return true;
}

//Deletes the last Node, returning whether or not the operation was successful.
bool LinkedList::RemoveTail() {
    if (count == 0)
        return false;
    else if (tail == head)
        RemoveHead();
    else {
        Node* n = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete n;
        count--;
    }
    return true;
}

//Remove ALL Nodes containing values matching that of the passed-in parameter. Returns how many instances were removed.
unsigned int LinkedList::Remove(const string& gatorId) {
    unsigned int removedVal = 0;
    Node* n = head;
    if (head->gatorId == gatorId) {
        RemoveHead();
        removedVal++;
        n = nullptr;
    }
    else if (tail->gatorId == gatorId) {
        RemoveTail();
        removedVal++;
    }
    while (n != nullptr) {
        if (n->gatorId == gatorId) {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            Node* deleting = n->next;
            delete n;
            n = deleting;
            removedVal++;
            count--;
        }
        n = n->next;
    }
    return removedVal;
}

//Deletes all Nodes. Don't forget the node count—how many nodes do you have after you deleted all of them?
void LinkedList::Clear() {
    Node* temp = head;
    while (temp != nullptr) {
        head = head->next;
        delete temp;
        temp = head;
    }
    count = 0;
    head = nullptr;
    tail = nullptr;
}

void LinkedList::PrintForwardRecursive(const Node* node) const {
    if (node != nullptr) {
        cout << node->gatorId << endl;
        PrintForwardRecursive(node->next);
    }
}

unsigned int hashFunction(char const* key, int table_size) {
    unsigned int hashCode = 0;
    unsigned int temp = 0;
    unsigned int charToASCII = 0;

    for (unsigned int i = 0; i < strlen(key); i++) {
        if (i % 2 == 0) {
            temp = (hashCode << 7) ^ key[i] ^ (hashCode >> 3);
        }
        else {
            temp = (hashCode << 11) ^ key[i] ^ (hashCode >> 5);
            temp = ~temp;
        }
        hashCode = hashCode ^ temp;
    }

    hashCode &= ~(1UL << 31);
    return (hashCode % table_size);
}

class UnorderedMap
{
private:
    vector<LinkedList> myHash;
    unsigned int bucketCount;
    double currentLoadFactor;
    double maxLoadFactor;
    unsigned int hashSize;

public:
    class Iterator;
    UnorderedMap(unsigned int bucketCount, double loadFactor);
    ~UnorderedMap();
    Iterator begin() const;
    Iterator end() const;
    std::string& operator[] (std::string const& key);
    void rehash();
    void remove(std::string const& key);
    unsigned int size();
    double loadFactor();

    class Iterator
    {
        LinkedList const* linkedListPointer;
        LinkedList::Node const* nodePointer;
        int count;
        int size;
    public:
        //this constructor does not need to be a default constructor;
        //the parameters for this constructor are up to your discretion.
        //hint: you may need to pass in an UnorderedMap object.
        Iterator(const UnorderedMap* map, int begin) {
            count = 0;
            size = map->myHash.size();
            nodePointer = nullptr;
            linkedListPointer = nullptr;

            if (begin == 0) {
                int i = 0;

                while (i < map->myHash.size()) {
                    if (map->myHash[i].NodeCount() != 0) {
                        nodePointer = map->myHash[i].Head();
                        linkedListPointer = &map->myHash[i];
                        break;
                    }
                    i++;
                }
            }
        }

        Iterator& operator=(Iterator const& rhs) {
            count = rhs.count;
            size = rhs.size;
            nodePointer = rhs.nodePointer;
            linkedListPointer = rhs.linkedListPointer;
            return *this;
        }

        Iterator& operator++() { 
            if (nodePointer->next != nullptr && nodePointer != nullptr)
                nodePointer = nodePointer->next;
            else {
                count++;
                linkedListPointer++;

                while (count < size) {
                    if (linkedListPointer->NodeCount() != 0) {
                        nodePointer = linkedListPointer->Head();
                        return *this;
                    }
                    count++;
                    linkedListPointer++;
                }

                nodePointer = nullptr;
                linkedListPointer = nullptr;
            }
            return *this;
        }

        bool operator!=(Iterator const& rhs) {
            if (nodePointer != rhs.nodePointer)
                return true;
            return false;
        }

        bool operator==(Iterator const& rhs) { }
        std::pair<std::string, std::string> operator*() const { 
            if (nodePointer != nullptr) {
                return pair<string, string>(this->nodePointer->gatorId, this->nodePointer->name);
            }
        }
        friend class UnorderedMap;
    };
};

//Constructor
UnorderedMap::UnorderedMap(unsigned int bucketCount, double loadFactor)
{
    this->bucketCount = bucketCount;
    myHash.resize(bucketCount);
    maxLoadFactor = loadFactor;
    hashSize = 0;
}

//Destructor (dw about)
UnorderedMap::~UnorderedMap() {}

UnorderedMap::Iterator UnorderedMap::begin() const
{
    return Iterator(this, 0);
}

UnorderedMap::Iterator UnorderedMap::end() const
{
    return Iterator(this, -1);
}

std::string& UnorderedMap::operator[] (std::string const& key)
{
    for (unsigned int i = 0; i < myHash.size(); i++) {
        LinkedList::Node* searchKey = myHash[i].Find(key);

        if (searchKey != nullptr) {
            return searchKey->name;
        }
    }

    int index = (hashFunction(key.c_str(), myHash.size()));
    myHash[index].AddTail(key, "");
    hashSize++;
    //cout << "Bucket count: " << bucketCount << endl;
    //cout << key.c_str() << endl;

    if (loadFactor() >= maxLoadFactor) {
        rehash();
        index = (hashFunction(key.c_str(), myHash.size()));
    }

    return myHash[index].Tail()->name;

}

void UnorderedMap::rehash()
{
    //cout << "Capacity: " << myHash.capacity() << endl;
    //cout << "Old bucket count: " << bucketCount << endl;
    bucketCount *= 2;
    //cout << "New bucket count: " << bucketCount << endl;
    vector<LinkedList> tempVector;
    tempVector.resize(bucketCount);
    //vector<int> tempIndices;

    for (unsigned int i = 0; i < myHash.size(); i++) {
        auto temp = myHash[i].Head();

        while (temp != nullptr) {
            //cout << temp->gatorId << endl;
            int index = (hashFunction((temp->gatorId).c_str(), bucketCount));
            //tempIndices.push_back(index);
            tempVector[index].AddTail(temp->gatorId, temp->name);
            temp = temp->next;
        }
    }

    myHash.clear();
    myHash.resize(bucketCount);

    for (unsigned int i = 0; i < tempVector.size(); i++) {
        myHash[i] = tempVector[i];
        //myHash[i].Head()->name = tempVector[i].Head()->name;
    }

    tempVector.clear();
    //tempIndices.clear();
}

void UnorderedMap::remove(std::string const& key)
{
    const char* temp = key.c_str();
    unsigned int index = hashFunction(temp, myHash.size());
    myHash[index].Remove(key);
    hashSize--;
}

unsigned int UnorderedMap::size()
{
    return hashSize;
}

double UnorderedMap::loadFactor()
{
    unsigned int numElements = size();
    double capacity = myHash.capacity();
    //cout << capacity << endl;
    currentLoadFactor = ((double)numElements) / capacity;
    return currentLoadFactor;
}

//Do not change main() 
int main()
{
    int buckets = 5;
    double maxLoadFactor = 0.8;
    std::string command = "", ufid = "", name = "", key = "";
    UnorderedMap myMap = UnorderedMap(buckets, maxLoadFactor);

    /*while (lines--)
    {
        std::cin >> command;
        if (command == "hash")
        {
            std::cin >> key;
            const char* convertedKey = key.c_str();
            std::cout << hashFunction(convertedKey, buckets) << "\n";
        }
        else if (command == "insert")
        {
            std::cin >> ufid >> name;
            myMap[ufid] = name;
        }
        else if (command == "size")
        {
            std::cout << myMap.size() << "\n";
        }
        else if (command == "load")
        {
            std::cout << std::fixed << std::setprecision(2) << myMap.loadFactor() << "\n";
        }
        else if (command == "search")
        {
            std::cin >> ufid;
            std::cout << myMap[ufid] << "\n";
        }
        else if (command == "traverse")
        {
            for (UnorderedMap::Iterator iter = myMap.begin(); iter != myMap.end(); ++iter)
            {
                std::cout << (*iter).first << " " << (*iter).second << "\n";
            }

            /* This should also work
                for (auto tableEntry: myMap)
                {
                    std::cout << tableEntry.first << " " << tableEntry.second << "\n";
                }
                

        }
        
        else if (command == "remove")
        {
            std::cin >> ufid;
            myMap.remove(ufid);
        }
    }
    */
    unordered_map<string, string> unorderedSTL;

    //========================================TIMING==========================================
    //Self-made unordered map implementation
    for (unsigned int i = 0; i < 100000; i++) {
        myMap[to_string(i)] = to_string(i);
    }
    auto t1 = Clock::now();
    for (unsigned int i = 100000; i > 0; i--) {
        myMap[to_string(i)];
    }
    auto t2 = Clock::now();
    std::cout << "My search (100000): "
        << duration_cast<nanoseconds>(t2 - t1).count()
        << " nanoseconds" << '\n';

    t1 = Clock::now();
    for (unsigned int i = 100000; i > 0; i--) {
        myMap.remove(to_string(i));
    }
    t2 = Clock::now();
    std::cout << "My remove (100000): "
        << duration_cast<nanoseconds>(t2 - t1).count()
        << " nanoseconds" << '\n';
    
    //STL unordered map implementation
    for (unsigned int i = 0; i < 100000; i++) {
        unorderedSTL[to_string(i)] = to_string(i);
    }
    t1 = Clock::now();
    for (unsigned int i = 100000; i > 0; i--) {
        unorderedSTL.find(to_string(i));
    }
    t2 = Clock::now();
    std::cout << "STL search (100000): "
        << duration_cast<nanoseconds>(t2 - t1).count()
        << " nanoseconds" << '\n';

    t1 = Clock::now();
    for (unsigned int i = 100000; i > 0; i--) {
        unorderedSTL.erase(to_string(i));
    }
    t2 = Clock::now();
    std::cout << "STL remove (100000): "
        << duration_cast<nanoseconds>(t2 - t1).count()
        << " nanoseconds" << '\n';

    return 0;
}