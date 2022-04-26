#ifndef _H_COMMAND
#define _H_COMMAND

#include "./command_data.h"
#include "command_category.h"
#include <stdlib.h>

#define APPLICATION_ID strtoull(getenv("APPLICATION_ID"), NULL, 10)

struct command_t {
  /** The command name */
  char *name;

  /** The command description */
  char *description;

  /**
   * The command usage (Used in /help)
   */
  char *usage;

  /**
   * The command example (Used in /help)
   */
  char *example;

  /**
   * The command category
   */
  CommandCategory category;

  /**
   * All command options (use NULL if the command doesn't have options)
   */
  struct discord_application_command_options **options;

  /**
   * The function to execute when this command is used by a user
   *
   * This can be NULL if the command isn't implemented yet,
   * if this function receive NULL and the user use this
   * command, this user will receive an warning saying
   * "this command doesn't have been implemented yet."
   */
  void (*execute)(CommandData *data);
};

typedef struct command_t Command;

void init_commands();
void upsert_command(struct discord *client, Command *command);
void update_command(struct discord *client, Command *command);
int exists_command(char *name);
Command *get_command(char *name);
void delete_command(struct discord *client, Command *command);
char *create_command_description(Command *command);

#endif
