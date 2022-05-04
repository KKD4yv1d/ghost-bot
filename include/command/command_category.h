#ifndef _H_COMMAND_CATEGORY
#define _H_COMMAND_CATEGORY

typedef enum {
  CATEGORY_UTILITY,
  CATEGORY_FUN,
  CATEGORY_MINIGAME,
  CATEGORY_ECONOMY,
  CATEGORY_MODERATION
} CommandCategory;

char *get_command_category_name(CommandCategory category);

#endif
