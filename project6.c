

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))
// pad size x 
// mark in use 
// shange size "remaining space"
//return node +padded size 

struct block *head = NULL;

struct block {
    int size;            // Size in bytes
    int in_use;          // Boolean
    struct block *next;
};

void *myalloc(int size){
    if(head == NULL){
        void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                  MAP_ANON|MAP_PRIVATE, -1, 0);
        int data_size = 1024 - PADDED_SIZE(sizeof(struct block));
        head = heap ;
        head -> size = data_size;
        head -> next = NULL ;
        head -> in_use= 0;
        
    }

    struct block *current = head ;
   
    while (current != NULL){
        

        if(current->in_use==0){
            if (current->size >= PADDED_SIZE(size)){
                current->in_use=1;
                return PTR_OFFSET(current ,PADDED_SIZE(sizeof(struct block) ));
                // current->size= PADDED_SIZE(size);

            }

            }
    current= current->next;
    }

    return NULL;

}
void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}



int main(){
  void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}

// // int *p = myalloc(sizeof(int) * 5);
// }


// struct node *node = PTR_OFFSET(y, -PADDED_SIZE(sizeof(structnode)))



// free (pointer )
// go back the size of the padding 
//       // struct node *node = PTR_OFFSET(y, -PADDED_SIZE(sizeof(structnode)))
//   set the nodes in use to 0 