#ifndef __BT_ECHO_H__
#define __BT_ECHO_H__

#include <libbip.h>

typedef unsigned char byte;

struct appdata_t
{
    Elf_proc_*  proc;
    void*       ret_f;
};


// function addresses in latin 1.1.5.36

#define ALIPAY_TASK_CREATE_ADDR         0x080323f4+1 
#define ALIPAY_TASK_DELETE_ADDR         0x08032420+1 
#define ALIPAY_SET_MSG_HANDLER_ADDR     0x080492F0+1
#define ALIPAY_SEND_HOST_DATA_ADDR      0x080150B0+1

typedef void (*pf_alipay_task_create)();
typedef void (*pf_alipay_task_delete)();
typedef void (*pf_alipay_set_msg_handler)(void*);
typedef int (*pf_alipay_send_host_data)(void*, int);

void echo_init();
void echo_deinit();
void show_screen_handler(void*);
void keypress_handler();
void custom_msg_handler(byte*, int);

#endif