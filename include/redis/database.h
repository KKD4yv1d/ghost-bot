#ifndef _H_DATABASE
#define _H_DATABASE

#define REDIS_LOCAL_HOST "127.0.0.1"
#define REDIS_LOCAL_PORT 6379

#include <hiredis/hiredis.h>

struct reply_t {
  redisReply *reply;

  char *(*as_string)(struct reply_t *reply);
  int (*as_int)(struct reply_t *reply);
  long (*as_long)(struct reply_t *reply);
  double (*as_double)(struct reply_t *reply);

  int (*valid)(struct reply_t *reply);
  int type;

  void (*free)(struct reply_t *reply);
};

struct redis_t {
  redisContext *context;

  struct reply_t *(*query)(struct redis_t *redis, char *command, ...);
  void (*exec)(struct redis_t *redis, char *command, ...);
  void (*free)(struct redis_t *redis);
};

typedef struct redis_t RedisConnection;
typedef struct reply_t RedisReply;

RedisConnection *create_redis_connection(char *host, int port);
RedisReply *create_redis_reply(redisReply *reply);

char *reply_as_string(RedisReply *reply);
int reply_as_int(RedisReply *reply);
long reply_as_long(RedisReply *reply);
double reply_as_double(RedisReply *reply);

RedisReply *redis_query(RedisConnection *redis, char *command, ...);
void redis_exec(RedisConnection *redis, char *command, ...);

void redis_free(RedisConnection *redis);
void reply_free(RedisReply *reply);

int reply_valid(RedisReply *reply);

#endif
