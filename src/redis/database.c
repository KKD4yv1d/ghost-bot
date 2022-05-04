#include <hiredis/hiredis.h>
#include <redis/database.h>
#include <concord/discord.h>
#include <stdlib.h>

RedisConnection *create_redis_connection(char *host, int port) {
  if (host == NULL) {
    host = REDIS_LOCAL_HOST;
  }
  if (port == 0) {
    port = REDIS_LOCAL_PORT;
  }

  RedisConnection *self = (RedisConnection *) calloc(1, sizeof(RedisConnection));

  self->context = redisConnect(host, port);

  if (self->context == NULL || self->context->err) {
    if (self->context) {
      log_error("Connection error: %s", self->context->errstr);
      redisFree(self->context);
    } else {
      log_error("Connection error: can't allocate redis context");
    }

    free(self);
    return NULL;
  }

  self->query = &redis_query;
  self->exec = &redis_exec;
  self->free = &redis_free;

  return self;
}

RedisReply *create_redis_reply(redisReply *reply) {
  RedisReply *self = (RedisReply *) calloc(1, sizeof(RedisReply));

  self->reply = reply;
  self->valid = &reply_valid;
  self->free = &reply_free;
  self->as_double = &reply_as_double;
  self->as_string = &reply_as_string;
  self->as_int = &reply_as_int;
  self->type = reply->type;

  return self;
}

char *reply_as_string(RedisReply *self) {
  return self->reply->str;
}

int reply_as_int(RedisReply *self) {
  return self->reply->integer;
}

double reply_as_double(RedisReply *self) {
  return (double) self->reply->integer;
}

int reply_valid(RedisReply *self) {
  return self != NULL && self->reply != NULL;
}

void reply_free(RedisReply *self) {
  freeReplyObject(self->reply);
  free(self);
}

void redis_free(RedisConnection *self) {
  redisFree(self->context);
  free(self);
}

RedisReply *redis_query(RedisConnection *self, char *query, ...) {
  va_list args;
  va_start(args, query);
  redisReply *reply = redisvCommand(self->context, query, args);
  va_end(args);

  return create_redis_reply(reply);
}

void redis_exec(RedisConnection *self, char *query, ...) {
  va_list args;
  va_start(args, query);
  redisReply *r = redisvCommand(self->context, query, args);
  va_end(args);

  if (r != NULL) {
    freeReplyObject(r);
  }
}
