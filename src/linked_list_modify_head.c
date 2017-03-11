/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/

/* the way to modify head pointer of list
1. Make head pointer global

    // global head pointer
    struct node *head = NULL;

    // function to delete first node
    // See http://ideone.com/ClfQB for complete program and output
    void deleteFirst()
    {
        if(head != NULL)
        {
           // store the old value of head pointer
           struct node *temp = head;

           // Change head pointer to point to next node
           head = head->next;

           // delete memory allocated for the previous head node
           free(temp);
        }
    }

2. Return head pointer

    // function to delete first node
    // See http://ideone.com/P5oLe for complete program and output
    struct node *deleteFirst(struct node *head)
    {
        if(head != NULL)
        {
           // store the old value of head pointer
           struct node *temp = head;

           // Change head pointer to point to next node
           head = head->next;

           // delete memory allocated for the previous head node
           free(temp);
        }

        return head;
    }

3. Use Double Pointer,
    This approach follows the simple C rule:
    if you want to modify local variable of one function inside another function,
    pass pointer to that variable.

    // function to delete first node:
    // See http://ideone.com/9GwTb for complete program and output
    void deleteFirst(struct node **head_ref)
    {
        if(*head_ref != NULL)
        {
           // store the old value of pointer to head pointer
           struct node *temp = *head_ref;

           // Change head pointer to point to next node
           *head_ref = (*head_ref)->next;

           // delete memory allocated for the previous head node
           free(temp);
        }
    }

4. delete the second node,
   modify data of head, copy data from the next node to head,
   then change next pointer of head to the next of second node,
   finally delete the second node.
   void deleteFirst( struct node * head )
   {
        if( head->next == NULL )
        {
            //can't delete the head, for this is the only node
            return;
        }

        node_t * tmp = head->next;
        head->data = head->next->data;
        head->next = head->next->next;

        free(tmp);
   }
*/
