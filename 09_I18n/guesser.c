#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

void print_rules() { printf(_("загадайте число 1..100\n")); }

bool ask_if_greater(const int mid) {
  printf(_("больше %d?\n"), mid);

  int ans = 0;
  do {
    printf("y/n: ");
    ans = getchar();
    getchar(); // eat \n
  } while ((ans != 'y') && (ans != 'n'));

  return ans == 'y';
}

void print_result(const int res) { printf(_("число %d\n"), res); }

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  bindtextdomain(GETTEXT_DOMAIN, LOCALE_PATH);
  textdomain(GETTEXT_DOMAIN);

  bool guessed = false;
  int guess = -1;
  print_rules();

  int upper = 100;
  int lower = 1;

  while (!guessed) {
    if (lower == upper) {
      guess = lower;
      guessed = true;
      continue;
    }

    int mid = (lower + upper) / 2;
    bool is_greater_than_mid = ask_if_greater(mid);

    if (is_greater_than_mid) {
      if (upper - lower == 1) {
        guessed = true;
        guess = upper;
        continue;
      }

      lower = mid;
      continue;
    }

    upper = mid;
  }

  print_result(guess);
  return 0;
}
