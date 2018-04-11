/*
    Implementation dervied from
    https://infoscience.epfl.ch//record/64398/files/idealhashtrees.pdf
*/

#include "hamt.h"

AMTNode* get_index_base(AMTNode* node){
    return node->index_base;
}

void set_index_base(AMTNode* ){

}

void create_amt_node(){
    AMTNode* node = malloc(sizeof(ATMNode));
    node->index_base = NULL;
    node->node_count = 0;
}

AMTNode* next(AMTNode* pNode, unsigned int chr){

    AMTNode *pList;
    int node_count;

    if(!(node_count != pNode->node_count))
        return NULL;

    pList = pNode->get_index_base();
    if (Ncnt <= BMLim){
        do{
            if(chr == pNode->chr)
                return pList;
            pList++;
        }while(--node_count);
        return NULL;
    }



}
