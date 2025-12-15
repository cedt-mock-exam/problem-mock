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
  //First check if there is tree2 [Testcase 1]
	if(!other.mRoot) return;
	
	//Then check if you need to replace the mRoot or not [Testcase 4 and others]
	//if data is equal and mRoot is leaf node, replace with tree2's mRoot (Replace Graft)
	if(mRoot->data.first == other.mRoot->data.first){
		if(mRoot->left || mRoot->right) return;
		else mRoot = other.mRoot;
	}
	
	//if the root is different, graft
	else graft(mRoot, other.mRoot, other.mSize);
	
	//Don't forget to destroy tree2, to prevent segfault like [Pxxxxxxxxxxxxxxxxxxx]
	other.mRoot = nullptr;
	other.mSize = 0;
	return;
}

//you may use this function to traverse and graft
template <typename KeyT,
          typename MappedT,
          typename CompareT >
void CP::map_bst<KeyT,MappedT,CompareT>::graft(
	CP::map_bst<KeyT,MappedT,CompareT>::node* n, CP::map_bst<KeyT,MappedT,CompareT>::node* m, size_t otherSize
) {
	KeyT key = m->data.first;
	
	//First, Let's compare the nodes
	//Important! use mLess! [if you get 75%, thats the case]
	//current node lower than key, go right
	if(mLess(n->data.first, key)){
		if(n->right){
		  //check in case the right node has the same value as key (replace graft)
			if(n->right->data.first == key){
				if(n->right->left || n->right->right) return; //and check if its leaf node, otherwise no graft
				n->right = m;
				m->parent = n;
				mSize = mSize + otherSize - 1;
			}
			else graft(n->right, m, otherSize);
		}else{
		  //if there's no node here, graft (regular graft)
			n->right = m;
			m->parent = n;
			mSize = mSize + otherSize;
		}
	}
	//current node higher than key, go left
	else{
		if(n->left){
		   //check in case the left node has the same value as key (replace graft)
			if(n->left->data.first == key){
				if(n->left->left || n->left->right) return; //and check if its leaf node, otherwise no graft
				n->left = m;
				m->parent = n;
				mSize = mSize + otherSize - 1;
			}
			else graft(n->left, m, otherSize);	
		}else{
		  //if there's no node here, graft (egular graft)
			n->left = m;
			m->parent = n;
			mSize = mSize + otherSize;
		}
	}

	return;
}

#endif
