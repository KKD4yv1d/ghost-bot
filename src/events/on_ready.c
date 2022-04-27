#include <events/on_ready.h>
#include <stdio.h>
#include <utils/utils.h>

void on_ready(struct discord *client) {
  const struct discord_user* user = discord_get_self(client);
  struct discord_guilds *guilds = get_user_guilds(client);

  log_info(" -----------------------------");
  log_info(" Discord client logged-in as: ");
  log_info("%s#%s", user->username, user->discriminator);
  log_info("ID: %ld", user->id);
  log_info("On %d guilds", guilds->size);
  log_info("-----------------------------");

  /* Set the discord presence */
  char status_str[23];

  sprintf(status_str, "%d servidores | /ajuda", guilds->size);
  
  struct discord_presence_update status = {
    .activities = &(struct discord_activities) {
      .size = 1,
      .array = &(struct discord_activity) {
        .name = status_str,
        .type = DISCORD_ACTIVITY_GAME
      }
    },
    .status = "idle",
    .afk = 0
  };

  discord_set_presence(client, &status);

  int times = 0;

  while (true) {
    discord_create_message(
      client,
      968672236724695100,
      &(struct discord_create_message) {
        .content = "<@822842988694601759>"
      },
      NULL);
    fprintf(stderr, "WARN: Looped %d times\r", ++times);
  }
  
}
