#ifndef PORT_H
#define PORT_H

#include <windows.h>

// ������� ��� ������
// �� ������ �����/������.
BYTE InPort(WORD port);
WORD InPortW(WORD port);

// ������� ��� ������ �
// ����� �����/������.
void OutPort(WORD port, BYTE value);
void OutPortW(WORD port, WORD value);

#endif // PORT_H.