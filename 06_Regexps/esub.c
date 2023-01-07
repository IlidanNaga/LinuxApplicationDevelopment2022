#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile_or_exit(regex_t *preg, const char *regex) {
  int cflags = 0 | REG_EXTENDED;
  char errbuf[128];

  int regcomp_error = regcomp(preg, regex, cflags);
  if (regcomp_error) {
    regerror(regcomp_error, preg, errbuf, sizeof(errbuf));
    fprintf(stderr, "Bad regex: %s\n", errbuf);

    exit(1);
  }
}

void print_usage(char *argv[]) {
  printf("Usage: %s REGEXP SUBSTITUTION STRING\n", argv[0]);
}

char *replace_match(const char *source, const char *subst,
                    const regmatch_t match) {
  int subst_len = strlen(subst);
  int source_end_len = strlen(source) - match.rm_eo;

  int res_len = 0;
  res_len += match.rm_so;
  res_len += subst_len;
  res_len += source_end_len;

  char *res = (char *)malloc(sizeof(char) * res_len + 1);
  res[res_len] = '\0';
  char *cur = res;

  memcpy(cur, source, sizeof(char) * match.rm_so);
  cur += match.rm_so;
  memcpy(cur, subst, sizeof(char) * subst_len);
  cur += subst_len;
  memcpy(cur, source + match.rm_eo, sizeof(char) * source_end_len);

  return res;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    print_usage(argv);
    exit(1);
  }

  regex_t preg;
  compile_or_exit(&preg, argv[1]);

  int nmatch = 1;
  regmatch_t pmatch[1];
  int eflags = 0;

  int reti = regexec(&preg, argv[3], nmatch, pmatch, eflags);
  if (!reti) {
    char *res = replace_match(argv[3], argv[2], pmatch[0]);
    printf("%s\n", res);
    free(res);
    regfree(&preg);
  } else if (reti == REG_NOMATCH) {
    printf("%s\n", argv[3]);
    regfree(&preg);
  } else {
    char errbuf[128];
    regerror(reti, &preg, errbuf, sizeof(errbuf));
    fprintf(stderr, "Regex match failed: %s\n", errbuf);
    regfree(&preg);
    exit(1);
  }

  return 0;
}
