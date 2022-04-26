#include <command/command.h>
#include <command/command_category.h>
#include <concord/application_command.h>
#include <stdio.h>
#include <utils/map.h>

Map *commands;

void init_commands() {
  commands = create_map();
}

char *create_command_description(Command *command) {
  char *frame_start = "｛",
       *frame_end = "｝";

  char *final = (char *) calloc(100, sizeof(char));

  snprintf(final, 100, "%s%s%s",
    frame_start,
    get_category_name(command->category),
    frame_end);

  return final;
}

void upsert_command(struct discord *client, Command *command) {
  struct discord_create_global_application_command params = {
    .name = command->name
  };

  if (command->options != NULL) {
    params.options = *command->options;
  }

  if (command->description != NULL) {
    params.description = create_command_description(command);
  }

  discord_create_global_application_command(
    client,
    APPLICATION_ID,
    &params,
    NULL
  );

  free(params.description);
}

Command *get_command(char *name) {
  return commands->get(commands, name);
}

int exists_command(char *name) {
  return commands->contains(commands, name);
}

void delete_command(struct discord *client, Command *command) {
  // TODO:
  commands->remove(commands, command->name);
}

void update_command(struct discord *client, Command *command) {
  delete_command(client, command);
  upsert_command(client, command);
}
