#include <stdio.h>
#include <stdlib.h>

typedef struct Linked_List {
    char data;
    struct Linked_List* next_node;
} Linked_List;

//forward declarations
int insert(Linked_List** head, char data);
int delete(Linked_List** head, char data);
int isEmpty(Linked_List* head);
void printList(Linked_List* head);
void menu(Linked_List** head);

int main(){
    //head of list
    Linked_List* Head = NULL;
    //start list
    menu(&Head);
    return 0;
}

//insert an element in order (sorted alphabetically)
int insert(Linked_List** head, char data){
    //allocate memory for new link
    Linked_List* node = malloc(sizeof(Linked_List));
    //check to make sure we had sufficient memory
    if(node != NULL){
        //set up new node with relevent data
        node->data = data;
        node->next_node = NULL;
        //create temporary pointers to keep track of where we are in the list
        Linked_List* previous_node = NULL;
        Linked_List* current_node = *head;
        //walk through our list to find where to insert our new node
        //this will sort our list alphabetically
        //example:
            //node |   previous_node current_node
            // |   |        |             |
            // z   |        a     ->      b 
            // z > a ? true : next, z > b ? true : next. End of list
            // z gets inserts here
        while(current_node != NULL && data > current_node->data){
            previous_node = current_node;
            current_node = current_node->next_node;       
        }
        //insert node at beginning of list
        if(previous_node == NULL){
            node->next_node = *head;
            *head = node;
        } else {
            //insert node in between two nodes
            previous_node->next_node = node;
            node->next_node = current_node;
        }
        return 0;
    }
    return -1;
}

//remove element from list
int delete(Linked_List** head, char data){
    //check if list is empty so we don't dereference a null pointer
    if (!isEmpty(*head)) {
        // delete first node if a match is found
        if(data == (*head)->data){
            //create a temporary pointer so we don't lose where we are in
            //in the list when we delete this node
            Linked_List* temp = *head;
            //move head forward one node
            *head = (*head)->next_node;
            //now safely delete the node we wanted to
            free(temp);
            return 0;
        } else {
            //if the first node wasn't a match we move here
            //create temporary pointers to keep track of where we are in the list
            Linked_List* previous_node = NULL;
            Linked_List* current_node = *head;
            //walk through our list to find the node we wish to delete if it exists
            //example:
                //node |   previous_node current_node
                // |   |        |             |
                // b   |        a     ->      b 
                // b == a ? no : next, b == b ? yes : stop.
            while(current_node != NULL && data != current_node->data){
                previous_node = current_node;
                current_node = current_node->next_node;
            }
            //if we're here, that means the node was found. Because current_node != NULL
            if(current_node != NULL){
                Linked_List* temp = current_node;
                previous_node->next_node = current_node->next_node;
                free(temp);
                return 0;
            }
        }
    }
    //if we get here that means the node doesn't exist or list is empty
    return -1;
}

//check if list is empty
int isEmpty(Linked_List* head){
     //if head is NULL, return true, otherwise return false
	return head == NULL;
}

//print the queue
void printList(Linked_List* head){
    //check if list is empty so we don't dereference a null pointer
    if (isEmpty(head)) {
		printf("List is empty.\n");
	} else {
		printf("The list is: ");
        //walkthrough list until we hit the end
		while (head != NULL) {
			printf("%c --> ", head->data);
			head = head->next_node;
		}
		printf("NULL\n");
	}
}

//menu for list operation 
void menu(Linked_List** head){
    //used for user input and menu choice
    char data;
	unsigned choice;
    //print menu instructions
    printf(
        "***LIST MENU***\n"
		"1. Insert element\n"
		"2. Remove element\n"
		"3. Exit\n"
        ": "
    );
    //get the users choice
	scanf("%u", &choice);
	//execute user choice
	while (choice != 3) {
		switch (choice) {
		//insert element
		case 1:
            printf("Please enter your value: ");
            scanf("\n%c", &data);
			if(insert(head, data) == 0){
                printf("Element inserted succesfully\n");
            } else {
	        	fprintf(stderr, "Element not inserted. No memory available.\n");
            }
			printList(*head);
			break;
        //delete element
		case 2:
            printf("Please enter your value: ");
            scanf("\n%c", &data);
			if(delete(head, data) == 0){
                printf("Element deleted successfully\n");
            } else {
                fprintf(stderr, "Deletion failed.\n");                
            }
			printList(*head);
			break;
        //error
		default:
			printf("Invalid choice.\n");
			break;
		}
		printf(": ");
		scanf("%u", &choice);
	}
	printf("Quitting...\n");
}