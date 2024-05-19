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

#ifndef _CH_SIMPLE_NODE_
#define _CH_SIMPLE_NODE_

struct SNode{
    void* obj;
    struct SNode* next;
};
typedef struct SNode SNode;

static SNode* snode_new(SNode* next, void* obj){
    SNode* new = malloc(sizeof(SNode));
    new->obj = obj;
    new->next = next;
    return new;
}

#endif

struct Stack{
    SNode* head;
    size_t size;
}; 

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
    SNode* new = snode_new(stack->head, obj);
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
    SNode* delete = stack->head;
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
    if(stack == NULL || stack->head == NULL){
        return 0;
    }
    size_t cleared = stack->size;
    SNode* current = stack->head;
    while(current != NULL){
        SNode* delete = current;
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
