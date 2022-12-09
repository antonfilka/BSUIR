#include <iomanip>
#include <iostream>

#include "hexioctrl.h"
#include "port.h"

using namespace std;

// Макросы, представляющие команды
// для устройств ATA.
#define IDENTIFY_PACKET_DEVICE 0xA1
#define IDENTIFY_DEVICE        0xEC

// Регистры устройств ATA.
const WORD AS[2] = { 0x3F6, 0x376 }; // алтернативный регистр состояния
const WORD DR[2] = { 0x1F0, 0x170 }; // регисьр данных 
const WORD DH[2] = { 0x1F6, 0x176 }; // регистр адрессас
const WORD SR[2] = { 0x1F7, 0x177 }; // регистр состояния
const WORD CR[2] = { 0x1F7, 0x177 }; // регистр комманд

// Данные, получаемые из регистра данных.
WORD data[256];

// Ожидает, пока устройство ATA занято.
void WaitBusy(int channel);

// Ожидает, пока устройство ATA не готово
// к работе.
BOOL WaitReady(int channel);

// Получение дискового устройства ATA, при
// этом записывая всю необходимую информацию
// в `data'.
BOOL GetATADevice(int channel, int device);

// Печать полученной информации,
// находящейся в `data'.
void PrintData(int channel, int device);

int main()
{
	ALLOW_IO_OPERATIONS;

	setlocale(LC_ALL, ".1251");

	// Печать разделительной линии.
	cout << setw(77) << setfill('=') << "" << endl;

	// Перебираем все возможные
	// устройства ATA.
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

	// Ожидаем обнуления бита BSY.
	do
		state = InPort(AS[channel]);
	while (state & 0x80); // 0x80  == 1000 0000
}

BOOL WaitReady(int channel)
{
	for (int i = 0; i < 1000; ++i)
		// Если устройство ATA готово к работе...
		if (InPort(AS[channel]) & 0x40)
			return true;

	return false;
}

BOOL GetATADevice(int channel, int device)
{
	// Массив, представляющий
	// команды.
	const BYTE commands[] = {
		IDENTIFY_PACKET_DEVICE, // добавить инфу о сидиромах
		IDENTIFY_DEVICE, // добавить инфу о всех дисках
	};

	// Перебор всех команд.
	for (int i = 0; i < sizeof(commands); ++i) {
		// Ожидаем обнуления бита BSY.
		WaitBusy(channel);

		// Формируем адрес устройства ATA.
		OutPort(DH[channel], (device << 4) | 0xE0);

		// Дожидаемся признака готовности, если
		// устройство ATA присутствует.
		if (!WaitReady(channel))
			return false;

		// Записываем код команды в регистр команд.
		OutPort(CR[channel], commands[i]);

		// Ожидаем обнуления бита BSY.
		WaitBusy(channel);

		// Проверка на ошибку.
		if (!(InPort(SR[channel]) & 0x08)) {
			// Если ошибка произошла при обработке
			// команды IDENTIFY_DEVICE...
			if (i == 1)
				return false;

			continue;
		} else
			break;
	}

	// Получение конфигурационного блока.
	for (int i = 0; i < 256; ++i)
		data[i] = InPortW(DR[channel]);

	return true;
}

void PrintData(int channel, int device)
{
	cout << setw(30) << setfill(' ') << left << "РАЗМЕЩЕНИЕ:";
	cout << channel << ", " << device;
	// Печать типа устройства ATA.
	cout << endl << endl << setw(29) << setfill(' ') << left << "ТИП:";
	for (int i = 29; i <= 46; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);
	// Печать модели устройства ATA.
	cout << endl << endl << setw(30) << setfill(' ') << left << "МОДЕЛЬ:";
	for (int i = 27; i <= 46; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

	// Печать серийного номера устройства ATA.
	cout << endl << setw(30) << setfill(' ') << left << "Серийный номер:";
	for (int i = 10; i <= 19; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

	// Печать версии прошивки устройства ATA.
	cout << endl << setw(30) << setfill(' ') << left << "Версия прошивки:";
	for (int i = 23; i <= 26; ++i)
		cout << (CHAR)(data[i] >> 8) << (CHAR)(data[i] & 0x00FF);

	// Печать размера устройства ATA в МБ.
	cout << endl << endl << setw(30) << setfill(' ') << left << "РАЗМЕР:";
	cout << setprecision(0) << (long double)(((ULONG *)data)[30]) * 512 / 1024 / 1024 << " МБ";
		// Печать поддержки PIO.
	cout << endl << endl << "Поддержка PIO:";
	cout << endl << "  (" << (data[64] & 0x1 ? "+" : "-") << ") PIO 3";
	cout << endl << "  (" << (data[64] & 0x2 ? "+" : "-") << ") PIO 4";

	// Печать поддержки Multiword DMA.
	cout << endl << endl << "Поддержка Multiword DMA:";
	cout << endl << "  (" << (data[63] & 0x1 ? "+" : "-") << ") MWDMA 0";
	cout << endl << "  (" << (data[63] & 0x2 ? "+" : "-") << ") MWDMA 1";
	cout << endl << "  (" << (data[63] & 0x4 ? "+" : "-") << ") MWDMA 2";

	// Печать поддержки Ultra DMA.
	cout << endl << endl << "Поддержка Ultra DMA:";
	cout << endl << "  (" << (data[88] & 0x1 ? "+" : "-") << ") UDMA 0";
	cout << endl << "  (" << (data[88] & 0x2 ? "+" : "-") << ") UDMA 1";
	cout << endl << "  (" << (data[88] & 0x4 ? "+" : "-") << ") UDMA 2";
	cout << endl << "  (" << (data[88] & 0x8 ? "+" : "-") << ") UDMA 3";
	cout << endl << "  (" << (data[88] & 0x10 ? "+" : "-") << ") UDMA 4";
	cout << endl << "  (" << (data[88] & 0x20 ? "+" : "-") << ") UDMA 5";

	// Печать поддержки версий ATA.
	cout << endl << endl << "Поддержка версий ATA:";
	cout << endl << "  (" << (data[80] & 0x2 ? "+" : "-") << ") ATA 1";
	cout << endl << "  (" << (data[80] & 0x4 ? "+" : "-") << ") ATA 2";
	cout << endl << "  (" << (data[80] & 0x8 ? "+" : "-") << ") ATA 3";
	cout << endl << "  (" << (data[80] & 0x10 ? "+" : "-") << ") ATA 4";
	cout << endl << "  (" << (data[80] & 0x20 ? "+" : "-") << ") ATA 5";
	cout << endl << "  (" << (data[80] & 0x40 ? "+" : "-") << ") ATA 6";
	cout << endl << "  (" << (data[80] & 0x80 ? "+" : "-") << ") ATA 7";

	cout << endl;
}
