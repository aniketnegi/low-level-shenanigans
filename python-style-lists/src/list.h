#ifndef _LIST_H_
#define _LIST_H_

#include <sys/types.h>

typedef enum {
  INT,
  FLOAT,
  STRING,
  // LIST,
} data_type_t;

typedef struct list_element_t {
  size_t posn;
  void *data;
  data_type_t data_type;
  list_element_t *prev;
  list_element_t *next;
} list_element_t;

typedef struct list_t {
  size_t size;
  size_t capacity;
  list_element_t *head;
  list_element_t *tail;
} list_t;

list_t *list_create();

void list_destroy(list_t *list);

void list_print(list_t *list);

// void list_append(list_t *list, void *data);

// void list_prepend(list_t *list, void *data);

// void list_insert(list_t *list, size_t index, void *data);

// void *list_get(list_t *list, size_t index);

// void list_remove(list_t *list, size_t index);

// size_t list_size(list_t *list);

// list_t *list_copy(list_t *list);

// void list_reverse(list_t *list);

// void list_map(list_t *list, void (*function)(void *));

// void list_filter(list_t *list, bool (*function)(void *));

// void list_fold(list_t *list, void *initial_value,
//                void (*function)(void *, void *));

#endif  // !_LIST_H_
