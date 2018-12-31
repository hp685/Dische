#define SET_NODE(Data* head, void* key, void* value){\
  head->key = (char*) malloc( (strlen(key) + 1) * sizeof(char));\
  head->value = (char*) malloc( (strlen(value) + 1) * sizeof(char));\
  strcpy(head->key, key);\
   strcpy(head->value, value);\
}					       

#define LIST_INSERT(node, list)					\
  for (node=list->head; node != NULL; node=node->next){          \
    if (strcmp(node->key, key) == 0)				 \
      SET_NODE(node, key, value)				 \
      }								 \
