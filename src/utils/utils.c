#include <utils/utils.h>

struct discord_guilds *get_user_guilds(struct discord *discord) {
  struct discord_guilds *guilds = (struct discord_guilds *)
    calloc(1, sizeof(struct discord_guilds));

  discord_get_current_user_guilds(
      discord,
      &(struct discord_ret_guilds) {
        .sync = guilds
      });

  return guilds;
}

size_t array_len(void **array) {
  size_t i = 0;

  while (array[i] != NULL) {
    i++;
  }
  return i;
}
