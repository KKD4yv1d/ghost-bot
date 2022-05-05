#include <stdarg.h>
#include <sys/resource.h>
#include <stdio.h>
#include <utils/utils.h>

#ifdef __MINGW32__
# include <windows.h>
#endif

/* Discord utilites */

/**
 * This returns all guilds from the discord client
 */
struct discord_guilds *get_user_guilds(struct discord *discord) {
  struct discord_guilds *guilds = (struct discord_guilds *)
    calloc(1, sizeof(struct discord_guilds));

  discord_get_current_user_guilds(
      discord,
      &(struct discord_ret_guilds) {
        .sync = guilds
      });

  return guilds;
}

/**
 * This returns a string in the format <@$(id)> that
 * is the discord mention format
 *
 * This string is allocated in memory! use free in it
 * after using it
 */
char *get_user_as_mention(struct discord_user *user) {
  char *string = (char *) malloc(sizeof(char) * 22);
  snprintf(string, 22, "<@%lu>", user->id);

  return string;
}

/* Array utilites */

/**
 * Returns the array length
 */
size_t array_len(void **array) {
  size_t i = 0;

  while (array[i] != NULL) {
    i++;
  }
  return i;
}

/* Process utilites */

void set_terminal_title(char *title) {
  // This set the window title to $title variable
# ifndef __MINGW32__
  printf("%c]0;%s%c", '\033', title, '\007');
# else
  SetConsoleTitle(title);
# endif
}

/**
 * Returns the CPU Usage (not implemented yet)
 */
float get_cpu_usage() {
  // TODO: Return the CPU Usage
  return 0;
}

/**
 * Returns the RAM usage with the given unit
 * @see ByteUnit
 */
float get_ram_usage(ByteUnit unit) {
  float usage;
  struct rusage info;

  getrusage(RUSAGE_SELF, &info);

  // Sorry if has a better way to do this
  switch (unit) {
    case BYTE_UNIT_BYTE:
      usage = info.ru_maxrss;
      break;
    case BYTE_UNIT_KBYTE:
      usage = info.ru_maxrss / 1024.0f;
      break;
    case BYTE_UNIT_MEGABYTE:
      usage = info.ru_maxrss / (1024.0f * 1024.0f);
      break;
    case BYTE_UNIT_GIGABYTE:
      usage = info.ru_maxrss / (1024.0f * 1024.0f * 1024.0f);
      break;
    case BYTE_UNIT_TERABYTE:
      usage = info.ru_maxrss / (1024.0f * 1024.0f * 1024.0f * 1024.0f);
  }

  return usage;
}
