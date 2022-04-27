#include <command/command_category.h>

char *get_command_category_name(CommandCategory category) {
  switch (category) {
    case ECONOMY:
      return "💰 Economy";
    case FUN:
      return "🎉 Fun";
    case UTILITY:
      return "🔧 Utility";
    case MINIGAME:
      return "🎮 Minigame";
    case MODERATION:
      return "👮 Moderation";
  }
}
