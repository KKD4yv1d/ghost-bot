#ifndef _H_COMMAND_PING
#define _H_COMMAND_PING

#include "../command.h"

/**
 * This register the ping command and returns a
 * Command * struct
 */
Command *register_ping();

/**
 * When the command is executed, this method will
 * be called
 */
void ping_command(CommandData *data);

#endif /* _H_COMMAND_PING */
