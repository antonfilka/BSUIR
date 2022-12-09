#include "port.h"

BYTE InPort(WORD port)
{
	BYTE result;

	__asm {
		mov DX, port
		in AL, DX
		mov result, AL
	}

	return result;
}

WORD InPortW(WORD port)
{
	WORD result;

	__asm {
		mov DX, port
		in AX, DX
		mov result, AX
	}

	return result;
}

void OutPort(WORD port, BYTE value)
{
	__asm {
		mov DX, port
		mov AL, value
		out DX, AL
	}
}

void OutPort(WORD port, WORD value)
{
	__asm {
		mov DX, port
		mov AX, value
		out DX, AX
	}
}
