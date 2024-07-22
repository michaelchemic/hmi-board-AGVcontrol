#include "../ui.h"

rt_int8_t motor_mode;
rt_int8_t function_code;
lv_timer_t * point_mode_timer;  // 定时器

// Function to lock other buttons
static void lock_other_buttons(lv_obj_t * active_btn) {
    if (active_btn != ui_point) {
        lv_obj_clear_state(ui_point, LV_STATE_CHECKED);
        lv_obj_add_state(ui_point, LV_STATE_DISABLED);
    }
    if (active_btn != ui_continuous) {
        lv_obj_clear_state(ui_continuous, LV_STATE_CHECKED);
        lv_obj_add_state(ui_continuous, LV_STATE_DISABLED);
    }
    if (active_btn != ui_MotorStop) {
        lv_obj_clear_state(ui_MotorStop, LV_STATE_CHECKED);
        lv_obj_add_state(ui_MotorStop, LV_STATE_DISABLED);
    }
}

// Function to unlock all buttons
static void unlock_all_buttons() {
    lv_obj_clear_state(ui_point, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_continuous, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_MotorStop, LV_STATE_DISABLED);
}

// Function to lock direction buttons
static void lock_direction_buttons(lv_obj_t * active_btn) {
    if (active_btn != ui_Forward) {
        lv_obj_clear_state(ui_Forward, LV_STATE_CHECKED);
        lv_obj_add_state(ui_Forward, LV_STATE_DISABLED);
    }
    if (active_btn != ui_back) {
        lv_obj_clear_state(ui_back, LV_STATE_CHECKED);
        lv_obj_add_state(ui_back, LV_STATE_DISABLED);
    }
    if (active_btn != ui_Left) {
        lv_obj_clear_state(ui_Left, LV_STATE_CHECKED);
        lv_obj_add_state(ui_Left, LV_STATE_DISABLED);
    }
    if (active_btn != ui_Right) {
        lv_obj_clear_state(ui_Right, LV_STATE_CHECKED);
        lv_obj_add_state(ui_Right, LV_STATE_DISABLED);
    }
}

// Function to unlock direction buttons
static void unlock_direction_buttons() {
    lv_obj_clear_state(ui_Forward, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_back, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_Left, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_Right, LV_STATE_DISABLED);
}

// 定时器回调函数
static void point_mode_timer_cb(lv_timer_t * timer) {
    // 在这里添加发送指令的代码
    motor_mode = 1;  // 示例：设置 motor_mode
}

// point_mode 按钮事件处理函数
static void ui_point_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_PRESSED) {
        // 按下按钮时启动定时器
        point_mode_timer = lv_timer_create(point_mode_timer_cb, 100, NULL); // 每100ms触发一次
        lock_other_buttons(ui_point);
    } else if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST) {
        // 松开按钮时停止定时器
        lv_timer_del(point_mode_timer);
        unlock_all_buttons();
    }
}

static void ui_continuous_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        if (lv_obj_has_state(ui_continuous, LV_STATE_CHECKED)) {
            motor_mode = 2;
            lock_other_buttons(ui_continuous);
        } else {
            motor_mode = 0;
            unlock_all_buttons();
        }
    }
}

static void ui_MotorStop_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        if (lv_obj_has_state(ui_MotorStop, LV_STATE_CHECKED)) {
            motor_mode = 3;
            lock_other_buttons(ui_MotorStop);
        } else {
            motor_mode = 0;
            unlock_all_buttons();
        }
    }
}

static void ui_Forward_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        if (lv_obj_has_state(ui_Forward, LV_STATE_CHECKED)) {
            function_code = 1;
            lock_direction_buttons(ui_Forward);
        } else {
            function_code = 0;
            unlock_direction_buttons();
        }
    }
}

static void ui_Left_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        if (lv_obj_has_state(ui_Left, LV_STATE_CHECKED)) {
            function_code = 3;
            lock_direction_buttons(ui_Left);
        } else {
            function_code = 0;
            unlock_direction_buttons();
        }
    }
}

static void ui_Right_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        if (lv_obj_has_state(ui_Right, LV_STATE_CHECKED)) {
            function_code = 4;
            lock_direction_buttons(ui_Right);
        } else {
            function_code = 0;
            unlock_direction_buttons();
        }
    }
}

static void ui_back_event_handler(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        if (lv_obj_has_state(ui_back, LV_STATE_CHECKED)) {
            function_code = 2;
            lock_direction_buttons(ui_back);
        } else {
            function_code = 0;
            unlock_direction_buttons();
        }
    }
}

void ui_Screen1_screen_init(void) {
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Forward = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Forward, 60);
    lv_obj_set_height(ui_Forward, 60);
    lv_obj_set_x(ui_Forward, -120);
    lv_obj_set_y(ui_Forward, -80);
    lv_obj_set_align(ui_Forward, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Forward, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Forward, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_Forward, ui_Forward_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_Forward, LV_OBJ_FLAG_CHECKABLE);

    ui_Left = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Left, 60);
    lv_obj_set_height(ui_Left, 60);
    lv_obj_set_x(ui_Left, -200);
    lv_obj_set_y(ui_Left, 0);
    lv_obj_set_align(ui_Left, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Left, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Left, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_Left, ui_Left_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_Left, LV_OBJ_FLAG_CHECKABLE);

    ui_Right = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Right, 60);
    lv_obj_set_height(ui_Right, 60);
    lv_obj_set_x(ui_Right, -40);
    lv_obj_set_y(ui_Right, 0);
    lv_obj_set_align(ui_Right, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Right, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Right, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_Right, ui_Right_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_Right, LV_OBJ_FLAG_CHECKABLE);

    ui_back = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_back, 60);
    lv_obj_set_height(ui_back, 60);
    lv_obj_set_x(ui_back, -120);
    lv_obj_set_y(ui_back, 80);
    lv_obj_set_align(ui_back, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_back, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_back, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_back, ui_back_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_back, LV_OBJ_FLAG_CHECKABLE);

    ui_point = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_point, 100);
    lv_obj_set_height(ui_point, 50);
    lv_obj_set_x(ui_point, 120);
    lv_obj_set_y(ui_point, -80);
    lv_obj_set_align(ui_point, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_point, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_point, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_point, ui_point_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_point, LV_OBJ_FLAG_CLICKABLE );

    ui_continuous = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_continuous, 100);
    lv_obj_set_height(ui_continuous, 50);
    lv_obj_set_x(ui_continuous, 120);
    lv_obj_set_y(ui_continuous, 0);
    lv_obj_set_align(ui_continuous, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_continuous, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_continuous, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_continuous, ui_continuous_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_continuous, LV_OBJ_FLAG_CHECKABLE);

    ui_MotorStop = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_MotorStop, 100);
    lv_obj_set_height(ui_MotorStop, 50);
    lv_obj_set_x(ui_MotorStop, 120);
    lv_obj_set_y(ui_MotorStop, 80);
    lv_obj_set_align(ui_MotorStop, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MotorStop, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MotorStop, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_MotorStop, ui_MotorStop_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui_MotorStop, LV_OBJ_FLAG_CHECKABLE);

    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -120);
    lv_obj_set_y(ui_Label1, -35);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Forward");

    ui_Label2 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -150);
    lv_obj_set_y(ui_Label2, 0);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Left");

    ui_Label3 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -95);
    lv_obj_set_y(ui_Label3, 0);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Right");

    ui_Label4 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, -120);
    lv_obj_set_y(ui_Label4, 35);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Back");

    ui_Label5 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, 123);
    lv_obj_set_y(ui_Label5, -40);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "point_mode");

    ui_Label6 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 123);
    lv_obj_set_y(ui_Label6, 40);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "continuous_mode");

    ui_Label7 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, 123);
    lv_obj_set_y(ui_Label7, 120);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "Motor_Stop");
}
