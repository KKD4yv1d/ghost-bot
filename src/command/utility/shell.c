#include <command/utility/shell.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils/utils.h>
#include <concord/discord.h>

Command *register_shell(void) {
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
  // If the sender is not the bot owner, reject the request
  if (data->sender->id != 888625491760799755) {
    send_error_embed("Você não é o dono do bot!", data);
    return;
  }

  FILE *process = popen(data->options->get(data->options, "command"), "r");

  char *output = calloc(1, 2000),
       *tmp = calloc(1, 2000);

  int max_output_size = 2000;

  if (process == NULL) {
    send_error_embed("Não foi possivel iniciar o processo!", data);
    return;
  }

  while ((fgets(tmp, max_output_size, process)) != NULL) {
    strncat(output, tmp, max_output_size - 1);
  }

  pclose(process);
  free(tmp);

  struct discord_embed embed = {
    .color = 0xA0FFF0
  };

  discord_embed_set_title(&embed, ":white_check_mark: O comando %s foi executado!",
    data->options->get(data->options, "command"));
  discord_embed_set_description(&embed, "%s", output);

  discord_create_interaction_response(
    data->client,
    data->interaction->id,
    data->interaction->token,
    &(struct discord_interaction_response) {
      .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
      .data = &(struct discord_interaction_callback_data) {
        .embeds = &(struct discord_embeds) {
          .size = 1,
          .array = &embed
        }
      }
    },
    NULL
  );

  free(output);
  discord_embed_cleanup(&embed);
}
