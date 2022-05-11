#include <command/command.h>
#include <command/command_category.h>
#include <command/info/ping.h>
#include <concord/channel.h>
#include <concord/discord_codecs.h>
#include <malloc.h>

Command *register_ping(void) {
  Command *self = (Command *) calloc(1, sizeof(Command));

  self->name = "ping";
  self->description = "Pong! Verifica a latência do bot";

  self->usage = "/ping";
  self->example = "/ping";
  self->category = CATEGORY_UTILITY;

  self->execute = &ping_command;
  self->options = NULL;

  return self;
}

void ping_command(CommandData *data) {
  struct discord_embed embed = { .color = 0xA0FFAA };

  discord_embed_set_title(&embed, ":ping_pong: Pong!");
  discord_embed_set_description(&embed, "> Latência: %dms _   _",
                                discord_get_ping(data->client));

  struct discord_interaction_response *params = calloc(
    1,
    sizeof(struct discord_interaction_response)
  );

  struct discord_interaction_callback_data *resp_data = calloc(
    1,
    sizeof(struct discord_interaction_callback_data)
  );

  struct discord_embeds *embeds = calloc(1, sizeof(struct discord_embeds));

  embeds->size = 1;
  embeds->array = &embed;

  resp_data->embeds = embeds;

  params->type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE;
  params->data = resp_data;

  discord_create_interaction_response(
    data->client,
    data->interaction->id,
    data->interaction->token,
    params,
    NULL
  );

  free(params);
  free(resp_data);
  free(embeds);
  discord_embed_cleanup(&embed);
}
