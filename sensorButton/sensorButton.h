#ifndef _SENSOR_BUTTON_H
#define _SENSOR_BUTTON_H
#include "MDR1986VE1T.h"                // Device header



// Количество кнопок
#define BTN_NUM 6

// Предел счётчика
#define BTN_CNT_LIM 128

// Псевдонимы кнопок
typedef enum {
  BTN_U = 0,  // Кнопка UP
  BTN_D = 1,  // Кнопка DOWN
  BTN_L = 2,  // Кнопка LEFT
  BTN_R = 3,  // Кнопка RIGHT
  BTN_M = 4,  // Кнопка MID
  BTN_S = 5   // Кнопка SENSE
} btn_alias_t;

// Псевдонимы состояний конечного автомата
// (Finite-State Machine, FSM)
typedef enum {
  BTN_FSM_PRESS_CHECK      = 0,  // «Ожидание нажатия»
  BTN_FSM_PRESS_DEBOUNCE   = 1,  // «Защита от дребезга при нажатии»
  BTN_FSM_RELEASE_CHECK    = 2,  // «Ожидание отпускания»
  BTN_FSM_RELEASE_DEBOUNCE = 3   // «Защита от дребезга при отпускании»
} btn_fsm_t;


class BUTTON{
	public:
		BUTTON();
	~BUTTON();
	
	uint8_t BTN_Handler(btn_alias_t button);
	private:


};



class SENSOR_BUTTON{


};
#endif
