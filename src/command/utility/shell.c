#include <command/utility/shell.h>
#include <stdbool.h>
#include <stdlib.h>

Command *register_shell() {
  Command *self = calloc(1, sizeof(Command));

  self->name = "shell";
  self->description = "Executa um comando no shell do bot";
  
  self->usage = "/shell <command...:string>";
  self->example = "/shell ls -lAh";
  self->category = CATEGORY_UTILITY;

  struct discord_application_command_option *option = calloc(
    1,
    sizeof(struct discord_application_command_option)
  );

  option->name = "command";
  option->description = "O comando para ser executado";
  option->required = true;
  option->type = DISCORD_APPLICATION_OPTION_STRING;

  self->options = calloc(1, sizeof(struct discord_application_command_options));
  self->options->size = 1;
  self->options->array = option;

  self->execute = &shell_command;

  return self;
}

void shell_command(CommandData *data) {
  log_info(data->options->get(data->options, "command"));
}
