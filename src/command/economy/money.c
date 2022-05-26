#include <command/economy/money.h>
#include <redis/database.h>
#include <utils/utils.h>
#include <stdlib.h>

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
  RedisConnection *conn = create_redis_connection(NULL, 0);

  if (conn == NULL) {
    send_error_embed("Não foi possivel se conectar a database!", data);
    return;
  }
  
  /**
   * Verify if that user exists on the redis database
   */
  RedisReply *existsReply = conn->query(conn, "EXISTS profile:%llu:money", data->sender->id);

  if (!existsReply->valid(existsReply) ||
      existsReply->as_int(existsReply) != 1) {
    send_error_embed("Você não tem uma conta na database!", data);
    redis_free(conn);
    reply_free(existsReply);
    return;
  }

  /**
   * Get the user money from database and send as an embed
   */
  RedisReply *moneyReply = conn->query(conn, "GET profile:%llu:money", data->sender->id);

  int money_count = moneyReply->as_int(moneyReply);

  struct discord_interaction_response *params = calloc(1, sizeof(struct discord_interaction_response));
  struct discord_interaction_callback_data *params_data = calloc(1, sizeof(struct discord_interaction_callback_data));
  struct discord_embed embed = {
    .color = 0xA0FFAA
  };

  discord_embed_set_title(&embed, "Seus kwanzas (Primeiro layout, vai mudarkk)");
  discord_embed_set_description(&embed, "Você atualmente tem %d kwanzas", money_count);

  char *mention = get_user_as_mention(data->sender);

  params_data->content = mention;
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

  discord_embed_cleanup(&embed);
  free(params);
  free(params_data);
  free(mention);
  reply_free(moneyReply);
  redis_free(conn);
}
