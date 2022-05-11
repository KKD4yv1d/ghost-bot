#include <command/command.h>
#include <command/command_category.h>
#include <command/economy/money.h>
#include <command/info/ping.h>
#include <command/info/botinfo.h>
#include <command/utility/shell.h>
#include <concord/application_command.h>
#include <stdio.h>
#include <utils/map.h>
#include <redis/database.h>
#include <utils/utils.h>

Map *commands;
RedisConnection *connection;

void init_commands(struct discord* client) {
  connection = create_redis_connection(NULL, 0);
  if (connection == NULL ||
      connection->context == NULL) {
    log_error("Can't connect to redis! exiting...");
    exit(10);
  }

  commands = create_map();

  commands->put(commands, "ping", register_ping());
  commands->put(commands, "botinfo", register_botinfo());
  commands->put(commands, "shell", register_shell());
  commands->put(commands, "money", register_money());

  commands->for_each(commands, client, &register_default_commands);
  connection->free(connection);
}

void register_default_commands(char *key, void *value, void *data) {
  struct discord* client = (struct discord*) data;
  Command *command = (Command*) value;

  RedisReply *reply = connection->query(
    connection, "EXISTS commands:%s", command->name
  );

  if (reply->valid(reply) && reply->as_int(reply) == 1) {
    log_info("O comando /%s já foi registrado!", command->name);
    return;
  }

  reply->free(reply);
  connection->exec(connection, "SET commands:%s 1", command->name);
  upsert_command(client, command);
}

char *create_command_description(Command *command) {
  char *frame_start = "｛ ",
       *frame_end = " ｝";

  char *final = (char *) calloc(128, sizeof(char));

  snprintf(final, 100, "%s%s%s%s",
    frame_start,
    get_command_category_name(command->category),
    frame_end,
    command->description);

  return final;
}

void upsert_command(struct discord *client, Command *command) {
  struct discord_create_global_application_command params = {
    .name = command->name,
    .type = DISCORD_APPLICATION_CHAT_INPUT
  };

  if (command->options != NULL) {
    params.options = command->options;
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
  free(params.options->array);
  free(params.options);
}

Command *get_command(char *name) {
  return commands->get(commands, name);
}

int exists_command(char *name) {
  return commands->contains(commands, name);
}

void delete_command(struct discord *client, Command *command) {
  commands->remove(commands, command->name);
}

void update_command(struct discord *client, Command *command) {
  delete_command(client, command);
  upsert_command(client, command);
}
