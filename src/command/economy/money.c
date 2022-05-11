#include <command/economy/money.h>

Command *register_money(void) {
  Command *self = calloc(1, sizeof(Command));

  self->name = "money";
  self->description = "Veja a sua quantia de kwanzas";
  self->usage = "/money [user: target]";

  self->example = "/money [@D4y]";
  self->category = CATEGORY_ECONOMY;

  struct discord_application_command_option *opt = calloc(1, sizeof(struct discord_application_command_option));

  opt->name = "user";
  opt->required = 0;
  opt->type = DISCORD_APPLICATION_OPTION_USER;
  opt->description = "O usuário para ver os kwanzas";

  self->options = calloc(1, sizeof(struct discord_application_command_options));
  self->options->size = 1;
  self->options->array = opt;

  self->execute = &money_command;

  return self;
}

void money_command(CommandData *data) {
  log_info("O comando de money foi usado!");
}
