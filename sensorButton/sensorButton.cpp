#include "sensorButton.h"



uint8_t BUTTON::BTN_Handler(btn_alias_t button){
//  /* --- Конечный автомат --- */
//  // Состояние «Ожидание нажатия»
//  if (fsm_state[button] == BTN_FSM_PRESS_CHECK) {

//    // Проверка состояния кнопки
//    if (((bool)(*port & mask) ^ pull) == true) {     // Если кнопка нажата...
//      fsm_state[button] = BTN_FSM_PRESS_DEBOUNCE;    // Переход к следующему состоянию
//    } else {                                         // Если кнопка не нажата...
//      return 0;                                  // Негативный выход
//    }
//  }

//  // Состояние «Защита от дребезга при нажатии»
//  if (fsm_state[button] == BTN_FSM_PRESS_DEBOUNCE) {

//    // Сброс счётчика
//    counter = 0;

//    // Цикл счёта
//    for (int i = 0; i < BTN_CNT_LIM; i++) {
//      counter += (bool)(*port & mask) ^ pull;
//    }

//    // Проверка состояния счётчика
//    if (counter == BTN_CNT_LIM) {                    // Если счётчик достиг предела...
//      fsm_state[button] = BTN_FSM_RELEASE_CHECK;     // Переход к следующему состоянию
//      return 1;                                   // Позитивный выход
//    } else {                                         // Если счётчик не достиг предела...
//      fsm_state[button] = BTN_FSM_PRESS_CHECK;       // Переход к начальному состоянию
//      return 0;                                  // Негативный выход
//    }
//  }

//  // Состояние «Ожидание отпускания»
//  if (fsm_state[button] == BTN_FSM_RELEASE_CHECK) {

//    // Проверка состояния кнопки
//    if (((bool)(*port & mask) ^ pull) == 0) {    // Если кнопка отпущена...
//      fsm_state[button] = BTN_FSM_RELEASE_DEBOUNCE;  // Переход к следующему состоянию
//    } else {                                         // Если кнопка не отпущена...
//      return 0;                                  // Негативный выход
//    }
//  }

//  // Состояние «Защита от дребезга при отпускании»
//  if (fsm_state[button] == BTN_FSM_RELEASE_DEBOUNCE) {

//    // Сброс счётчика
//    counter = 0;

//    // Цикл счёта
//    for (int i = 0; i < BTN_CNT_LIM; i++) {
//      counter += !((bool)(*port & mask) ^ pull);
//    }

//    // Проверка состояния накопителя
//    if (counter == BTN_CNT_LIM) {                    // Если счётчик достиг предела...
//      fsm_state[button] = BTN_FSM_PRESS_CHECK;       // Переход к начальному состоянию
//    } else {                                         // Если счётчик не достиг предела...
//      fsm_state[button] = BTN_FSM_RELEASE_CHECK;     // Переход к предыдущему состоянию
//    }
//    return 0;                                    // Негативный выход
//  }

//  // Во всех неопределенных случаях
//  // производится негативный выход
  return 0;
	
}
