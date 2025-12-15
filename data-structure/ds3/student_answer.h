#ifndef __STUDENT_H_
#define __STUDENT_H_
#include "map_bst.h"

//this is the modify() function to be submitted
template <typename KeyT,
          typename MappedT,
          typename CompareT >
void CP::map_bst<KeyT,MappedT,CompareT>::modify(
	CP::map_bst<KeyT,MappedT,CompareT> &other
) {
	if(other.mRoot == nullptr) return;
	graft(this->mRoot, other.mRoot, other.mSize);
	other.mRoot = nullptr;
	other.mSize = 0;
	return;
}

//you may use this function to find the grafting point
template <typename KeyT,
          typename MappedT,
          typename CompareT >
void CP::map_bst<KeyT,MappedT,CompareT>::graft(
	CP::map_bst<KeyT,MappedT,CompareT>::node* n, CP::map_bst<KeyT,MappedT,CompareT>::node* m, size_t s
) {
	if (n==nullptr) return;
	if (m==nullptr) return;
	
	//if data is the same -> replace node
	if (n->data.first == m->data.first){
		if(n->left || n->right) return;
		if(n->parent){
			if(mLess(n->data.first, n->parent->data.first)){
				n->parent->left = m;
				m->parent = n->parent;
			} else {
				n->parent->right = m;
				m->parent = n->parent;
			}
			mSize = mSize + s - 1;
			return;
		}
		//only if replacing at root
		else{
			mRoot = m;
			mSize = s;
			return;
		}
	}
	
	//if less go left, if no left, place m
	else if (mLess(m->data.first, n->data.first)){
		if(n->left){
			graft(n->left, m, s);
			return;
		} else {
			n->left = m;
			m->parent = n;
			mSize = mSize + s;
			return;
		}
	}
	
	//if more go right, if no right, place m 
	else{
		if(n->right){
			graft(n->right, m, s);
			return;
		} else {
			n->right = m;
			m->parent = n;
			mSize = mSize + s;
			return;
		}
	}
}

#endif
