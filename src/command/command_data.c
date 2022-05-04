#include <command/command_data.h>
#include <stdlib.h>

CommandData* create_command_data(struct discord* client,
                                 struct discord_interaction* interaction) {
  CommandData* data = (CommandData *) calloc(1, sizeof(CommandData));

  struct discord_user *sender = NULL;
  if (interaction->user != NULL)
    sender = interaction->user;
  else if (interaction->member != NULL &&
           interaction->member->user != NULL)
    sender = interaction->member->user;

  data->interaction = interaction;
  data->sender = sender;
  data->client = client;
  data->options = NULL;
  
  if (interaction->data->options != NULL) {
    data->options = create_map();
    
    for (int i = 0; i < interaction->data->options->size; i++) {
      struct discord_application_command_interaction_data_option opt =
        interaction->data->options->array[i];

      char *key = calloc(strlen(opt.name), sizeof(char));
      void *value = calloc(strlen(opt.value), sizeof(char));

      strcpy(key, opt.name);
      memcpy(value, opt.value, strlen(opt.value));

      data->options->put(data->options, key, value);
    }
  }

  return data;
}

void free_command_data(CommandData* data) {
  if (data->options != NULL)
    destroy_map(data->options);

  free(data); // So isso kk 
}
