#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
       
typedef struct s_node {
    int key;
    struct s_node **next;  
} s_node;


typedef struct SkipList {
    int level;  
    s_node *root;
} SkipList;

int randomLevel(int max_level) {
    int level = 1;
    while (((float)rand() / RAND_MAX) < 0.5 && level < max_level)
        level++;
    return level;
}

s_node* node(int key, int level) {
    s_node *node = (s_node*)malloc(sizeof(s_node));
    node->key = key;
    node->next = (s_node**)malloc(sizeof(s_node*) * (level + 1));
    for (int i = 0; i <= level; i++)
        node->next[i] = NULL;
    return node;
}

SkipList* list_init(int max_level) {
    SkipList *new = (SkipList*)malloc(sizeof(SkipList));
    new->level = 0;
    new->root = node(INT_MIN, max_level);
    return new;
}


void insert(SkipList *list, int key,int max_level) {
    s_node *update[max_level+1];
    s_node *x=list->root;
    for (int i = list->level; i >= 0; i--) {
        while (x->next[i] != NULL && x->next[i]->key < key) {
            x=x->next[i];
        }
        update[i] = x; 
    }

    x = x->next[0];
    if (x == NULL || x->key != key) {
        int lvl = randomLevel(max_level);
        if(lvl>list->level) {
            for (int i = list->level + 1; i <= lvl; i++) {
                update[i] = list->root;
            }
            list->level = lvl;
        }
        s_node *newNode = node(key, lvl);
        for (int i = 0; i <= lvl; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }
}

int search(SkipList *list, int key) {
    s_node *x = list->root;
    int steps=0;
    for (int i = list->level; i >= 0; i--) {
        while (x->next[i] != NULL && x->next[i]->key < key) {
            if ( x->key == key){
                return steps;
            }
            x = x->next[i];
            steps++;
        }
        if ( x->key == key){
            return steps;
        }
    }
    return steps;  
}



void print_skp(SkipList *list) {

    for (int i = list->level; i >= 0; i--) {
        s_node *node = list->root->next[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("%d ", node->key);
            node = node->next[i];
        }
        printf("\n");
    }
}

void free_skp(SkipList *list) {
    if (list == NULL) return;
    s_node *current = list->root;
    while (current != NULL) {
        s_node *next = current->next[0];
        free(current->next);  
        free(current);         
        current = next;
    }
    free(list);
}


int main(int argc, char * argv[]) {
    if(argc==2){
        int i,size=atoi(argv[1]);
        int avg_sz=1000000;
        int val;
        int step_sz=avg_sz/2;
        srand(time(NULL));
        clock_t start,end;
        int count_steps=0;
        double time_taken=0;
        int *array = (int*)malloc( (size)* sizeof(int));
        int max_level=log2(atof(argv[1]));
        SkipList *list = list_init(max_level);
        printf("max level: %d\n",max_level);
        start = (double)clock();
        for(i=0;i<size;i++){
            val=rand()|1;
            insert(list,val,max_level);
            array[i]=val;
        }
        end = (double)clock();
        time_taken= ((end - start) / CLOCKS_PER_SEC);
        //hevleh
        //print_skp(list);
        printf(" skip baiguulah hugatsaa  %.2fs \n",time_taken);
        start = (double)clock();
        for(i=0;i<step_sz;i++){
                count_steps+=search(list,array[(rand()%size)]);
        }
        //baihgui element haih
        for(i=0;i<step_sz;i++){
                // 11..0 masklaad tuuniigee and hiij zovhon tegsh too generateldeg bolgoson
                count_steps+=search(list,rand()&(~1));
        }
        end = (double)clock();
        time_taken= ((end - start) / CLOCKS_PER_SEC);
        printf("hailt hiisen hugatsaa %.2fs ,dundaj alham  %.2f \n",time_taken,((double)count_steps/avg_sz));
        free_skp(list);
        free(array);
    }
    return 0;
}
