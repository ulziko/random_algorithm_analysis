#include<stdio.h>
#include<stdlib.h>
#include<time.h>


struct Elm {
    int k;
    int p;
    struct Elm *L;
    struct Elm *R;
};
typedef struct Elm Elm;


// node шинээр үүсгэн хаягийг нь буцаах функц
static Elm *node(int x)
{
        Elm *node;
        node = (struct Elm *)malloc(sizeof(struct Elm));
        node->k = x;
        node->p= rand()%100; 
        node->L = NULL;
        node->R = NULL;
};

struct BST {
    Elm *root;
};
typedef struct BST BST;


static int compare(int root, int x)
{
        if (root < x)
        {
                return 1;
        }
        else if (root > x)
        {
                return -1;
        }
        else
        {
                return 0;
        }
}
Elm *right_rotate(Elm *root){
        Elm *tmp=root->L;
        root->L=tmp->R;
        tmp->R=root;
        return tmp;
}

Elm *left_rotate(Elm *root){
        Elm *tmp=root->R;
        root->R=tmp->L;
        tmp->L=root;
        return tmp;
}



static Elm *insert(Elm *root, int x)
{
        if (!root)
        {       
                root = node(x);
                return root;
        }
        int cmp = compare(root->k, x);
        if (cmp == 1)
        {
                root->R= insert(root->R, x);
                if (root->R->p > root->p){
                        root = left_rotate(root);
                }
                
        }
        else if (cmp == -1)
        {
                root->L= insert(root->L, x);
                  // Fix the heap property if it is violated
                if (root->L->p > root->p){
                        root = right_rotate(root);
                }
        }
        else
        {
                root->k= x;
        }

        return root;
}

int  search(Elm *root, int x)
{
        int count=0;
        while (root != NULL)
        {
                int cmp = compare(root->k, x);
                count++;
                if (cmp == 1)
                {
                        root = root->R;
                }
                else if (cmp == -1)
                {
                        root = root->L;
                }
                else
                {
                        return count;
                }
        }
        return count;
}



static void inorder(Elm *root)
{
        if (root == NULL)
        {
                return;
        }
        else{
                inorder(root->L);
                printf("root->%d, p=%d ",root->k,root->p);
                if(root->L!=NULL){
                        printf("root->L %d ",root->L->k);
                }
                if(root->R!=NULL){
                        printf("root->R %d ",root->R->k);
                }
                printf("\n");
                inorder(root->R);
        }
}
       



void bs_put(BST *ptree, int k)
{
        // Generate random numbers
        ptree->root = insert(ptree->root,k);
}



void bs_inorder(const BST *ptree)
{
        inorder(ptree->root);
}


void free_tree(Elm * node){
        if (node != NULL) {
             free_tree(node->R);
             free_tree(node->L);
             free(node);
        }
}


int main(int argc,char *argv[])
{
        if(argc==2){
                int i;
                BST bst;
                bst.root=NULL;
                BST *bstp=&bst;
                int val,count_steps=0;
                int avg_sz=1000000;
                int step_sz=avg_sz/2;
                srand(time(NULL));
                clock_t start,end;
                double time_taken=0;
                int size=atoi(argv[1]);
                int *array = (int*)malloc( (size)* sizeof(int));
                //modoo baiguulah
                start = (double)clock();
                for(i=0;i<size;i++){
                        //rand 1rei or hiisner dan sondgoi too bolno
                        val=rand()|1;
                        bs_put(bstp,val);
                        array[i]=val;
                }
                end = (double)clock();
                //printing purpose
                //inorder(bstp->root);
                time_taken= ((end - start) / CLOCKS_PER_SEC);
                printf(" treap baiguulah hugatsaa  %.2fs \n",time_taken);
                start = (double)clock();
                for(i=0;i<step_sz;i++){
                        count_steps+=search(bstp->root,array[(rand()%size)]);
                }
                //baihgui element haih
                for(i=0;i<step_sz;i++){
                        // 11..0 masklaad tuuniigee and hiij zovhon tegsh too generateldeg bolgoson
                        count_steps+=search(bstp->root,rand()&(~1));
                }
                end = (double)clock();
                time_taken= ((end - start) / CLOCKS_PER_SEC);
                printf("hailt hiisen hugatsaa %.2fs ,dundaj alham  %.2f \n",time_taken, (double)count_steps/avg_sz);
                free_tree(bstp->root);
                free(array);
            }
        return 0;
}