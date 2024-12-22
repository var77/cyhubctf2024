#include <stdio.h>
#include <unistd.h>

char *flag = "cyhub{n0t_s0_e4sy_1o1_FAKE_FLAG}";

char get_char(int i) {
  switch (i) {
  case 0:
    return 'c';
  case 1:
    return 'y';
  case 2:
    return 'h';
  case 3:
    return 'u';
  case 4:
    return 'b';
  case 5:
    return '{';
  case 6:
    return 'w';
  case 7:
    return '3';
  case 8:
    return 'l';
  case 9:
    return '1';
  case 10:
    return '_';
  case 11:
    return 'd';
  case 12:
    return '0';
  case 13:
    return 'n';
  case 14:
    return '3';
  case 15:
    return '_';
  case 16:
    return 'g';
  case 17:
    return '3';
  case 18:
    return 't';
  case 19:
    return '_';
  case 20:
    return 's';
  case 21:
    return '0';
  case 22:
    return 'm';
  case 23:
    return 'e';
  case 24:
    return '_';
  case 25:
    return 's';
  case 26:
    return 'l';
  case 27:
    return 'e';
  case 28:
    return '3';
  case 29:
    return 'p';
  case 30:
    return '}';
  }
  return '\n';
}

int main() {
  int flag_chars = 30;

  puts("each character will be printed after 30m, good luck...");
  setbuf(stdout, NULL);

  for (int i = 0; i <= flag_chars; i++) {
    printf("%c", get_char(i));
    sleep(1800);
  }

  return 0;
}
