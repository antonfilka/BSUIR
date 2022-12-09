#include <iomanip>
#include <iostream>

#include "hexioctrl.h"
#include "port.h"

using namespace std;

// �������, �������������� �������
// ��� ��������� ATA.
#define IDENTIFY_PACKET_DEVICE 0xA1
#define IDENTIFY_DEVICE        0xEC

// �������� ��������� ATA.
const WORD AS[2] = { 0x3F6, 0x376 }; // ������������� ������� ���������
const WORD DR[2] = { 0x1F0, 0x170 }; // ������� ������ 
const WORD DH[2] = { 0x1F6, 0x176 }; // ������� ��������
const WORD SR[2] = { 0x1F7, 0x177 }; // ������� ���������
const WORD CR[2] = { 0x1F7, 0x177 }; // ������� �������

// ������, ���������� �� �������� ������.
WORD data[256];

// �������, ���� ���������� ATA ������.
void WaitBusy(int channel);

// �������, ���� ���������� ATA �� ������
// � ������.
BOOL WaitReady(int channel);

// ��������� ��������� ���������� ATA, ���
// ���� ��������� ��� ����������� ����������
// � `data'.
BOOL GetATADevice(int channel, int device);

// ������ ���������� ����������,
// ����������� � `data'.
void PrintData(int channel, int device);

int main()
{
	ALLOW_IO_OPERATIONS;

	setlocale(LC_ALL, ".1251");

	// ������ �������������� �����.
	cout << setw(77) << setfill('=') << "" << endl;

	// ���������� ��� ���������
	// ���������� ATA.
	int channel = 0;
	for (int device = 0; device < 2; ++device)
		if (GetATADevice(channel, device)) {
			PrintData(channel, device);
			cout << endl;
			cout << setw(77) << setfill('=') << "" << endl;
		}

	system("pause");

	return 0;
}

void WaitBusy(int channel)
{
	BYTE state;

	// ������� ��������� ���� BSY.
	do
		state = InPort(AS[channel]);
	while (state & 0x80); // 0x80  == 1000 0000
}

BOOL WaitReady(int channel)
{
	for (int i = 0; i < 1000; ++i)
		// ���� ���������� ATA ������ � ������...
		if (InPort(AS[channel]) & 0x40)
			return true;

	return false;
}

BOOL GetATADevice(int channel, int device)
{
	// ������, ��������������
	// �������.
	const BYTE commands[] = {
		IDENTIFY_PACKET_DEVICE, // �������� ���� � ���������
		IDENTIFY_DEVICE, // �������� ���� � ���� ������
	};

	// ������� ���� ������.
	for (int i = 0; i < sizeof(commands); ++i) {
		// ������� ��������� ���� BSY.
		WaitBusy(channel);

		// ��������� ����� ���������� ATA.
		OutPort(DH[channel], (device << 4) | 0xE0);

		// ���������� �������� ����������, ����
		// ���������� ATA ������������.
		if (!WaitReady(channel))
			return false;

		// ���������� ��� ������� � ������� ������.
		OutPort(CR[channel], commands[i]);

		// ������� ��������� ���� BSY.
		WaitBusy(channel);

		// �������� �� ������.
		if (!(InPort(SR[channel]) & 0x08)) {
			// ���� ������ ��������� ��� ���������
			// ������� IDENTIFY_DEVICE...
			if (i == 1)
				return false;

			continue;
		} else
			break;
	}

	// ��������� ����������������� �����.
	for (int i = 0; i < 256; ++i)
		data[i] = InPortW(DR[channel]);

	return true;
}

void PrintData(int channel, int device)
{
	cout << setw(30) << setfill(' ') << left << "����������:";
	cout << channel << ", " << device;
	// ������ ���� ���������� ATA.
	cout << endl << endl << setw(29) << setfill(' ') << left << "���:";
	for (int i = 29; i <= 46; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);
	// ������ ������ ���������� ATA.
	cout << endl << endl << setw(30) << setfill(' ') << left << "������:";
	for (int i = 27; i <= 46; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

	// ������ ��������� ������ ���������� ATA.
	cout << endl << setw(30) << setfill(' ') << left << "�������� �����:";
	for (int i = 10; i <= 19; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

	// ������ ������ �������� ���������� ATA.
	cout << endl << setw(30) << setfill(' ') << left << "������ ��������:";
	for (int i = 23; i <= 26; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

	// ������ ������� ���������� ATA � ��.
	cout << endl << endl << setw(30) << setfill(' ') << left << "������:";
	cout << setprecision(0) << (long double)(((ULONG *)data)[30]) * 512 / 1024 / 1024 << " ��";
		// ������ ��������� PIO.
	cout << endl << endl << "��������� PIO:";
	cout << endl << "  (" << (data[64] & 0x1 ? "+" : "-") << ") PIO 3";
	cout << endl << "  (" << (data[64] & 0x2 ? "+" : "-") << ") PIO 4";

	// ������ ��������� Multiword DMA.
	cout << endl << endl << "��������� Multiword DMA:";
	cout << endl << "  (" << (data[63] & 0x1 ? "+" : "-") << ") MWDMA 0";
	cout << endl << "  (" << (data[63] & 0x2 ? "+" : "-") << ") MWDMA 1";
	cout << endl << "  (" << (data[63] & 0x4 ? "+" : "-") << ") MWDMA 2";

	// ������ ��������� Ultra DMA.
	cout << endl << endl << "��������� Ultra DMA:";
	cout << endl << "  (" << (data[88] & 0x1 ? "+" : "-") << ") UDMA 0";
	cout << endl << "  (" << (data[88] & 0x2 ? "+" : "-") << ") UDMA 1";
	cout << endl << "  (" << (data[88] & 0x4 ? "+" : "-") << ") UDMA 2";
	cout << endl << "  (" << (data[88] & 0x8 ? "+" : "-") << ") UDMA 3";
	cout << endl << "  (" << (data[88] & 0x10 ? "+" : "-") << ") UDMA 4";
	cout << endl << "  (" << (data[88] & 0x20 ? "+" : "-") << ") UDMA 5";

	// ������ ��������� ������ ATA.
	cout << endl << endl << "��������� ������ ATA:";
	cout << endl << "  (" << (data[80] & 0x2 ? "+" : "-") << ") ATA 1";
	cout << endl << "  (" << (data[80] & 0x4 ? "+" : "-") << ") ATA 2";
	cout << endl << "  (" << (data[80] & 0x8 ? "+" : "-") << ") ATA 3";
	cout << endl << "  (" << (data[80] & 0x10 ? "+" : "-") << ") ATA 4";
	cout << endl << "  (" << (data[80] & 0x20 ? "+" : "-") << ") ATA 5";
	cout << endl << "  (" << (data[80] & 0x40 ? "+" : "-") << ") ATA 6";
	cout << endl << "  (" << (data[80] & 0x80 ? "+" : "-") << ") ATA 7";

	cout << endl;
}
