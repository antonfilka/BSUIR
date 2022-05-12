#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "FSInfo.h"
#include "FAT.h"
#include <string>

const int NotUsed = system("color f0");

void outputInformation(struct bootSectorAfterConverting current_boot_sector, struct FSInfo current_FSInfo)
{
    outputBootSector(current_boot_sector);
    outputFSInfo(current_FSInfo);
}

wchar_t* getTheLetterOfTheDevice() {

    printf("Input the letter of the desired volume in a format of C: - ");
    char input_string[5];
    scanf("%s", input_string);
    char symbols[25] = "\\\\.\\";
    strcat(symbols, input_string);
    size_t newsize = strlen(symbols) + 1;
    wchar_t* wcstring = new wchar_t[newsize];
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, symbols, _TRUNCATE);
    return wcstring;

}

int main() {
    
    wchar_t* device_path = getTheLetterOfTheDevice();
    HANDLE current_device_descriptor = openDevice(device_path);

    struct bootSectorBeforeConverting current_boot_sector_BC = readBootSector(current_device_descriptor);
    struct bootSectorAfterConverting current_boot_sector_AC = convertingBootSector(current_boot_sector_BC);
    struct FSInfo current_FSInfo = readFSInfo(current_device_descriptor);

    seekDescriptor(current_device_descriptor, current_boot_sector_AC.backup_boot_sector_location * current_boot_sector_AC.bytes_per_sector);
    outputInformation(current_boot_sector_AC, current_FSInfo);
    
    check_FAT_32(current_boot_sector_AC);

    if (!checkCorrectFSInfo(current_FSInfo)) {
        outputFSInfoError();
    }

    struct bootSectorBeforeConverting backup_boot_sector_BC = readBootSector(current_device_descriptor);
    struct FSInfo backup_FSInfo = readFSInfo(current_device_descriptor);

    int is_normal_boot_sector = checkBootSector(current_boot_sector_AC);

    if (checkEqualBootSector(current_boot_sector_BC, backup_boot_sector_BC) != 0) {
        warningBootSector();
    }

    if (!checkEqualFSInfo(current_FSInfo, backup_FSInfo)) {
        warningFSInfo();
    }
    
    char** FATs = readFAT(current_device_descriptor,
        current_boot_sector_AC.number_reserved_sectors * current_boot_sector_AC.bytes_per_sector,
        current_boot_sector_AC.mirror_flags,
        current_boot_sector_AC.number_FAT_copies,
        current_boot_sector_AC.number_of_sectors_per_FAT * current_boot_sector_AC.bytes_per_sector

    );

    if (!checkEqualFAT(
        FATs,
        number_of_FATs(current_boot_sector_AC.mirror_flags, current_boot_sector_AC.number_FAT_copies),
        current_boot_sector_AC.number_of_sectors_per_FAT * current_boot_sector_AC.bytes_per_sector))
    {
        error_FATs();
    }
    
    system("pause");

    return 0;
}
