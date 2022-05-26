#include <command/command.h>
#include <command/command_data.h>
#include <events/on_interaction_create.h>
#include <pthread.h>
#include <stdbool.h>

void on_interaction_create(struct discord *client,
                           const struct discord_interaction *interaction) {
  switch (interaction->type) {
    case DISCORD_INTERACTION_APPLICATION_COMMAND: {
      if (interaction->data == NULL)
        return;
      
      log_debug("Command %s used", interaction->data->name);

      Command *command = get_command(interaction->data->name);

      if (command == NULL)
        return;

      CommandData *data = create_command_data(
        client,
        (struct discord_interaction *) interaction
      );

      for (int i = 0; i < command->options->size; i++) {
        if (command->options->array[i].required == true &&
            data->options->get(data->options, command->options->array[i].name) == NULL) {
          free_command_data(data);
          return;
        }
      }

      pthread_t thread_id;

      pthread_create(&thread_id, NULL, (void (*)) command->execute, data);
      pthread_join(thread_id, NULL);

      free_command_data(data);
    } break;
    default: {
      log_info("The interaction of type %d isn't being handled!",
               interaction->type);
    };
  }
}
