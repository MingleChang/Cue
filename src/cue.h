//
//  cue.h
//  Cue
//
//  Created by gongtao on 2019/2/13.
//

#ifndef cue_h
#define cue_h

#define MAXLINE 2048

struct cue_protocol {
    uint16_t version;   //协议版本号：PROTOCOL_VERSION，用于兼容
    uint16_t auth;      //认证：PROTOCOL_AUTH，如果不为PROTOCOL_AUTH则说明不符合协议规范
    uint32_t no;        //序号：当前发送数据编号
    uint32_t type;      //类型：数据类型定义
    uint32_t length;    //数据长度
};

#endif /* cue_h */
