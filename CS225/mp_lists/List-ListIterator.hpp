
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        if (position_) {
          position_ = position_ -> next;
        }
        return *this;
    }

    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded inssssssssssss MP3.1
        ListNode* r = position_;
        position_ = position_ -> next;
        return ListIterator(r);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        if (position_) {
          position_ = position_ -> prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        ListNode* r = position_;
        if (position_) {
          position_ = position_ -> prev;
        }

        return ListIterator(r);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return position_ == rhs.position_;
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
