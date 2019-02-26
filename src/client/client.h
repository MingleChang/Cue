//
//  client.h
//  Server
//
//  Created by gongtao on 2019/2/18.
//

#ifndef client_h
#define client_h

#include <stdio.h>
#include "connect.h"

extern struct cue_connect *client;

void clientReadData(void *user_data);

#endif /* client_h */
