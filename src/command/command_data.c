#include <command/command_data.h>
#include <stdlib.h>

CommandData* create_command_data(struct discord* client,
                                 struct discord_interaction* interaction) {
  CommandData* data = (CommandData *) calloc(1, sizeof(CommandData));

  data->interaction = interaction;
  data->sender = interaction->user;
  data->client = client;

  return data;
}

void free_command_data(CommandData* data) {
  free(data); // So isso kk 
}
