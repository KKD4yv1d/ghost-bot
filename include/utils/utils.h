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

/* Array utilities */
size_t array_len(void **array);

/* Discord utilities */
struct discord_guilds *get_user_guilds(struct discord *discord);
char *get_user_as_mention(struct discord_user *user);

/* Process utilities (RAM, CPU, ...) */
typedef enum byte_unit_t {
  BYTE_UNIT_BYTE,
  BYTE_UNIT_KBYTE,
  BYTE_UNIT_MEGABYTE,
  BYTE_UNIT_GIGABYTE,
  BYTE_UNIT_TERABYTE
} ByteUnit;

void set_terminal_title(char *title);

float get_cpu_usage();
float get_ram_usage(ByteUnit unit);

/* File utilities */

#endif /* _H_UTILS */
