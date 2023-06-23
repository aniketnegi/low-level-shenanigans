#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

typedef struct list_node {
  struct list_node *prev, *next;
  ll_data_t data;
} node_t;

typedef struct list {
  struct list_node *head, *tail;
} list_t;

static void assert_valid_list_ptr(const list_t *list) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }
}

static void assert_list_not_empty(const list_t *list) {
  // tests don't specify how to deal with empty list so i just exit
  if (list->head == NULL) {
    // ERR -> list is empty
    fprintf(stderr, "Error: list is empty\n");
    exit(EXIT_FAILURE);
  }
}

static node_t *list_insert(list_t *list, node_t *node_prev, node_t *node_next,
                           ll_data_t data) {
  node_t *new_node = malloc(sizeof(node_t));

  if (new_node == NULL) {
    // ERR -> malloc failure
    fprintf(stderr, "ERR: malloc failure\n");
    exit(EXIT_FAILURE);
  }

  new_node->data = data;

  if (node_prev == NULL && node_next == NULL) {
    // list is currently empty
    list->head = new_node;
    list->tail = new_node;
  } else if (node_prev == NULL) {
    // node is to be inserted at beginning
    list->head = new_node;
    node_next->prev = new_node;
  } else if (node_next == NULL) {
    // node is to be inserted at end
    list->tail = new_node;
    node_prev->next = new_node;
  } else {
    // node to be inserted in the middle somewhere
    node_prev->next = new_node;
    node_next->prev = new_node;
  }

  new_node->prev = node_prev;
  new_node->next = node_next;

  return new_node;
}

static ll_data_t list_remove(list_t *list, node_t *node) {
  ll_data_t data = node->data;

  node_t *prev = node->prev;
  node_t *next = node->next;

  if (prev == NULL && next == NULL) {
    // only 1 element in list
    list->head = NULL;
    list->tail = NULL;
  } else if (prev == NULL) {
    // node is head
    list->head = next;
    next->prev = NULL;
  } else if (next == NULL) {
    // node is tail
    list->tail = prev;
    prev->next = NULL;
  } else {
    // node is in middle
    prev->next = next;
    next->prev = prev;
  }

  free(node);
  return data;
}

// constructs a new (empty) list
list_t *list_create(void) {
  list_t *new_list = malloc(sizeof(list_t));

  if (new_list == NULL) {
    // ERR -> malloc failure
    fprintf(stderr, "ERR: malloc failure\n");
    exit(EXIT_FAILURE);
  }

  new_list->head = NULL;
  new_list->tail = NULL;

  return new_list;
}

// counts the items on a list
size_t list_count(const list_t *list) {
  assert_valid_list_ptr(list);

  size_t list_size = 0;

  node_t *curr = list->head;

  while (curr != NULL) {
    list_size++;
    curr = curr->next;
  }

  return list_size;
}

// inserts item at back of a list
void list_push(list_t *list, ll_data_t item_data) {
  assert_valid_list_ptr(list);

  // (list_t *) to the newly created node returned by list_insert can be used
  list_insert(list, list->tail, NULL, item_data);
}

// removes item from back of a list
ll_data_t list_pop(list_t *list) {
  assert_valid_list_ptr(list);

  ll_data_t req_data;

  assert_list_not_empty(list);

  // list has 1  or more element
  req_data = list_remove(list, list->tail);

  return req_data;
}

// inserts item at front of a list
void list_unshift(list_t *list, ll_data_t item_data) {
  assert_valid_list_ptr(list);

  // (list_t *) to the newly created node returned by list_insert can be used
  list_insert(list, NULL, list->head, item_data);
}

// removes item from front of a list
ll_data_t list_shift(list_t *list) {
  assert_valid_list_ptr(list);

  ll_data_t req_data;

  assert_list_not_empty(list);

  // list has 1 or more elements
  req_data = list_remove(list, list->head);

  return req_data;
}

// deletes a node that holds the matching data
void list_delete(list_t *list, ll_data_t data) {
  assert_valid_list_ptr(list);

  if (list->head == NULL) {
    // empty list
    // DO NOTHING
    return;
  } else if (list->head == list->tail) {
    if (list->head->data == data) {
      list_remove(list, list->head);
      return;
    } else {
      // data not found
      return;
    }
  } else {
    // list has 2 or more elements
    for (node_t *curr = list->head; curr != NULL; curr = curr->next) {
      if (curr->data == data) {
        // delete this node
        list_remove(list, curr);
        return;
      }
    }
  }
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(list_t *list) {
  assert_valid_list_ptr(list);

  while (list->head != NULL) {
    list_pop(list);
  }

  list = NULL;
}
