#ifndef _H_MAP
#define _H_MAP

typedef struct {
  char *key;
  void *value;
} Pair;

struct map_m {
  Pair **pairs;
  int size;

  void (*destroy)(struct map_m *);
  void (*put)(struct map_m *map, char *key, void *value);
  void *(*get)(struct map_m *map, char *key);
  void (*remove)(struct map_m *map, char *key);
  int (*length)(struct map_m *map);
  int (*contains)(struct map_m *map, char *key);
  char **(*keys)(struct map_m *map);
  void **(*values)(struct map_m *map);
  void (*for_each)(struct map_m *map, void *data,
                   void (*callable)(char *key, void *value, void *data));
};

typedef struct map_m Map;

Map *create_map(void);
Pair *create_pair(char *key, void *value);
void destroy_pair(Pair *pair);
void destroy_map(Map *map);
void map_put(Map *map, char *key, void *value);
void *map_get(Map *map, char *key);
void map_remove(Map *map, char *key);
int map_length(Map *map);
int map_contains(Map *map, char *key);
char **map_keys(Map *map);
void **map_values(Map *map);
void map_for_each(Map *map,
                  void *data,
                  void (*func)(char *key, void *value, void *data));

#endif
