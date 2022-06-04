#ifndef _H_COMMAND_SHELL
#define _H_COMMAND_SHELL

#include "../command.h"

Command *register_shell(void);
void shell_command(CommandData *data);

#endif // _H_COMMAND_SHELL
