#include "boot_sector.h"

void errorMirrorFlags()
{
    printf("ERROR: error with finding or reading FAT\n");
    system("pause");
    exit(0);
}

void error_FATs()
{
    printf("ERROR: error with FATs, not equal\n");
}

void errorMemoryFAT()
{
    printf("ERROR: cannot allocate memory for FATs\n");
    system("pause");
    exit(0);
}

__int1 number_of_FATs(__int2 mirrorFlags, __int1 number_FAT_copies)
{
    int current_number_FAT = number_FAT_copies;
    int current_flag = (mirrorFlags & 0x0080);
    if (current_flag) {
        current_number_FAT = 1; // 7-th bit of flag meams that active is only one FAT, if 7-th bit = zero, all FATs are active
    }
    return current_number_FAT;
}

char** readFAT(HANDLE device_descriptor, __int8 offset_first_FAT, __int2 mirror_flags, __int1 number_FAT_copies, __int8 count_bytes_FAT)
{
    int current_number_FAT = number_FAT_copies;
    int current_flag = (mirror_flags & 0x0080);
    int is_simple_FAT = 0;
    int isFind = 0;
    if (current_flag) {
        current_number_FAT = 1; // 7-th bit of flag means that active is only one FAT, if 7-th bit = zero, all FATs are active
        is_simple_FAT = 1;
        if ((mirror_flags & 0x0001) > 0) {
            isFind++;
        }
        if ((mirror_flags & 0x0002) > 0) {
            isFind++;
            offset_first_FAT += count_bytes_FAT;
        }
        if ((mirror_flags & 0x0004) > 0) {
            isFind++;
            offset_first_FAT += 2 * count_bytes_FAT;
        }
        if ((mirror_flags & 0x0008) > 0) {
            isFind++;
            offset_first_FAT += 3 * count_bytes_FAT;
        }
    }
    if (is_simple_FAT && (isFind == 0 || isFind > 1)) {
        errorMirrorFlags();
        return NULL;
    }

    char** FATs = (char**)malloc(current_number_FAT * sizeof(char*));

    if (!FATs) {
        errorMemoryFAT();
        return NULL;
    }

    for (int i = 0; i < current_number_FAT; i++) {
        FATs[i] = (char*)malloc(count_bytes_FAT * sizeof(char));
        if (!FATs[i]) {
            errorMemoryFAT();
            free(FATs);
            return NULL;
        }
    }
    seekDescriptor(device_descriptor, offset_first_FAT);

    for (int i = 0; i < current_number_FAT; i++) {

        if (ReadFile(device_descriptor, FATs[i], count_bytes_FAT, NULL, NULL) == 0) {
            errorMirrorFlags();
            return NULL;
        }
    }
    return FATs;
}

int checkEqualFAT(char** FATs, __int1 number_of_FATs, __int8 size_of_FAT)
{
    for (int i = 0; i < number_of_FATs - 1; i++) {

        for (int j = 0; j < size_of_FAT; j++) {

            if (FATs[i][j] != FATs[i + 1][j]) {

                return 0;
            }
        }

    }
    return 1;
}
