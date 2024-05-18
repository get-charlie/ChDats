#ifndef _CHSTACK_
#define _CHSTACK_

// Forward declaration
typedef struct Stack Stack;

// Returns a new empty stack
Stack*  stack_new       ();
// Pushes an object on top of the stack, returns 0 if succesful 1 otherwise.
int     stack_push      (Stack* stack, void* obj);
// Pops the object on top of the stack and returns it, returns null pointer if the stack is empty.
void*   stack_pop       (Stack* stack);
// Returns the object on top of the stack without removing it, returns null pointer if the stack is empty.
void*   stack_peek      (Stack* stack);
// Returns the size of the stack.
size_t  stack_size      (Stack* stack);
// Clears the contents of the stack, returns the number of elements cleared.
size_t  stack_clear     (Stack* stack);
// Destroys the stack freeing memory, returns the number of elements cleared.
size_t  stack_destroy   (Stack** stack);

#ifdef IMPLEMENT_CHSTACK

struct Node{
    void* obj;
    struct Node* next;
};
typedef struct Node Node;

struct Stack{
    Node* head;
    size_t size;
}; 

static Node* node_new(Node* next, void* obj){
    Node* new = malloc(sizeof(Node));
    new->obj = obj;
    new->next = next;
    return new;
}

Stack* stack_new(){
    Stack* new = malloc(sizeof(Stack));
    if(new == NULL){
        return NULL;
    }
    new->head = NULL;
    new->size = 0;
    return new;
}

int stack_push(Stack* stack, void* obj){
    if(stack == NULL){
        return 1;
    }
    Node* new = node_new(stack->head, obj);
    if(new == NULL){
        return 1;
    }
    stack->head = new;
    stack->size++;
    return 0;
}

void* stack_pop(Stack* stack){
    if(stack == NULL || stack->head == NULL){
        return NULL;
    }
    void* obj = stack->head->obj;
    Node* delete = stack->head;
    stack->head = stack->head->next;
    free(delete);
    stack->size--;
    return obj;
}

void* stack_peek(Stack* stack){
    if(stack == NULL || stack->head == NULL){
        return NULL;
    }
    return stack->head->obj;
}

size_t stack_size(Stack* stack){
    if(stack == NULL){
        return 0;
    }
    return stack->size;
}

size_t stack_clear(Stack* stack){
    if(stack == NULL){
        return 0;
    }
    size_t cleared = stack->size;
    Node* current = stack->head;
    while(current != NULL){
        Node* delete = current;
        current = current->next;
        free(delete);
    }
    stack->head = NULL;
    stack->size = 0;
    return cleared;
}

size_t stack_destroy(Stack** stack){
   size_t cleared = stack_clear(*stack); 
   free(*stack);
   *stack = NULL;
   return cleared;
}

#endif // IMPLEMENT_CHSTACK
#endif
