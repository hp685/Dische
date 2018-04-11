#define MULTIPLIER 97

unsigned long hash(char* s){

  unsigned long h;
  unsigned char* us;

  us = (unsigned char* ) s;
  h = 0;
  while( *us != '\0' ){
    h = h * MULTIPLIER + *us;
    us++;
  }

  return h;
}

unsigned long get_index(char* key){

  unsigned long index;
  unsigned long hash_code = hash(key);

  index = hash_code % MAX_BUCKETS;
  return index;
}

char* get(char* key){

  index = get_index(key);
  DictNode _dn = DictNode[index];
  if ( _dn->key == NULL ){
    return NULL;
  }
  if ( strcmp(_dn->key, key) == 0 ){
    return _dn->value;
  }
  else{

    while ( _dn ){

      _dn = _dn->next;
      if ( strcmp(_dn->key, key) == 0 ){
        return _dn->value;
      }
    }
  }
  return NULL;

}


char* set(char* key, char* value){

}
