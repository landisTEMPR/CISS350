#include <iostream>


class Node
{
    
public:
    // Data part of node
    int data;
    
    // Pointer to next node in the list
    Node* next;

    // Constructor to initialize node with data
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};


int main()
{
    // Create the first node (head of list)
    Node* head = new Node(10);

    // Link second node
    head->next = new Node(20);

    // Link thrid node
    head->next->next = new Node(55);

    // Printing list
    while(head != NULL)
    {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << '\n';

    return 0;  
}
