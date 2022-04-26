#ifndef _H_UTILS
#define _H_UTILS

#include <concord/discord.h>
#include <stdlib.h>
#include <stdio.h>

#define ASSERT(expr, msg)                           \
  if (!expr) {                     .                \
    fprintf(stderr, "Assertion failed: %s\n", msg); \
    abort();                                        \
  }                                                 \
}

struct discord_guilds *get_user_guilds(struct discord *discord);

#endif /* _H_UTILS */
