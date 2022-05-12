#include "boot_sector.h"

const __int4 correct_first_signature = 0x41615252;
const __int4 correct_second_signature = 0x61417272;
const __int4 correct_third_signature = 0xAA550000;
const __int4 correct_FSInfo_cluster = 0xFFFFFFFF;

#define FSINFO_SIZE 512

struct FSInfo {
    unsigned char first_signature[4];
    unsigned char first_reserved[480];
    unsigned char second_signature[4];
    unsigned char free_cluster_count[4];
    unsigned char next_free_cluster[4];
    unsigned char second_reserved[12];
    unsigned char third_signature[4];
};

struct FSInfo readFSInfo(HANDLE current_device_descriptor)
{
    struct FSInfo current_FSInfo;
    if(ReadFile(current_device_descriptor, &current_FSInfo, sizeof(struct FSInfo), NULL, NULL)==0) errorReadDevice();
    return current_FSInfo;
}


void outputFSInfo(struct FSInfo current_FSInfo)
{
    printf("\n");
    printf("%d - free clusters\n", convertingCharInto_int4(current_FSInfo.free_cluster_count));
    printf("0x%x - next free cluster\n", convertingCharInto_int4(current_FSInfo.next_free_cluster));
    printf("\n");
}

void outputFSInfoError()
{
    printf("ERROR in FSInfo. Signatures is not correctly!\n");
}

int checkCorrectFSInfo(struct FSInfo current_FSInfo)
{
    if (convertingCharInto_int4(current_FSInfo.first_signature) != correct_first_signature) {

        return 0;
    }
    if (convertingCharInto_int4(current_FSInfo.second_signature) != correct_second_signature) {
        return 0;
    }
    if (convertingCharInto_int4(current_FSInfo.third_signature) != correct_third_signature) {
        return 0;
    }
    return 1;
}

void warningFSInfo()
{
    printf("WARNING in FSInfo. Main FSInfo does not match backup FSInfo!\n");
}

int checkEqualFSInfo(struct FSInfo first_FSInfo, struct FSInfo second_FSInfo)
{
    __int4 first_total_clusters = convertingCharInto_int4(first_FSInfo.free_cluster_count);
    __int4 second_total_clusters = convertingCharInto_int4(second_FSInfo.free_cluster_count);
    __int4 first_next_cluster = convertingCharInto_int4(first_FSInfo.next_free_cluster);
    __int4 second_next_cluster = convertingCharInto_int4(second_FSInfo.next_free_cluster);
    if (first_total_clusters != correct_FSInfo_cluster && second_total_clusters != correct_FSInfo_cluster &&
        first_total_clusters != second_total_clusters) {
        return 0;
    }
    if (first_next_cluster != correct_FSInfo_cluster && second_next_cluster != correct_FSInfo_cluster &&
        first_next_cluster != second_next_cluster) {
        return 0;
    }
    return 1;
}
