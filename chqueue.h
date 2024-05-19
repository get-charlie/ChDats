#ifndef _CHQUEUE_
#define _CHQUEUE_

// Forward declaration
typedef struct Queue Queue;

// Create a new empty queue.
Queue*  queue_new       ();
// Enqueue an object to the end of the queue, returns 0 if succesful, 1 otherwise.
int     queue_enqueue   (Queue* queue, void* obj);
// Retunrs the first element on the queue and dequeues it, returns null if the queue is empty.
void*   queue_dequeue   (Queue* queue);
// Retunrs the first element on the queue, null if the queue is empty.
void*   queue_peek      (Queue* queue);
// Returns the size of the queue.
size_t  queue_size      (Queue* queue);
// Clears the queue without destroying it, returns the number of elements cleared.
size_t  queue_clear     (Queue* queue);
// Destroys the queue freeing memory, returns the number of elements cleared.
size_t  queue_destroy   (Queue** queue);

#ifdef IMPLEMENT_CHQUEUE

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

struct Queue{
    SNode* tail;
    SNode* head;
    size_t size;
}; 
typedef struct Queue Queue;

Queue* queue_new(){
    Queue* new = malloc(sizeof(Queue));
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}

int queue_enqueue(Queue* queue, void* obj){
    if(queue == NULL){
        return 1;
    }
    SNode* new = snode_new(NULL, obj);
    if(new == NULL){
        return 1;
    }
    if(queue->head == NULL){
        queue->tail = new;
        queue->head = new;
    }else{
        queue->tail->next = new;
        queue->tail = new;
    }
    queue->size++;
    return 0;
}

void* queue_dequeue(Queue* queue){
    if(queue == NULL || queue->head == NULL){
        return NULL;
    }
    void* obj = queue->head->obj;
    SNode* delete = queue->head;
    queue->head = queue->head->next;
    free(delete);
    queue->size--;
    if(queue->head == NULL){
        queue->tail = NULL;
    }
    return obj;
}

void* queue_peek(Queue* queue){
    if(queue == NULL || queue->head == NULL){
        return NULL;
    }
    return queue->head->obj;
}

size_t queue_size(Queue* queue){
    if(queue == NULL){
        return 0;
    }
    return queue->size;
}

size_t queue_clear(Queue* queue){
    if(queue == NULL || queue->head == NULL){
        return 0;
    }
    size_t cleared = queue->size;
    SNode* current = queue->head;
    while(current != NULL){
        SNode* delete = current;
        current = current->next;
        free(delete);
    }
    queue->head = NULL; 
    queue->tail = NULL;
    queue->size = 0;
    return cleared;
}

size_t queue_destroy(Queue** queue){
    size_t cleared = queue_clear(*queue);    
    free(*queue);
    *queue = NULL;
    return cleared;
}

#endif // IMPLEMENT_CHQUEUE
#endif
