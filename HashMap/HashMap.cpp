#include <algorithm>
#include <iostream>

const int MAX_SIZE = 1000000;

struct HM_Item {
    char* key;
    char* value; // pointers to key and value
};

// handle collision using overflow linked lists
struct LinkedList {
    HM_Item* item;
    LinkedList* next;
};

struct HashMap {
    int n;
    int size;

    HM_Item** items;
    LinkedList** overflow_buckets;
};


HM_Item* create_item(char* k, char* v)
{
    HM_Item* item = (HM_Item*) malloc(sizeof(HM_Item));
    item->key = (char*) malloc(strlen(k) + 1); // + 1
    item->value = (char*) malloc(strlen(v) + 1); // + 1

    strcpy_s(item->key, strlen(k) + 1, k);
    strcpy_s(item->value, strlen(v) + 1, v);

    return item;
}

void free_item(HM_Item* item)
{
    if (item != NULL)
    {
        free(item->key);
        free(item->value);
    }
    free(item);
}

LinkedList* allocate_linked_list()
{
    return (LinkedList*)malloc(sizeof(LinkedList));
}


void free_linked_list(LinkedList* list) {
    if (list)
    {
        free_item(list->item);
        free_linked_list(list->next);
        free(list);
    }
    else
    {
        free(list);
    }
}

// allocate memory and initialize a NULL array
LinkedList** create_overflow_buckets(HashMap* map)
{
    LinkedList** buckets = (LinkedList**)calloc(map->size, sizeof(LinkedList*));

    for (int i = 0; i < map->size; i++)
    {
        buckets[i] = NULL;
    }

    return buckets;
}

void free_overflow_buckets(HashMap* map)
{
    if (map->overflow_buckets)
    {
        for (int i = 0; i < map->size; i++)
        {
            free_linked_list(map->overflow_buckets[i]);
        }
    }
    free(map->overflow_buckets);
}


// initialize a hash map w/ zero elements
HashMap* create_map(int size)
{
    HashMap* map = (HashMap*) malloc(sizeof(HashMap));
    map->size = size;
    map->n = 0;
    // allocates memory for a certain amount of HM_Items
    map->items = (HM_Item**) calloc(size, sizeof(HM_Item*));

    for (int i = 0; i < size; i++)
    {
        map->items[i] = NULL;
    }

    map->overflow_buckets = create_overflow_buckets(map);

    return map;
}

// insert item as the next item of list
LinkedList* linked_list_insert(HM_Item* item, LinkedList* list)
{
    // if the list is uninitialized
    if (!list)
    {
        list = allocate_linked_list();
        list->item = item;
        list->next = NULL;
        return list;
    }
    // if the list has an empty next element
    else if (list->next == NULL)
    {
        LinkedList* next = allocate_linked_list();
        next->item = item;
        next->next = NULL;

        list->next = next;

        return list;
    }
    // if we need to iterate through the entire linked list
    // and insert as a new node
    else
    {
        // our list to insert
        LinkedList* new_list = allocate_linked_list();
        new_list->item = item;
        new_list->next = NULL;

        // iterate and find the last linked list w/ an null next value
        LinkedList* temp = list;
        while (temp->next->next)
        {
            // should be temp->next->next???????????
            temp = temp->next;
        }

        temp->next = new_list;
        
        return list;
    }
}

// removes the head and returns the popped element
HM_Item* linked_list_remove(LinkedList* list)
{
    // base case checking
    if (!list)
    {
        return NULL;
    }
    
    if (!list->next)
    {
        list = NULL;
        return NULL;
    }

    // essentially set list as list->next

    LinkedList* temp = list;
    temp->next = NULL;
    HM_Item* popped = temp->item;

    list = list->next;

    // free the head of the linked list
    free_item(temp->item);
    free(temp);

    return popped;
}

void handle_collision(HashMap* map, unsigned long index, HM_Item* item)
{
    LinkedList* bucket = map->overflow_buckets[index];
    // if bucket at index uninitialized
    if (!bucket)
    {
        bucket = allocate_linked_list();
        bucket->item = item;
        bucket->next = NULL;
        map->overflow_buckets[index] = bucket;

        return;
    }
    else
    {
        // insert
        linked_list_insert(item, bucket);

        return;
    }
}


// adds ascii values of the characters in string and mods by capacity of map
unsigned long hash_func(char* k)
{
    unsigned long hash = 0;
    for (int i = 0; k[i]; i++)
    {
        hash += k[i];
    }
    return hash % MAX_SIZE;
}


void insert_item(HashMap* map, char* k, char* v)
{
    // hash to figure out location of item in hashmap
    int index = hash_func(k);

    HM_Item* item = create_item(k, v);

    // no previous value at that index
    if (map->items[index] == NULL)
    {
        if (map->n == map->size)
        {
            std::cout << "table is full" << std::endl;
        }

        // add to map
        map->items[index] = item;
        map->n++;
    }
    // already a value there
    else
    {
        // if previous element has matching key, simply update
        if (strcmp(map->items[index]->key, k) == 0)
        {
            map->items[index]->value = (char*)malloc(strlen(v) + 1);
            strcpy_s(map->items[index]->value, strlen(v) + 1, v);
        }
        // otherwise, hash collision
        else
        {
            handle_collision(map, index, item);
        }
    }
}

// delete the first item that has a matching key
void delete_item(HashMap* map, char* key)
{
    int index = hash_func(key);

    HM_Item* item = map->items[index];
    LinkedList* overflow = map->overflow_buckets[index];

    if (item == NULL)
    {
        return;
    }

    // delete from overflow buckets
    if (overflow != NULL)
    {
        // if key matches, delete and shift
        if (strcmp(item->key, key) == 0)
        {
            // delete
            free_item(item);
            map->n--;

            // shift
            LinkedList* temp = overflow;
            temp->next = NULL;

            map->items[index] = create_item(temp->item->key, temp->item->value);
            overflow = overflow->next;
            free_linked_list(temp);

            map->overflow_buckets[index] = overflow;

            return;
        }
        // else check overflow buckets
        else
        {
            LinkedList* prev = NULL;
            LinkedList* curr = overflow;

            while (curr)
            {
                // if the first in chain matches
                if (prev == NULL && strcmp(curr->item->key, key) == 0)
                {
                    // delete and reassign
                    LinkedList* temp = curr;
                    map->overflow_buckets[index] = curr->next;

                    temp->next = NULL;
                    free_linked_list(temp);
                    return;
                }
                // if some link in the chain matches
                else if (prev != NULL && strcmp(curr->item->key, key) == 0)
                {
                    // delete and shift
                    LinkedList* temp = curr;
                    
                    prev->next = curr->next; 
                    
                    map->overflow_buckets[index] = prev;

                    temp->next = NULL;
                    free_linked_list(temp);

                    return;
                }
            }
        }
    }
    // else no overflow buckets
    else
    {
        // simply delete item
        if (strcmp(item->key, key) == 0)
        {
            map->items[index] = NULL;
            free_item(item);
            map->n--;
            return;
        }
    }

}

// searches for the first item in the map with the specified key
char* search_map(HashMap* map, char* key)
{
    int index = hash_func(key);

    // check item's null-ness
    HM_Item* item = map->items[index];

    // check overflow buckets
    LinkedList* head = map->overflow_buckets[index];

    while (item)
    {
        // if key matches
        if (strcmp(item->key, key) == 0)
        {
            return item->value;
        }
        if (head == NULL)
        {
            return NULL;
        }
        item = head->item;
        head = head->next;
    }
    return NULL;
}

void print_search(HashMap* map, char* key) {
    char* val;
    if ((val = search_map(map, key)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_map(HashMap* map)
{
    std::printf("\nHash Map\n--------------------\n");
    for (int i = 0; i < map->size; i++)
    {
        if (map->items[i] != NULL)
        {
            std::printf("Index: %d, Key: %s, Value: %s\n", i, map->items[i]->key, map->items[i]->value);

            if (map->overflow_buckets[i] != NULL)
            {
                std::cout << " => Overflow Bucket => ";
                LinkedList* cur = map->overflow_buckets[i];

                while (cur != NULL)
                {
                    std::printf("Key: %s, Value: %s; ", cur->item->key, cur->item->value);
                    cur = cur->next;
                }
            }
            std::cout << "\n";
        }

    }
    std::printf("-------------------\nEnd of Hash Map\n");
}

void free_map(HashMap* map)
{
    for (int i = 0; i < map->size; i++)
    {
        free_item(map->items[i]);
    }
    free(map->items);
    free_overflow_buckets(map);
    free(map);
}

int main()
{
    HashMap* ht = create_map(MAX_SIZE);
    insert_item(ht, (char*)"1", (char*)"First address");
    insert_item(ht, (char*)"2", (char*)"Second address");
    insert_item(ht, (char*)"Hel", (char*)"Third address");
    insert_item(ht, (char*)"Cau", (char*)"Fourth address");
    print_search(ht, (char*)"1");
    print_search(ht, (char*)"2");
    print_search(ht, (char*)"3");
    print_search(ht, (char*)"Hel");
    print_search(ht, (char*)"Cau");  // Collision!
    print_map(ht);
    delete_item(ht, (char*)"1");
    delete_item(ht, (char*)"Cau");
    print_map(ht);
    free_map(ht);
    return 0;
}
