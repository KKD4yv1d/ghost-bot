#ifndef _H_ON_INTERACTION_CREATE
#define _H_ON_INTERACTION_CREATE

#include <concord/discord.h>

void on_interaction_create(struct discord *client,
                           const struct discord_interaction *interaction);


#endif /* _H_ON_INTERACTION_CREATE */
