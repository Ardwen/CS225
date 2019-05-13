/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  while(head_){
    tail_ = head_->next;
    delete(head_);
    head_ = tail_;
  }

  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_== NULL) {
    tail_ = newNode;
  }
  head_  = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode *newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;

  length_++;
  /// @todo Graded in MP3.1
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The numb%ser of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if (!start) {
    return NULL;
  }
  if (splitPoint == 0) {
    return start;
  }
//&& (curr != NULL)
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if (!curr) {
    return NULL;
  }

  curr->prev->next = NULL;
  curr->prev = NULL;
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  if (length_<=2) {
    return;
  }
  ListNode * curr = head_;
  bool index = false;
  while(curr &&curr !=tail_) {
    if (index) {
      ListNode * parent = curr -> prev;
      ListNode * child = curr-> next;
      parent -> next = child;
      child -> prev = parent;
      tail_ -> next = curr;
      curr -> prev = tail_;
      tail_ = curr;
      curr -> next = NULL;
      curr = child;
    }else{
      curr = curr -> next;
    }
    index = !index;
  }
  /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (startPoint==NULL || startPoint->next==NULL)
	{
		return;
	}
	// define 2 pointers
	ListNode * current = startPoint;
	ListNode * tmp = startPoint->next;

	while (current != endPoint)
	{
		current->next = current->prev;
		current->prev = tmp;
		current = tmp;
		tmp = tmp->next;
	}
	current->next = current->prev;
	current->prev = tmp;
  ListNode *startPointnext = startPoint -> next;
  ListNode *endPointprev = endPoint -> prev;
  if (startPointnext != NULL) {
    startPointnext -> next = endPoint;
    endPoint->prev = startPointnext;
  } else {
    endPoint -> prev = NULL;
  }
  if (endPointprev != NULL) {
    startPoint -> next = endPointprev;
    endPointprev -> prev = startPoint;
  } else {
    startPoint -> next = NULL;
  }
  tmp = startPoint;
  startPoint = endPoint;
  endPoint = tmp;
  return;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if(n>=length_){//full reverse
      reverse(head_, tail_);
      return;
    }
    if(head_ == NULL || n <= 1 ){//no reverse
      return;
    }

    ListNode* startPoint;
    ListNode* tmp= head_;

    ListNode* endPoint = head_;
    int  terms_left=  length_;
    bool ChangeHead = true; //record the number of swaps for head EDGE!!!
    while(terms_left > n && tmp!=NULL){
      startPoint = tmp;
      for(int i=1; i<n; i++){
        if (tmp != NULL){
        tmp = tmp->next;
      } else{
        break;
      }
      }
      if(ChangeHead){
        head_ = tmp;
        ChangeHead = false;
      }
      endPoint = tmp;
      tmp = tmp->next;
      reverse(startPoint,endPoint);
      terms_left -= n;
    }
    if(terms_left != 0){
      reverse(tmp,tail_);
    }
    return;
  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

 if (first == NULL) {
   return second;
 }
 if (second == NULL) {
   return first;
 }
 ListNode* newhead;
 ListNode* f = first;
 ListNode* s = second;
 ListNode* tmp;

 if (first -> data < second -> data){
   newhead = f;
   f = f -> next;
 } else {
   newhead = s;
   s = s -> next;
 }
 tmp = newhead;
 while (f != NULL && s != NULL) {
   if(s->data < f->data ){
        tmp->next = s; //link the old to the new
        s = s->next; //move s to the next variable on the list
        tmp->next->prev = tmp; //link the new to the old
        tmp = tmp->next;
      } else{
        tmp->next = f;
        f = f->next; //move F to the next variable on the list
        tmp->next->prev = tmp;
        tmp = tmp->next;
      }

    }
    if(f !=NULL){
      //append F to the list
      tmp->next = f;
      f->prev = tmp;
      return newhead;
    }
    if(s != NULL){
      //append s to the list
      tmp->next = s;
      s->prev = tmp;
      return newhead;
    }
    second = NULL;
    return newhead;

 }

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.
  if (chainLength == 1) {
    return start;
  }
  int splitpoint = chainLength / 2;
  ListNode *secondHead;
  ListNode *firstHead;
  ListNode *second;
  second = split(start, splitpoint);
  firstHead = mergesort(start, splitpoint);
  secondHead = mergesort(second, chainLength - splitpoint);
  return merge(firstHead, secondHead);
}
