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
	if(other.mRoot->data.first == mRoot->data.first){
		if(other.mRoot->left || other.mRoot->right) return;
		else{
			mRoot = other.mRoot;
		}
	}else{
		graft(mRoot, other.mRoot, other.mSize);
	}

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
	//your code here
	KeyT value = m->data.first;
	if(mLess(n->data.first, value)){
		if(n->right == nullptr){
			n->right = m;
			m->parent = n;
			mSize += s;
			return;
		} else if(n->right->data.first == value){
			if(n->right->left || n->right->right) return;
			n->right = m;
			m->parent = n;
			mSize += s-1;
			return;
		} else{
			graft(n->right, m, s);
			return;
		}
	}else{
		if(n->left == nullptr){
			n->left = m;
			m->parent = n;
			mSize += s;
			return;
		} else if(n->left->data.first == value){
			if(n->left->left || n->left->right) return;
			n->left = m;
			m->parent = n;
			mSize += s-1;
			return;
		} else{
			graft(n->left, m, s);
			return;
		}
	}
	return;
}

#endif
