#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_replace_target(const char *start, const char *end) {
    return (end - start > 2); // At least 2 characters between underscores
}

void replace_substring(char *str, const char *word) {
    char buffer[1000];
    char *insert_point = buffer;
    char *tmp = str;
    size_t word_len = strlen(word);

    while (*tmp) {
        if (*tmp == '_' && strchr(tmp + 1, '_')) {
            char *end = strchr(tmp + 1, '_');
            if (is_valid_replace_target(tmp, end)) {
                memcpy(insert_point, word, word_len);
                insert_point += word_len;
                tmp = end + 1;
                continue;
            }
        }
        *insert_point++ = *tmp++;
    }
    *insert_point = '\0';

    strcpy(str, buffer);
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char word[] = "cat";

    while ((read = getline(&line, &len, fp)) != -1) {
        replace_substring(line, word);
        printf("%s", line);
    }

    // free(line); // Release the memory allocated by getline
    fclose(fp);
    return 0;
}
