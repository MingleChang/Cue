//
//  protocol.h
//  Server
//
//  Created by gongtao on 2019/2/14.
//

#ifndef protocol_h
#define protocol_h

#include <stdio.h>

#define CUE_PROTOCOL_VERSION 0x0001
#define CUE_PROTOCOL_AUTH 0x2435

struct cue_protocol {
    uint16_t version;   //协议版本号：CUE_PROTOCOL_VERSION，用于兼容
    uint16_t auth;      //认证：CUE_PROTOCOL_AUTH，如果不为CUE_PROTOCOL_AUTH则说明不符合协议规范
    uint32_t no;        //序号：当前发送数据编号
    uint32_t type;      //类型：数据类型定义
    uint32_t length;    //数据长度
};

#endif /* protocol_h */
