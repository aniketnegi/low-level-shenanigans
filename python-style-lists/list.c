#include "list.h"
#include <stdlib.h>

list_t *list_create() {
  list_t *new_list = malloc(sizeof(list_t));
  new_list->size = 0;
  new_list->head = NULL;
  new_list->tail = NULL;

  return new_list;
}

void list_destroy(list_t *list) {
  list_element_t *curr = list->head;
  while (curr != NULL) {
    list_element_t *next = curr->next;
    free(curr);
    curr = next;
  }
  free(list);
}

// brah totally forgot that list access in O(1) in python. maybe i can have the
// head of list_t as an array of pointers to each list_element_t

// https://docs.python.org/3/glossary.html#term-list
// https://docs.python.org/3/c-api/init_config.html#pywidestringlist
