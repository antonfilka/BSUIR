#ifndef PORT_H
#define PORT_H

#include <windows.h>

// Функции для чтения
// из портов ввода/вывода.
BYTE InPort(WORD port);
WORD InPortW(WORD port);

// Функция для записи в
// порты ввода/вывода.
void OutPort(WORD port, BYTE value);
void OutPortW(WORD port, WORD value);

#endif // PORT_H.