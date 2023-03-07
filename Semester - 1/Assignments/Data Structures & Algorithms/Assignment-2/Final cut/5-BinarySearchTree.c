/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective: Write a program to maintain a priority queue using a binary search tree
*/

#include<stdio.h>
#include<stdlib.h>

/*
This structure defines a node of binary tree.
Left part of node can have a subtree or an operand. isLeftSubTree is a flag to indicate what is actually stored in union.
Same goes with right part.
*/
struct Element{
    struct Element * leftSubTree;
    int key;
    struct Element * rightSubTree;
};

//Pointer to root of the binary tree.
struct Element * rootNode;

//Print binary search tree using inorder tree traversal. (Left-Root-Right format)
int inorderTraversal(struct Element * parent){
    if(parent -> leftSubTree != NULL){
        inorderTraversal(parent -> leftSubTree);
    }
    printf("%d\t", parent -> key);
    if(parent -> rightSubTree != NULL){
        inorderTraversal(parent -> rightSubTree);
    }
    return 0;
}

//This function return NULL in case tree is empty else it will return the expected parent node of given key
struct Element * search(struct Element * rootNode, int key) {
    struct Element * currElem;
    currElem = rootNode;
    while(currElem != NULL){
        //If given key is lesser than the node's key then go down for left subtree and check whether left child is the key we are looking for
        if((key < currElem -> key) && (currElem -> leftSubTree != NULL && currElem -> leftSubTree -> key != key)) {
            currElem = currElem -> leftSubTree;
        } else if((key > currElem -> key) && (currElem -> rightSubTree != NULL && currElem -> rightSubTree -> key != key)){
            //else if key is greater than the node's key then go down for right subtree and check whether right child is the key we are looking for
            currElem = currElem -> rightSubTree;
        } else {
            break;
        }
    }
    return currElem;
}

//This function inserts the new element at its proper position
int insert(struct Element ** rootNode, int key){
    struct Element * currElem, * prevElem;
    //Search the tree for expected parent
    prevElem = search(* rootNode, key);
    currElem = (struct Element *) malloc(sizeof(struct Element));
    currElem -> key = key;
    //If parent is NULL then tree is empty, make the node root
    if(prevElem == NULL){
        * rootNode = currElem;
    } else if(prevElem -> key < key && prevElem -> rightSubTree == NULL){
        //If key is greater than parent's key and right part of parent is empty then add new node as a right child of parent
        prevElem -> rightSubTree = currElem;
    } else if(prevElem -> key > key && prevElem -> leftSubTree == NULL){
        //If key is lesser than parent's key and left part of parent is empty then add new node as a left child of parent
        prevElem -> leftSubTree = currElem;
    } else {
        //If key already exists then exit from function
        printf("Element already exists\n");
        free(currElem);
    }
    return 0;
}

//This function delete given key element from the tree
int delete(struct Element ** rootNode, int key){
    struct Element *f, *p, * q, *r, *s;
    //Expected parent node of key element is found
    q = search(* rootNode, key);
    //If key is lesser than parent's key then mark it's left child as p
    if(key < q -> key){
        p = q -> leftSubTree;
    } else {
        //If key is greater than parent's key then mark it's right child as p
        p = q -> rightSubTree;
    }
    //If p has single child then mark its child as r
    if(p -> leftSubTree == NULL){
        r = p -> rightSubTree;
    } else if(p -> rightSubTree == NULL){
        r = p -> leftSubTree;
    } else {
        //Else go for current p's inorder successor
        f = p;
        r = p -> rightSubTree;
        s = s -> leftSubTree;
        while(s != NULL){
            f = r;
            r = s;
            s = s -> leftSubTree;
        }
        q = f;
        p = r;
    }
    //Compare inorder successor and expected parent node q's key values, if successor has lesser then make it left child of expected parent q else make it right child
    if(p -> key < q -> key){
        q -> leftSubTree = r;
    } else {
        q -> rightSubTree = r;
    }
    //Since we removed p, free the storage it occupied
    free(p);
    return 0;
}

int main(){
    int i, numberOfElements;
    int sequence[] = {2, 4, 1, 6, 8, 10, 34};
    numberOfElements = 7;
    for(i = 0; i < numberOfElements; i++){
        insert(&rootNode, sequence[i]);
    }
    inorderTraversal(rootNode);
    printf("\n");
    delete(&rootNode, 8);
    inorderTraversal(rootNode);
    printf("\n");
    return 0;
}
