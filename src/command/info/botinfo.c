#include <command/info/botinfo.h>
#include <concord/channel.h>
#include <stdlib.h>
#include <utils/emoji.h>
#include <utils/utils.h>

Command *register_botinfo(void) {
  Command *self = calloc(1, sizeof(Command));

  self->name = "botinfo";
  self->description = "Mostra as minhas informacoes!";

  self->usage = "/botinfo";
  self->example = "/botinfo";

  self->category = CATEGORY_UTILITY;
  self->options = NULL;

  self->execute = &botinfo_command;
  
  return self;
}

void botinfo_command(CommandData *data) {
  float ram_usage = get_ram_usage(BYTE_UNIT_MEGABYTE);
  struct discord_interaction_response *params = calloc(
    1,
    sizeof(struct discord_interaction_response)
  );

  struct discord_interaction_callback_data *params_data = calloc(
    1,
    sizeof(struct discord_interaction_callback_data)
  );

  struct discord_embed embed = { .color = 0xA0FFAF };
  char *mention = get_user_as_mention(data->sender);

  discord_embed_set_title(&embed, "_ _      Ghosty");
  discord_embed_set_description(
    &embed,
    "Olá %s, meu nome e Ghosty e eu sou "
    "um bot simples feito para o discord "
    "escrito em %s [C](%s) com a biblioteca"
    " concord!\n\n O objetivo desse bot é "
    "ser simples e útil para seu servidor"
    ", contendo comandos para moderação, "
    "diversão, e entre outros!\n\n_ _    "
    "Veja algumas informações sobre mim "
    "abaixo!",
    mention,
    EMOJI_C,
    "https://pt.wikipedia.com/wiki/C_%28linguagem_de_programação%29");

  free(mention);
  char *ram_usage_str = calloc(22, sizeof(char));
  snprintf(ram_usage_str, 22, "> %.2f MiB", ram_usage);

  discord_embed_add_field(
    &embed,
    EMOJI_RAMSTICK " Uso de memória RAM",
    ram_usage_str,
    1
  );

  params_data->embeds = &(struct discord_embeds) {
    .size = 1,
    .array = &embed
  };

  params->type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE;
  params->data = params_data;

  discord_create_interaction_response(
    data->client,
    data->interaction->id,
    data->interaction->token,
    params,
    NULL
  );

  free(params);
  free(params_data);
  discord_embed_cleanup(&embed);
}
