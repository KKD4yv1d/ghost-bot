#ifndef _H_COMMAND_CATEGORY
#define _H_COMMAND_CATEGORY

typedef enum {
  UTILITY,
  FUN,
  MINIGAME,
  ECONOMY,
  MODERATION
} CommandCategory;

char *get_command_category_name(CommandCategory category);

#endif
