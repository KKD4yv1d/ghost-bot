#ifndef _H_COMMAND_DATA
#define _H_COMMAND_DATA

#include <concord/discord.h>
#include "../utils/map.h"

typedef struct {
  /**
   * The discord bot client
   */
  struct discord* client;

  /**
   * The discord interaction user 
   */
  struct discord_user* sender;

  /**
   * The discord interaction
   */
  struct discord_interaction* interaction;

  /**
   * All discord command options
   */
  Map *options;
} CommandData;

CommandData* create_command_data(struct discord* client, struct discord_interaction* interaction);
void free_command_data(CommandData* data);

#endif
