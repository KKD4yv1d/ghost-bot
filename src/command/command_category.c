#include <command/command_category.h>

char *get_command_category_name(CommandCategory category) {
  switch (category) {
    case CATEGORY_ECONOMY:
      return "💰 Economy";
    case CATEGORY_FUN:
      return "🎉 Fun";
    case CATEGORY_UTILITY:
      return "🔧 Utility";
    case CATEGORY_MINIGAME:
      return "🎮 Minigame";
    case CATEGORY_MODERATION:
      return "👮 Moderation";
  }
}
