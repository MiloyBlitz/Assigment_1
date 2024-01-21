#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

typedef struct 
{
    Node* head;  
    Node* tail;  
    int size;    
    int* positions; 
} LinkedList;

void List(LinkedList* list) 
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->positions = NULL;
}


void insertAt(LinkedList* list, int data, int position) 
{
    if (position < 0 || position > list->size) 
    {
        printf("Invalid position for insertion!\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (position == 0) 
    {
        // Insert at the beginning
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == NULL) {
            list->tail = newNode;
        }
    } else if (position == list->size) 
    {
        // Insert at the end
        list->tail->next = newNode;
        list->tail = newNode;
    } else 
    {
        // Insert in the middle
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) 
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // Update positions array
    list->positions = realloc(list->positions, (list->size + 1) * sizeof(int));
    for (int i = list->size; i > position; i--) 
    {
        list->positions[i] = list->positions[i - 1];
    }
    list->positions[position] = data;

    list->size++;
}

void removeElement(LinkedList* list, int position) 
{
    if (position < 0 || position >= list->size) 
    {
        printf("Invalid position for removal!\n");
        return;
    }

    printf("Remove the element from position %d: %d\n", position, list->positions[position]);

    Node* temp;
    if (position == 0) 
    {
        // Remove from the beginning
        temp = list->head;
        list->head = list->head->next;
        free(temp);
        if (list->head == NULL) 
        {
            list->tail = NULL;
        }
    } else 
    {
        // Remove from the middle or end
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) 
        {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
        free(temp);
        if (position == list->size - 1) {
            list->tail = current;
        }
    }

    // Update positions array
    for (int i = position; i < list->size - 1; i++) 
    {
        list->positions[i] = list->positions[i + 1];
    }
    list->positions = realloc(list->positions, (list->size - 1) * sizeof(int));

    list->size--;
}


// Function to get the element at a specific position in the list
int get(LinkedList* list, int position) 
{
    if (position < 0 || position >= list->size) 
    {
        printf("Invalid position for get!\n");
        return -1; 
    }

    return list->positions[position];
}

// Function to print the elements in the linked list
void printList(LinkedList* list) 
{
    Node* current = list->head;
    while (current != NULL) 
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the linked list
void freeLinkedList(LinkedList* list) 
{
    Node* current = list->head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list->positions);
    List(list);
}

int main() 
{
    LinkedList list;
    List(&list);

    int numElements = 20; //Change the value here if you want to how many elements to be inserted into the lists
    
    for (int i = 1; i <= numElements; i++) 
    {
        insertAt(&list, i, i-1);
    }
    
    printf("List after insertion: ");
    printList(&list);

    srand(time(NULL));
    int randomPosition = rand() % numElements;
    printf("A chosen position to remove randomly: %d\n", randomPosition);

    removeElement(&list, randomPosition);

    printf("List after removal at position %d: ", randomPosition);
    printList(&list);

    freeLinkedList(&list);

    return 0;
}