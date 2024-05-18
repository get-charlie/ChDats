#ifndef _CHSTACK_
#define _CHSTACK_

Stack*  stack_new       ();
int     stack_push      (Stack* stack, void obj);
void*   stack_pop       (Stack* stack);
void*   stack_peek      (Stack* stack);
int     stack_size      (Stack* stack);
int     stack_clear     (Stack* stack);
int     stack_destroy   (Stack* stack);

#ifdef IMPLEMENT_CHSTACK

struct Node{
    void* obj;
    struct Node* next;
}
typedef Node Node;

typedef struct{
    Node* head;
    size_t size;
}Stack; 

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
    stack->head = NULL;
    stack->size = 0;
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
    if(stack == NULL){
        return NULL;
    }
    return stack->head->obj;
}

int stack_size(Stack* stack){
    if(stack == NULL){
        return 0;
    }
    return stack->size;
}

int stack_clear(Stack* stack){
    if(stack == NULL){
        return 0;
    }
    int cleared = stack->size;
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

int stack_destroy(Stack* stack){
   int cleared = stack_clear(stack); 
   free(stack);
   return cleared;
}

#endif // IMPLEMENT_CHSTACK
#endif
