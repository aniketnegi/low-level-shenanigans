#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_element_t {
  int posn;
  void *data;
  list_element_t *prev;
  list_element_t *next;
} list_element_t;

typedef struct list_t {
  int size;
  list_element_t *head;
  list_element_t *tail;
} list_t;

list_t *list_create();

void list_destroy(list_t *list);

void list_append(list_t *list, void *data);

void list_prepend(list_t *list, void *data);

void list_insert(list_t *list, int index, void *data);

void *list_get(list_t *list, int index);

void list_remove(list_t *list, int index);

int list_size(list_t *list);

void list_print(list_t *list);

list_t *list_copy(list_t *list);

void list_reverse(list_t *list);

void list_map(list_t *list, void (*function)(void *));

void list_filter(list_t *list, bool (*function)(void *));

void list_fold(list_t *list, void *initial_value,
               void (*function)(void *, void *));

#endif  // !_LIST_H_
