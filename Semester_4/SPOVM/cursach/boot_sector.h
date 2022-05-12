#ifndef BOOT_SECTOR_H
#define BOOT_SECTOR_H

#include <windows.h>
#include <stdio.h>

#define CHAR unsighed char
#define __int1 unsigned char
#define __int2 unsigned short int
#define __int4 unsigned int
#define __int8 unsigned long long

#define BOOT_SECTOR_SIZE 512

#define media_byte_hard_disk 0xF8
#define media_byte_removable_disk 0xF0

#define INT_1 0x0001
#define INT_2 0x0002
#define INT_4 0x0004
#define INT_8 0x0008
#define INT_16 0x0010
#define INT_32 0x0020
#define INT_64 0x0040
#define INT_128 0x0080
#define INT_256 0x0100
#define INT_512 0x0200
#define INT_1024 0x0400
#define INT_2048 0x0800
#define INT_4096 0x1000

#define bool int
#define true 1
#define false 0

struct bootSectorBeforeConverting {
	unsigned char bootstrap[3];                                  // 0-2
	unsigned char OEM_name[8];                                   // 3-10
	unsigned char bytes_per_sector[2];                           // 11-12
	unsigned char sectors_per_cluster;                           // 13
	unsigned char number_reserved_sectors[2];                    // 14-15
	unsigned char number_FAT_copies;                             // 16
	unsigned char number_root_entries[2];                        // 17-18
	unsigned char total_number_sectors_NOFAT32[2];               // 19-20
	unsigned char media_descriptor_type;                         // 21
	unsigned char number_of_sectors_per_FAT_NOFAT32[2];          // 22-23; 0000 for FAT32
	unsigned char number_of_sectors_per_track[2];                // 24-25
	unsigned char number_of_heads[2];                            // 26-27
	unsigned char number_of_hidden_sectors[4];                   // 28-31
	unsigned char total_number_of_sectors[4];                    // 32-35
	unsigned char number_of_sectors_per_FAT[4];                  // 36-39
	unsigned char mirror_flags[2];                               // 40-41
	unsigned char filesystem_version[2];                         // 42-43
	unsigned char first_cluster_root_directory[4];               // 44-47
	unsigned char filesystem_information_sector[2];              // 48-49
	unsigned char backup_boot_sector_location[2];                // 50-51
	unsigned char reserved[12];                                  // 52-63
	unsigned char locival_drive_number;                          // 64
	unsigned char reserver_for_WindowsNT;                        // 65
	unsigned char extended_signature_0x29;                       // 66
	unsigned char serial_number_partition[4];                    // 67-70
	unsigned char volume_label[11];                              // 71-81
	unsigned char filesystem_type[8];                            // 82-89
	unsigned char bootstrap_data[420];                           // 90-509
	unsigned char signature_55AA[2];                              // 510-511
};


// number_root_entries * 32 / bytes_per_sector
// data sectors - total_number_of_sectors  - number_reserved_sectors + number_of_FATs * number_of_sectors_per_FAT +

struct bootSectorAfterConverting {
	unsigned char OEM_name[8];                                  // 3-10
	__int2 bytes_per_sector;                           // 11-12
	__int1 sectors_per_cluster;                        // 13
	__int2 number_reserved_sectors;                    // 14-15
	__int1 number_FAT_copies;                          // 16
	__int2 number_root_entries;                        // 17-18
	__int1 media_descriptor_type;                      // 21
	__int2 number_of_sectors_per_track;                // 24-25
	__int2 number_of_heads;                            // 26-27
	__int4 number_of_hidden_sectors;                   // 28-31
	__int4 total_number_of_sectors;                    // 32-35
	__int4 number_of_sectors_per_FAT;                  // 36-39
	__int2 mirror_flags;                               // 40-41
	__int4 first_cluster_root_directory;               // 44-47
	__int2 backup_boot_sector_location;                // 50-51
	__int2 signature_55AA;                     // 510-511
};

__int1 convertingCharInto_int1(unsigned char currentNumber)
{
	__int1 currentInt = 0;
	currentInt += (__int1)(currentNumber);
	return currentInt;
}

__int2 convertingCharInto_int2(unsigned char currentNumber[2])
{
	__int2 currentInt = 0;
	currentInt += (__int2)(currentNumber[1] << 8);
	currentInt += (__int2)(currentNumber[0]);
	return currentInt;
}

__int4 convertingCharInto_int4(unsigned char currentNumber[4])
{
	__int4 currentInt = 0;
	currentInt += (__int4)(currentNumber[3] << 24);
	currentInt += (__int4)(currentNumber[2] << 16);
	currentInt += (__int4)(currentNumber[1] << 8);
	currentInt += (__int4)currentNumber[0];
	return currentInt;
}

struct bootSectorAfterConverting convertingBootSector(struct bootSectorBeforeConverting current_boot_sector_BC)
{
	struct bootSectorAfterConverting current_boot_sector_AC;

	for (int i = 0; i < 8; i++) {
		current_boot_sector_AC.OEM_name[i] = current_boot_sector_BC.OEM_name[i];
	}

	current_boot_sector_AC.bytes_per_sector = convertingCharInto_int2(current_boot_sector_BC.bytes_per_sector);
	current_boot_sector_AC.sectors_per_cluster = convertingCharInto_int1(current_boot_sector_BC.sectors_per_cluster);
	current_boot_sector_AC.number_reserved_sectors = convertingCharInto_int2(current_boot_sector_BC.number_reserved_sectors);
	current_boot_sector_AC.number_FAT_copies = convertingCharInto_int1(current_boot_sector_BC.number_FAT_copies);
	current_boot_sector_AC.number_root_entries = 32;
	current_boot_sector_AC.media_descriptor_type = convertingCharInto_int1(current_boot_sector_BC.media_descriptor_type);
	current_boot_sector_AC.number_of_sectors_per_track = convertingCharInto_int2(current_boot_sector_BC.number_of_sectors_per_track);
	current_boot_sector_AC.number_of_heads = convertingCharInto_int2(current_boot_sector_BC.number_of_heads);
	current_boot_sector_AC.number_of_hidden_sectors = convertingCharInto_int4(current_boot_sector_BC.number_of_hidden_sectors);
	current_boot_sector_AC.total_number_of_sectors = convertingCharInto_int4(current_boot_sector_BC.total_number_of_sectors);
	current_boot_sector_AC.number_of_sectors_per_FAT = convertingCharInto_int4(current_boot_sector_BC.number_of_sectors_per_FAT);
	current_boot_sector_AC.mirror_flags = convertingCharInto_int2(current_boot_sector_BC.mirror_flags);
	current_boot_sector_AC.first_cluster_root_directory = convertingCharInto_int4(current_boot_sector_BC.first_cluster_root_directory);
	current_boot_sector_AC.backup_boot_sector_location = convertingCharInto_int2(current_boot_sector_BC.backup_boot_sector_location);
	current_boot_sector_AC.signature_55AA = convertingCharInto_int2(current_boot_sector_BC.signature_55AA);
	return current_boot_sector_AC;
}

void errorOpenDevice()
{
	printf("\nThere is no such directory, or it isn't possible to open your device for reading. Please check your device and try again\n");
	system("pause");
	exit(0);
}

HANDLE openDevice(wchar_t* device_path)
{
	HANDLE hDevice;
	hDevice = CreateFileW(device_path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hDevice == INVALID_HANDLE_VALUE) // невозможно открыть устройство
	{
		errorOpenDevice();

	}
	return hDevice;
}

void errorReadDevice()
{
	printf("\n Cannot read memory from Your device. \n");
	system("pause");
	exit(0);
}

void seekDescriptor(HANDLE deviceDescriptor, __int8 offset)
{
	_LARGE_INTEGER integer;
	integer.QuadPart = offset;
	if (SetFilePointerEx(deviceDescriptor, integer, NULL, FILE_BEGIN) == 0) errorReadDevice();

}

struct bootSectorBeforeConverting readBootSector(HANDLE current_device_descriptor)
{
	struct bootSectorBeforeConverting current_boot_sector;
	if (ReadFile(current_device_descriptor, &current_boot_sector, sizeof(struct bootSectorBeforeConverting), NULL, NULL) == 0) errorReadDevice();
	return current_boot_sector;
}

void warningBootSector()
{
	printf("WARNING in boot sector. Main boot sector does not match backup boot sector!\n");
}

void check_FAT_32(struct bootSectorAfterConverting current_boot_sector)
{
	long long root_dir_sectors = 1LL * current_boot_sector.number_root_entries * 32 / current_boot_sector.bytes_per_sector;
	long long data = current_boot_sector.total_number_of_sectors - (current_boot_sector.number_reserved_sectors +
		current_boot_sector.number_FAT_copies * current_boot_sector.number_of_sectors_per_FAT + root_dir_sectors);
	long long answer = data / current_boot_sector.sectors_per_cluster;
	if (answer < 4085) {
		printf("Your device is formated into FAT12 - NOT OKEY\n");
	}
	if (answer >= 4085 && answer <= 65524) {
		printf("Your device is formated into FAT16 - NOT OKEY\n");
	}
	if (answer > 65524) {
		printf("Your device is formated into FAT32 - OK!\n");
	}
}

void outputBootSector(struct bootSectorAfterConverting current_boot_sector)
{
	printf("System ID \"%s\"\n", current_boot_sector.OEM_name);
	printf("Media byte \"%x\"\n", current_boot_sector.media_descriptor_type);
	if (current_boot_sector.media_descriptor_type == media_byte_hard_disk) {
		printf("Hard disk\n");
	}
	if (current_boot_sector.media_descriptor_type == media_byte_removable_disk) {
		printf("Removable disk\n");
	}
	printf("%d bytes per logical sector\n", current_boot_sector.bytes_per_sector);
	printf("%lld bytes per cluster\n", (__int8)(current_boot_sector.sectors_per_cluster * current_boot_sector.bytes_per_sector));
	printf("%d reserved sectors\n", current_boot_sector.number_reserved_sectors);
	printf("First FAT starts at byte %lld (sector %d)\n",
		(__int8)(current_boot_sector.number_reserved_sectors * current_boot_sector.bytes_per_sector),
		current_boot_sector.number_reserved_sectors
	);
	printf("%d FATs, %d bit entries\n", current_boot_sector.number_FAT_copies, current_boot_sector.number_root_entries);
	printf("%lld bytes per FAT (%d sectors)\n",
		(__int8)(current_boot_sector.number_of_sectors_per_FAT * current_boot_sector.bytes_per_sector),
		current_boot_sector.number_of_sectors_per_FAT
	);
	printf("Root directory start at cluster %d\n", current_boot_sector.first_cluster_root_directory);
	__int8 data_area_sector = (current_boot_sector.number_FAT_copies * current_boot_sector.number_of_sectors_per_FAT) +
		current_boot_sector.number_reserved_sectors;
	__int8 data_clusters = (current_boot_sector.total_number_of_sectors - current_boot_sector.number_FAT_copies *
		current_boot_sector.number_of_sectors_per_FAT - current_boot_sector.number_reserved_sectors) /
		current_boot_sector.sectors_per_cluster;
	printf("Data area starts at byte %lld (sector %d)\n", data_area_sector * current_boot_sector.bytes_per_sector, data_area_sector);
	printf("%lld data clusters (%lld bytes)\n", data_clusters, (__int8)data_clusters * current_boot_sector.sectors_per_cluster *
		current_boot_sector.bytes_per_sector);
	printf("%d sectors/track, %d heads\n", current_boot_sector.number_of_sectors_per_track, current_boot_sector.number_of_heads);
	printf("%d sectors total\n", current_boot_sector.total_number_of_sectors);
	printf("\n");
}

int checkEqualBootSector(struct bootSectorBeforeConverting first_boot_sector, struct bootSectorBeforeConverting second_boot_sector)
{
	second_boot_sector.reserver_for_WindowsNT = first_boot_sector.reserver_for_WindowsNT;
	return memcmp(&first_boot_sector, &second_boot_sector, sizeof(struct bootSectorBeforeConverting));
}

// 0 - normal 1 - warning 2 - error
int checkBootSector(struct bootSectorAfterConverting current_boot_sector)
{
	int current_check = 0;
	__int1 MDT = current_boot_sector.media_descriptor_type; // MDT - media descriptor type
	if (MDT != media_byte_hard_disk && MDT != media_byte_removable_disk) {
		printf("WARNING: media descriptor type should be 0xF0(removable disk) or 0xF8(hard disk). Your device media descriptor: %x\n", MDT);
		current_check = 1;
	}
	__int1 NFC = current_boot_sector.number_FAT_copies; //NFC - number of fat copies
	if (NFC != 2) {
		printf("WARNING: number of FAT copies should be 2. Your device number of FAT copies: %d\n", NFC);
		current_check = 1;
	}
	if (current_boot_sector.signature_55AA != 0xAA55) {
		printf("WARNING: 510-511 bytes should be 0x55AA. Your device 510-511 bytes: %x\n", current_boot_sector.signature_55AA);
		current_check = 1;
	}
	__int2 BPS = current_boot_sector.bytes_per_sector; // BPS - bytes per sector
	if (BPS != INT_512 && BPS != INT_1024 && BPS != INT_2048 && BPS != INT_4096) {
		printf("ERROR: bytes per sector must be 512, 1024, 2048, 4096. From your device: %d\n", BPS);
		current_check = 2;
	}
	__int1 SPC = current_boot_sector.sectors_per_cluster; //SPC sectors per cluster
	if (SPC != INT_1 && SPC != INT_2 && SPC != INT_4 && SPC != INT_8 && SPC != INT_16 && SPC != INT_32 && SPC != INT_64 && SPC != INT_128) {
		printf("ERROR: sector per cluster must be 1, 2, 4, 8, 16, 32, 64, 128. From your device: %d\n", SPC);
		current_check = 2;
	}
	__int4 SOC = BPS * SPC; // SOC - size of clusters
	if (SOC > 65536) {
		printf("ERROR: A cluster should have at most 32768 bytes. In rare cases 65536 is OK. Your device cluster's size: %d\n", SOC);
		current_check = 2;
	}
	return current_check;
}

#endif BOOT_SECTOR_H
