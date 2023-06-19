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

static node_t *list_insert(node_t *node_prev, node_t *node_next,
                           ll_data_t data) {
  node_t *new_node = malloc(sizeof(node_t) + sizeof(ll_data_t));

  if (new_node == NULL) {
    /// malloc failure
    fprintf(stderr, "ERR: malloc failure\n");
    exit(EXIT_FAILURE);
  }
  new_node->data = data;

  new_node->prev = node_prev;
  new_node->next = node_next;

  return new_node;
}

static ll_data_t list_remove(list_t *list, node_t *node, size_t situation) {
  /// situation is used to determine if node has next or prev pointer = NULL /
  /// OBVIOUSLY:
  ///   next = NULL ==> node is at list->tail /
  ///   prev = NULL ==> node is at list->head /
  ///   neither is NULL ==> node is somewhere in the middle /
  /// prev = NULL ==> situation = -1 /
  /// both = NULL ==> situation = 0 /
  /// next = NULL ==> situation = 1 /
  /// case default ==> neither = NULL
  ll_data_t data = node->data;

  node_t *prev = node->prev;
  node_t *next = node->next;

  switch (situation) {
  case -1:
    // node is at list->head
    list->head = next;
    next->prev = NULL;
    break;

  case 0:
    // list only has one element
    // prev = next = NULL
    // can use them also, but code doesn't read very good IMO
    list->head = NULL;
    list->tail = NULL;
    break;

  case 1:
    // node is at list->tail
    list->tail = prev;
    prev->next = NULL;
    break;

  default:
    // somwhere in the middle
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
    /// malloc failure
    fprintf(stderr, "ERR: malloc failure\n");
    exit(EXIT_FAILURE);
  }

  new_list->head = NULL;
  new_list->tail = NULL;

  return new_list;
}

// counts the items on a list
size_t list_count(const list_t *list) {
  size_t list_size = 0;
  if (list == NULL) {
    return list_size;
  }

  node_t *curr = list->head;

  while (curr != NULL) {
    list_size++;
    curr = curr->next;
  }

  return list_size;
}

// inserts item at back of a list
void list_push(list_t *list, ll_data_t item_data) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }

  if (list_count(list) == 0) {
    // empty list
    node_t *node = list_insert(NULL, NULL, item_data);

    list->head = node;
    list->tail = node;

    return;
  }
  // list has one or more elements
  node_t *node = list_insert(list->tail, NULL, item_data);

  list->tail->next = node;
  list->tail = node;
}

// removes item from back of a list
ll_data_t list_pop(list_t *list) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }

  ll_data_t req_data;

  if (list_count(list) == 0) {
    // empty list
    // tests don't specify how to handle err
    fprintf(stderr, "Error: Can't pop from empty list\n");
    return -1; // or exit(EXIT_FAILURE)
  } else if (list_count(list) == 1) {
    req_data = list_remove(list, list->tail, 0);
  } else {
    // list has 2 or more elements
    req_data = list_remove(list, list->tail, 1);
  }

  return req_data;
}

// inserts item at front of a list
void list_unshift(list_t *list, ll_data_t item_data) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }

  if (list_count(list) == 0) {
    // empty list
    node_t *node = list_insert(NULL, NULL, item_data);

    list->head = node;
    list->tail = node;

    return;
  }
  // list has 1 element or more elements
  node_t *node = list_insert(NULL, list->head, item_data);

  list->head->prev = node;
  list->head = node;
}

// removes item from front of a list
ll_data_t list_shift(list_t *list) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }

  ll_data_t req_data;

  if (list_count(list) == 0) {
    // empty list
    // tests don't specify how to handle err
    fprintf(stderr, "Error: Can't pop from empty list\n");
    return -1; // or exit(EXIT_FAILURE)
  } else if (list_count(list) == 1) {
    req_data = list_remove(list, list->head, 0);
  } else {
    // list has 2 or more elements
    req_data = list_remove(list, list->head, -1);
  }

  return req_data;
}

// deletes a node that holds the matching data
void list_delete(list_t *list, ll_data_t data) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }

  if (list_count(list) == 0) {
    // empty list
    // DO NOTHING
    return;
  } else if (list_count(list) == 1) {
    if (list->head->data == data) {
      list_remove(list, list->head, 0);
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
        node_t *previous = curr->prev;
        node_t *following = curr->next;
        size_t situation;
        if (previous == NULL) {
          // element to be removed is first element
          situation = -1;
        } else if (following == NULL) {
          // element to be removed is last element
          situation = 1;
        } else {
          // element to be removes is neither first nor last element
          situation = 69; // switch-case will go to default
        }

        list_remove(list, curr, situation);
        return;
      }
    }
  }
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(list_t *list) {
  if (list == NULL) {
    // ERR -> list use uninitialized
    fprintf(stderr, "Error: list is uninitialized\n");
    exit(EXIT_FAILURE);
  }

  node_t *curr = list->head;

  while (curr != NULL) {
    node_t *nextNode = curr->next;
    free(curr);
    curr = nextNode;
  }
  free(list);
}
