#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple structure for binary I/O demo
struct Record { int id; char name[50]; };

int main() {
    FILE *fp;
    char buffer[256];

    // --- Part 1: Text File Operations ---

    // 1. CREATE AND WRITE FILE (MODE "w")
    printf("1. Writing to file.txt (mode 'w')...\n");
    fp = fopen("file.txt", "w");
    if (fp == NULL) { perror("Error writing file.txt"); return 1; }
    fprintf(fp, "This is the first line.\n");
    fprintf(fp, "This is the second line.\n");
    fclose(fp);

    // 2. APPEND TO FILE (MODE "a")
    printf("\n2. Appending to file.txt (mode 'a')...\n");
    fp = fopen("file.txt", "a");
    if (fp == NULL) { perror("Error appending to file.txt"); return 1; }
    fprintf(fp, "This is the appended line.\n");
    fclose(fp);

    // 3. READ FROM FILE (MODE "r")
    printf("\n3. Reading from file.txt (mode 'r')...\n");
    fp = fopen("file.txt", "r");
    if (fp == NULL) { perror("Error reading file.txt"); return 1; }

    printf("--- File Contents ---\n");
    while (fgets(buffer, 256, fp) != NULL) {
        printf("%s", buffer);
    }
    printf("---------------------\n");
    fclose(fp);

    // 4. READ/WRITE (MODE "r+")
    printf("\n4. Modifying file with 'r+' mode...\n");
    fp = fopen("file.txt", "r+");
    if (fp == NULL) { perror("Error opening file.txt for r+"); return 1; }
    // Overwrite the first part of the file
    fprintf(fp, "---MODIFIED---");
    fclose(fp);
    printf("   Modified first line.\n");


    // --- Part 2: Binary File Operations ---

    struct Record rec_write = {101, "Alice"};
    struct Record rec_read;

    // 5. WRITE TO BINARY FILE (MODE "wb")
    printf("\n5. Writing struct to data.bin (mode 'wb')...\n");
    fp = fopen("data.bin", "wb");
    if (fp == NULL) { perror("Error opening data.bin for writing"); return 1; }
    fwrite(&rec_write, sizeof(struct Record), 1, fp);
    fclose(fp);
    printf("   Wrote ID: %d, Name: %s\n", rec_write.id, rec_write.name);

    // 6. READ FROM BINARY FILE (MODE "rb")
    printf("\n6. Reading struct from data.bin (mode 'rb')...\n");
    fp = fopen("data.bin", "rb");
    if (fp == NULL) { perror("Error opening data.bin for reading"); return 1; }
    fread(&rec_read, sizeof(struct Record), 1, fp);
    fclose(fp);
    printf("   Read ID: %d, Name: %s\n", rec_read.id, rec_read.name);


    // --- Part 3: File Management ---

    // 7. DELETE FILES
    printf("\n7. Deleting files...\n");
    
    if (remove("file.txt") == 0) {
        printf("   'file.txt' deleted successfully.\n");
    } else {
        perror("   Error deleting file.txt");
    }
    
    if (remove("data.bin") == 0) {
        printf("   'data.bin' deleted successfully.\n");
    } else {
        perror("   Error deleting data.bin");
    }

    printf("\nAll operations complete.\n");
    return 0;
}