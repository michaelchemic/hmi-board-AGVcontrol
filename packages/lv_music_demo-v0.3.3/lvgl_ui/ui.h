// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Forward;
extern lv_obj_t * ui_Left;
extern lv_obj_t * ui_Right;
extern lv_obj_t * ui_back;
extern lv_obj_t * ui_point;
extern lv_obj_t * ui_continuous;
extern lv_obj_t * ui_MotorStop;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui____initial_actions0;

static void ui_Forward_event_handler(lv_event_t * e);
static void ui_Left_event_handler(lv_event_t * e);
static void ui_Right_event_handler(lv_event_t * e);
static void ui_back_event_handler(lv_event_t * e);
static void ui_point_event_handler(lv_event_t * e);
static void ui_continuous_event_handler(lv_event_t * e);
static void ui_MotorStop_event_handler(lv_event_t * e);





void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif