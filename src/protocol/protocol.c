//
//  protocol.c
//  Server
//
//  Created by gongtao on 2019/2/14.
//

#include "protocol.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct cue_header cue_header_init(uint32_t no, uint32_t type, uint32_t length) {
    struct cue_header header;
    memset(&header, 0, sizeof(header));
    header.version = CUE_PROTOCOL_VERSION;
    header.auth = CUE_PROTOCOL_AUTH;
    header.no = no;
    header.type = type;
    header.length = length;
    return header;
}
