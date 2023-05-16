#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list_t *list_create() {
  list_t *new_list = (list_t *)malloc(sizeof(list_t));

  // initially list will have size 0, capacity 0
  new_list->size = 0;
  new_list->capacity = 0;

  new_list->head = NULL;
  new_list->tail = NULL;

  return new_list;
}

void list_destroy(list_t *list) {
  if (list->size == 0 && list->head == NULL && list->tail == NULL) {
    free(list);
    fprintf(stdout, "Destroyed list!\n");
    return;
  }

  list_element_t *curr = list->head;
  list_element_t *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  list->head = NULL;
  fprintf(stdout, "Destroyed list!\n");
}

void list_print(list_t *list) {
  if (list->size == 0 && list->head == NULL && list->tail == NULL) {
    fprintf(stdout, "The List is empty!\n");
    return;
  }
  size_t list_size = list->size;
  list_element_t *curr = list->head;

  while (curr != NULL) {
    switch (curr->data_type) {
      case INT: {
        fprintf(stdout, "List[%zu] = %d\n", curr->posn, *((int *)curr->data));
        break;
      }
      case FLOAT: {
        fprintf(stdout, "List[%zu] = %f\n", curr->posn, *((float *)curr->data));
        break;
      }
      case STRING: {
        fprintf(stdout, "List[%zu] = %f\n", curr->posn, *((char *)curr->data));
      }
      default: {
        fprintf(
            stdout,
            "Sorry, couldn't determine the datatype of element at posn: %zu",
            curr->posn);
        fprintf(stdout,
                "Please confirm that it is on of the following:\n<int>, "
                "<float>, <char>, <string>\n");
      }
    }
    curr = curr->next;
  }
}

// brah totally forgot that list access in O(1) in python. maybe i can have the
// head of list_t as an array of pointers to each list_element_t

// https://docs.python.org/3/glossary.html#term-list
// https://docs.python.org/3/c-api/init_config.html#pywidestringlist
