#include "headers.h"
void printProcessInfo(int pid) {
    // Get process status
    char statusFilePath[1024];
    snprintf(statusFilePath, sizeof(statusFilePath), "/proc/%d/status", pid);

    FILE *statusFile = fopen(statusFilePath, "r");
    if (!statusFile) {
        perror("fopen status");
        return;
    }

    char line[256];
    char processStatus[16];
    while (fgets(line, sizeof(line), statusFile)) {
        if (strncmp(line, "State:", 6) == 0) {
            sscanf(line, "State:\t%s", processStatus);
            break;
        }
    }
    fclose(statusFile);

    char processGroup[16];
    snprintf(processGroup, sizeof(processGroup), "%d", pid);

    // Get virtual memory size
    char vmSize[16];
    snprintf(vmSize, sizeof(vmSize), "N/A"); // Default value if not available
    snprintf(statusFilePath, sizeof(statusFilePath), "/proc/%d/statm", pid);

    FILE *statmFile = fopen(statusFilePath, "r");
    if (statmFile) {
        unsigned long long vmData;
        fscanf(statmFile, "%llu", &vmData);
        fclose(statmFile);

        snprintf(vmSize, sizeof(vmSize), "%llu", vmData);
    }

    // Get executable path
    char exePath[1024];
    snprintf(exePath, sizeof(exePath), "/proc/%d/exe", pid);
    ssize_t readlinkSize = readlink(exePath, exePath, sizeof(exePath) - 1);
    if (readlinkSize != -1) {
        exePath[readlinkSize] = '\0';
    } else {
        perror("readlink");
        snprintf(exePath, sizeof(exePath), "N/A");
    }

    printf("pid : %d\n", pid);
    printf("process status : %s\n", processStatus);
    printf("Process Group : %s\n", processGroup);
    printf("Virtual memory : %s\n", vmSize);
    printf("executable path : %s\n", exePath);
}

void proclore(char input[100]) {
    char *args=input+8;
            char* token=strtok(args," ");
    if (token == NULL) {
        int pid = getpid();
        printProcessInfo(pid);
    } else {
        int pid = atoi(token);
        printProcessInfo(pid);
    }
}




