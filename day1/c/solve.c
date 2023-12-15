#include <bits/time.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char *word;
    char digits;
} lookup_table;

char *substr(const char *, size_t, size_t);

char *substr(const char *str, size_t pos, size_t len) {
    size_t str_len = strlen(str);
    if (pos >= str_len) {
        fprintf(stderr, "Error: pos out of range\n");
        return NULL;
    }

    len = (pos + len > str_len) ? (str_len - pos) : len;

    char *result = (char *)malloc(sizeof(char) * (len + 1));
    if (result == NULL) {
        perror("Error allocating memory");
        return NULL;
    }

    // copy the substring into the newly allocated memory
    strncpy(result, str + pos, len);
    result[len] = '\0'; // Null-terminate the substring

    return result;
}

int64_t part1(char *);
int64_t part2(char *);

int64_t part1(char *line) {
    char first, last;
    for (int i = 0; line[i] != '\0'; i++) {
        if (isdigit(line[i])) {
            first = line[i];
            break;
        }
    }
    for (int i = strlen(line) - 1; i >= 0; i--) {
        if (isdigit(line[i])) {
            last = line[i];
            break;
        }
    }

    char str[3];
    int sprintfResult = snprintf(str, sizeof(str), "%c%c", first, last);
    if (sprintfResult >= 0 && sprintfResult < sizeof(str)) {
        char *endptr;
        long result = strtol(str, &endptr, 10);
        if (endptr == str) {
            fprintf(stderr, "ERROR: No valid digits were found\n");
            exit(EXIT_FAILURE);
        } else if (*endptr != '\0') {
            fprintf(stderr, "ERROR: Invalid character found: %c\n", *endptr);
            exit(EXIT_FAILURE);
        } else {
            return result;
        }
    } else {
        fprintf(stderr, "ERROR: File to concatinate first and last digit\n");
        exit(EXIT_FAILURE);
    }
    return -1;
}

int64_t part2(char *line) {
    lookup_table nums[9] = {{"one", '1'},   {"two", '2'},   {"three", '3'},
                            {"four", '4'},  {"five", '5'},  {"six", '6'},
                            {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};
    int32_t len = strlen(line);
    char first, last;
    int32_t firstIndex, lastIndex;
    firstIndex = len;
    lastIndex = -1;

    // first digit
    for (int32_t i = 0; i < len; i++) {
        if (isdigit(line[i])) {
            first = line[i];
            firstIndex = i;
            break;
        }
    }

    // first word
    uint8_t found = 0;
    for (int32_t j = 0; j < firstIndex; j++) {
        for (int32_t i = 0; i < 9; i++) {
            char *substring = substr(line, j, strlen(nums[i].word));
            if (j + strlen(nums[i].word) < strlen(line) &&
                !strcmp(substring, nums[i].word)) {
                if (j < firstIndex) {
                    firstIndex = j;
                    first = nums[i].digits;
                    found = 1;
                }
                free(substring);
                break;
            }
            free(substring);
        }
        if (found) {
            break;
        }
    }

    lastIndex = firstIndex;

    // last digit
    for (int32_t i = len - 1; i >= 0; --i) {
        if (isdigit(line[i])) {
            last = line[i];
            lastIndex = i;
            break;
        }
    }

    // last word
    found = 0;
    for (int32_t j = lastIndex + 1; j < len; j++) {
        for (int32_t i = 0; i < 9; i++) {
            char *substring = substr(line, j, strlen(nums[i].word));
            if (j + strlen(nums[i].word) < strlen(line) &&
                !strcmp(substring, nums[i].word)) {
                if (j > lastIndex) {
                    lastIndex = j;
                    last = nums[i].digits;
                    found = 1;
                }
                free(substring);
                break;
            }
            free(substring);
        }
    }

    char str[3];
    int sprintfResult = snprintf(str, sizeof(str), "%c%c", first, last);
    if (sprintfResult >= 0 && sprintfResult < sizeof(str)) {
        char *endptr;
        long result = strtol(str, &endptr, 10);
        if (endptr == str) {
            fprintf(stderr, "ERROR: No valid digits were found\n");
            exit(EXIT_FAILURE);
        } else if (*endptr != '\0') {
            fprintf(stderr, "ERROR: Invalid character found: %c\n", *endptr);
            exit(EXIT_FAILURE);
        } else {
            return result;
        }
    } else {
        fprintf(stderr, "ERROR: File to concatinate first and last digit\n");
        exit(EXIT_FAILURE);
    }

    return -1;
}

int32_t main(int32_t argc, char **argv) {

    char *fName = "./../input";
    char *testPart1 = "./../test.part1";
    char *testPart2 = "./../test.part2";

    int64_t result1, result2;
    result1 = result2 = 0;

    FILE *file = fopen(fName, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    char line[1024];

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    while (fgets(line, (size_t)sizeof(line), file) != NULL) {
        result1 += part1(line);
        result2 += part2(line);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    int64_t diff =
        1e9 * (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
    printf("Solution part1: %ld\n", result1);
    printf("Solution part2: %ld\n", result2);
    printf("Time Taken: %ldus\n", (int64_t)(diff / 1e3));

    fclose(file);
    return 0;
}
