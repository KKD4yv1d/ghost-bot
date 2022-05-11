#include <stdlib.h>
#include <utils/map.h>

Map *create_map(void) {
  Map *map = (Map *) calloc(1, sizeof(Map));

  map->pairs = (Pair **) calloc(0, sizeof(Pair*));
  map->size = 0;
  
  map->get = &map_get;
  map->put = &map_put;
  map->contains = &map_contains;
  map->remove = &map_remove;
  map->for_each = &map_for_each;
  map->keys = &map_keys;
  map->values = &map_values;
  map->destroy = &destroy_map;
  map->length = &map_length;

  return map;
}

Pair *create_pair(char *key, void *value) {
  Pair *pair = (Pair *) calloc(1, sizeof(Pair));

  pair->key = key;
  pair->value = value;

  return pair;
}

void destroy_pair(Pair *pair) {
  free(pair->key);
  free(pair->value);
  free(pair);
}

void destroy_map(Map *map) {
  for (int i = 0; i < map->size; i++) {
    destroy_pair(map->pairs[i]);
  }

  free(map->pairs);
  free(map);
}

void map_put(Map *map, char *key, void *value) {
  Pair *pair = create_pair(key, value);

  map->pairs = (Pair **) realloc(map->pairs, (map->size + 1) * sizeof(Pair*));
  map->pairs[map->size] = pair;
  map->size++;
}

void *map_get(Map *map, char *key) {
  for (int i = 0; i < map->size; i++) {
    if (strcmp(map->pairs[i]->key, key) == 0) {
      return map->pairs[i]->value;
    }
  }

  return NULL;
}

void map_remove(Map *map, char *key) {
  for (int i = 0; i < map->size; i++) {
    if (strcmp(map->pairs[i]->key, key) == 0) {
      destroy_pair(map->pairs[i]);
      map->size--;

      for (int j = i; j < map->size; j++) {
        map->pairs[j] = map->pairs[j + 1];
      }

      map->pairs = (Pair **) realloc(map->pairs, map->size * sizeof(Pair*));
      break;
    }
  }
}

int map_length(Map *map) {
  return map->size;
}

int map_contains(Map *map, char *key) {
  for (int i = 0; i < map->size; i++) {
    if (strcmp(map->pairs[i]->key, key) == 0) {
      return 1;
    }
  }

  return 0;
}

char **map_keys(Map *map) {
  char **keys = (char **) calloc(map->size, sizeof(char*));

  for (int i = 0; i < map->size; i++) {
    keys[i] = map->pairs[i]->key;
  }

  return keys;
}

void **map_values(Map *map) {
  void **values = (void **) calloc(map->size, sizeof(void*));

  for (int i = 0; i < map->size; i++) {
    values[i] = map->pairs[i]->value;
  }

  return values;
}

void map_for_each(Map *map, void *data, void (*func)(char *, void *, void *)) {
  for (int i = 0; i < map->size; i++) {
    func(map->pairs[i]->key, map->pairs[i]->value, data);
  }
}
