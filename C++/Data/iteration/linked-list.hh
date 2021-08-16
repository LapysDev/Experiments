struct LinkedList final {
  LinkedList *next;
  unsigned char value;
  
  LinkedList() : next(NULL), value(0u) {}
};
