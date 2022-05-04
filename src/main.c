#include <events/on_interaction_create.h>
#include <events/on_ready.h>
#include <redis/database.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <concord/discord.h>

int main(int argc, char **argv) {
  char *token = getenv("TOKEN");

  if (token == NULL) {
    if (argc < 2) {
      log_error("Usage: %s TOKEN\n/!\\ Or set a enviroment variable called TOKEN with your discord token", argv[0]);
      return 1;
    }
    token = argv[1];
  }

  struct discord *client = discord_init(token);

  discord_set_on_ready(client, &on_ready);
  discord_set_on_interaction_create(client, &on_interaction_create);

  discord_run(client);
  discord_cleanup(client);

  return 0;
}
