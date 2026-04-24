#include "hashtable.h"

size_t hash_code(const std::string& str) {
    size_t h = 0;
    for (size_t i = 0; i < str.length(); i++) {
        h = 31 * h + str[i];
    }
    return h;
}

HashTable::HashTable(size_t nbuckets)
{
    for (size_t i = 0; i < nbuckets; i++)
    {
        buckets.push_back(nullptr);
    }
    current_size = 0;
}

size_t HashTable::count(const std::string& x)
{
    size_t h =hash_code(x) % buckets.size();
        
    Node* current = buckets[h];
    while (current != nullptr)
    {
        if (current->data == x) { return 1; }
        current = current->next;
    }
    return 0;
}

void HashTable::rehash(size_t new_size){
    std::vector<Node*> old_buckets = buckets;

    buckets.clear(); 
    buckets.resize(new_size, nullptr);
    current_size = 0;

    for(auto head: old_buckets){
        Node* curr = head;
        while(curr){

            size_t h = hash_code(curr->data) % buckets.size();
            Node* newNode = new Node();
            newNode->data = curr->data;
            
            newNode->next = buckets[h];
            buckets[h] = newNode;
            current_size++;

            Node* del = curr;
            curr = curr->next;
            delete del;
        }
    }
    load_factor = static_cast<double>(current_size) / buckets.size();
}

void HashTable::grow_if_necessary(){
    if(load_factor > 0.75){
        rehash(buckets.size() * 2);
    }
    if(load_factor < 0.25 && buckets.size() > 1){
        rehash(buckets.size()/2);
    }
}

void HashTable::insert(const std::string &s){
    
    size_t h = hash_code(s) % buckets.size();

    //check if already exists
    Node* curr = buckets[h];
    while(curr){
        if(curr->data == s){
            return;
        }
        curr = curr->next;
    }

    Node* newNode = new Node();
    newNode->data = s;
    newNode->next = buckets[h];
    buckets[h] = newNode;
    current_size++;
    load_factor = static_cast<double>(current_size) / buckets.size();

    grow_if_necessary();

}

void HashTable::erase(const std::string &s){
    size_t h = hash_code(s) % buckets.size();

    Node* curr = buckets[h];
    Node* prev = nullptr;
    while(curr){
        if (curr->data == s){
            if(prev){
                prev->next = curr->next;
            }
            else{
                buckets[h] = curr->next;
            }
            delete curr;
            current_size--;
            load_factor = static_cast<double>(current_size) / buckets.size();
            grow_if_necessary();

            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void Iterator::next(){
    if(current != nullptr){
        current = current->next;
        if(current!= nullptr){
            return;
        }
        bucket_index++;
        
    }
    else {
        bucket_index++;
    }

    int n = static_cast<int>(container->buckets.size());
    while (bucket_index < n) {
        if (container->buckets[bucket_index] != nullptr) {
            current = container->buckets[bucket_index];
            return;
        }
        bucket_index++;
    }
    current = nullptr;
    bucket_index = n;
}

void Iterator::operator++() { next();}

size_t HashTable::size() const
{
    return current_size;
}
size_t HashTable::buckets_size() const
{
    return buckets.size();
}
Iterator HashTable::begin() const
{
    Iterator iter;
    iter.current = nullptr;
    iter.bucket_index = -1;
    iter.container = this;
    iter.next();
    return iter;
}

Iterator HashTable::end() const
{
    Iterator iter;
    iter.current = nullptr;
    iter.bucket_index = buckets.size();
    iter.container = this;
    return iter;
}

std::string Iterator::get() const
{
    return current->data;
}

bool Iterator::equals(const Iterator& other) const
{
    return current == other.current;
}
