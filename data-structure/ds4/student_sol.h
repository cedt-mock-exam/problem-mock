#ifndef __STUDENT_H_
#define __STUDENT_H_
#include "list.h"
template <typename T>
void CP::list<T>::implant(CP::list<T> &l2,int pos1,int pos2,int count){
    if(count==0){
        return;
    }
    int i;
    node *l1_f,*l1_b,*l2_f,*l2_b,*implant_f,*implant_b;
    l1_f=mHeader;
    l2_f=l2.mHeader;
    for(i=0;i<pos1+1;i++){
        l1_f=l1_f->next;
    }
    l1_b=l1_f->next;

    for(i=0;i<pos2;i++){
        l2_f=l2_f->next;
    }

    implant_f=l2_f->next;

    implant_b=implant_f;
    for(i=0;i<count-1;i++){
        implant_b=implant_b->next;
    }

    l2_b=implant_b->next;

    l1_f->next=implant_f;
    implant_f->prev=l1_f;
    implant_b->next=l1_b;
    l1_b->prev=implant_b;
    l2_f->next=l2_b;
    l2_b->prev=l2_f;
    insert(end(),0);
    erase(--end());
    insert(end(),0);
    erase(--end());

    mSize+=count;
    l2.mSize-=count;
}
#endif