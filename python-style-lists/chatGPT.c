#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void** elements;
  size_t size;
  size_t capacity;
} PyList;

PyList* create_list() {
  PyList* list = (PyList*)malloc(sizeof(PyList));
  if (list == NULL) {
    // Error handling for memory allocation failure
    return NULL;
  }

  list->elements = NULL;
  list->size = 0;
  list->capacity = 0;
  return list;
}

void append(PyList* list, void* element) {
  if (list->size >= list->capacity) {
    size_t newCapacity = (list->capacity == 0) ? 1 : list->capacity * 2;
    void** newElements =
        (void**)realloc(list->elements, newCapacity * sizeof(void*));
    if (newElements == NULL) {
      // Error handling for memory allocation failure
      return;
    }
    list->elements = newElements;
    list->capacity = newCapacity;
  }

  list->elements[list->size++] = element;
}

void destroy_list(PyList* list) {
  if (list == NULL) {
    return;
  }

  free(list->elements);
  free(list);
}

int main() {
  PyList* myList = create_list();

  int intValue = 42;
  append(myList, &intValue);

  char charValue = 'A';
  append(myList, &charValue);

  // Accessing the elements
  for (size_t i = 0; i < myList->size; ++i) {
    printf("Element at index %zu: %c\n", i, *((char*)(myList->elements[i])));
  }

  destroy_list(myList);

  return 0;
}
