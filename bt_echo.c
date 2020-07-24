// bluetooth echo by x27

#include <libbip.h>
#include "bt_echo.h"

struct regmenu_ menu_screen = { 55, 1, 0, 0, keypress_handler, 0, 0, show_screen_handler, 0, 0 };

struct appdata_t** p_app_data;
struct appdata_t* app_data;

// ����������� ������� �� ��������

pf_alipay_task_create alipay_task_create = (pf_alipay_task_create) ALIPAY_TASK_CREATE_ADDR;
pf_alipay_task_delete alipay_task_delete = (pf_alipay_task_delete) ALIPAY_TASK_DELETE_ADDR;
pf_alipay_set_msg_handler alipay_set_msg_handler = (pf_alipay_set_msg_handler) ALIPAY_SET_MSG_HANDLER_ADDR;
pf_alipay_send_host_data alipay_send_host_data = (pf_alipay_send_host_data) ALIPAY_SEND_HOST_DATA_ADDR;

// ����� �����
int main(int p, char** a) 
{ 
    show_screen_handler((void*) p);
}

// ������������� ����������
void startup_stub(void *p)
{
    p_app_data = get_ptr_temp_buf_2();

    if ( (p == *p_app_data) && get_var_menu_overlay()) {
        app_data = *p_app_data;
        *p_app_data = NULL;
        reg_menu(&menu_screen, 0);
        *p_app_data = app_data;
    } else {
        reg_menu(&menu_screen, 0);
        *p_app_data = (struct appdata_t *)pvPortMalloc(sizeof(struct appdata_t));
        app_data = *p_app_data;
        _memclr(app_data, sizeof(struct appdata_t));
        app_data->proc = p;
    }
    
    if ( p && app_data->proc->elf_finish )
        app_data->ret_f = app_data->proc->elf_finish;
    else
        app_data->ret_f = show_watchface;

    set_graph_callback_to_ram_1();
    load_font();
}

void show_screen_handler(void *p) 
{
    // ������ ��� ��������� ����������
    // �������� � ��������� �������
    startup_stub(p);

    set_bg_color(COLOR_BLACK);
    fill_screen_bg();
    set_fg_color(COLOR_BLUE);
    text_out_center("BT Echo", 88, 60);

    set_display_state_value(8, 1);
    set_display_state_value(4, 1);
    set_display_state_value(2, 1);

    // ��������� ���
    echo_init();
}

// ���������� ������� ������: 
// ������� �� ����������
void keypress_handler()
{
    // ����������� ���
    echo_deinit();
    show_menu_animate(app_data->ret_f, (unsigned int)show_screen_handler, ANIMATE_RIGHT);   
};

// ���������
void echo_init()
{
    // ��������� ������ ��������� ������� ��������� alipay
    alipay_task_create();
    // ������������� ���� ���������� ���������
    alipay_set_msg_handler(custom_msg_handler);
}

// �����������
void echo_deinit()
{
    // ���������� ���������� ���������
    alipay_set_msg_handler(NULL);
    // ����� ������
    alipay_task_delete();
}

// ���������� ��������� ���������� �� �����
void custom_msg_handler(byte *data, int len)
{
    // �������� �����, �� ��� �������� �� ����
    alipay_send_host_data(data, len);
}


