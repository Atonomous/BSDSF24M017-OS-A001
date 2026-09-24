#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("========================================\n");
    printf("       TESTING STRING FUNCTIONS\n");
    printf("========================================\n");

    char str1[100];
    char str2[50] = "Operating Systems";
    
    // 1. mystrcpy
    mystrcpy(str1, "Hello");
    printf("[mystrcpy] Copied: '%s'\n", str1);

    // 2. mystrlen
    printf("[mystrlen] Length of '%s': %d\n", str1, mystrlen(str1));

    // 3. mystrcat
    mystrcat(str1, " World!");
    printf("[mystrcat] Concatenated: '%s'\n", str1);

    // 4. mystrncpy
    char str3[20];
    mystrncpy(str3, str2, 9);
    printf("[mystrncpy] Copied 9 chars: '%s'\n", str3);

    printf("\n========================================\n");
    printf("        TESTING FILE FUNCTIONS\n");
    printf("========================================\n");

    FILE* fp = fopen("testfile.txt", "w+");
    if (!fp) {
        perror("Failed to create test file");
        return 1;
    }

    fputs("Operating Systems Assignment 01\nLearning multi-file builds and linking\nOperating Systems is fun\n", fp);

    // 5. wordCount
    int lines = 0, words = 0, chars = 0;
    if (wordCount(fp, &lines, &words, &chars) == 0) {
        printf("[wordCount] Lines: %d | Words: %d | Characters: %d\n", lines, words, chars);
    }

    // 6. mygrep
    char** matches = NULL;
    int count = mygrep(fp, "Operating", &matches);
    printf("[mygrep] Pattern 'Operating' found in %d line(s):\n", count);
    for (int i = 0; i < count; i++) {
        printf("   Match %d: %s", i + 1, matches[i]);
        free(matches[i]);
    }
    free(matches);

    fclose(fp);
    remove("testfile.txt");

    printf("\nAll functions tested successfully.\n");
    return 0;
}
