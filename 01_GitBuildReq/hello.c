#include <stdio.h>
#include <stdlib.h>

#define ch_size sizeof(char)

int main(){

    char c;
    int max_len = 64, cur_len = 0;
    char *str = (char*) malloc(max_len * ch_size);

    while ((c = getchar()) != EOF && c != '\n') {
        str[cur_len] = c;
        cur_len++;

        if (cur_len >= max_len) {
            max_len += 64;
            str = (char*) realloc(str, max_len * ch_size);
        }
    }

    printf("Hello, %s!\n", str);
    free(str);

    return 0;
}