#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *notes[20] = {0};
size_t notes_size = 0;

void add_note() {

  if (notes_size == 20) {
    fprintf(stderr, "No more than 10 notes\n");
    return;
  }

  fprintf(stderr, "Note size>> ");
  unsigned int size = 0;
  scanf("%u", &size);
  while (fgetc(stdin) != '\n')
    ;

  if (size < 1 || size > 100) {
    fprintf(stderr, "size should be > 0 and <= 100 \n");
    return;
  }

  char *note = calloc(1, size);
  fprintf(stderr, "Note content(%u)>> ", size);
  fgets(note, size, stdin);
  fprintf(stderr, "Address -> %p\n", note);

  notes[notes_size++] = note;
}

void delete_note() {
  fprintf(stderr, "Note index>> ");
  unsigned int idx = 0;
  scanf("%u", &idx);

  if (idx > notes_size - 1) {
    return;
  }

  free(notes[idx]);
}

void list_notes() {
  printf("----- Notes -----\n");
  for (unsigned int i = 0; i < notes_size; i++) {
    printf("\%u -> %s\n", i, notes[i]);
  }
  fprintf(stderr, "\n");
}

void print_flag(char *flag, size_t *target) {
  fprintf(stderr, "Checking if %p 's 3rd element is 0x1337\n", target);
  if (target[2] != 0x1337) {
    fprintf(stderr, "Flag is only for h4xors\n");
    return;
  }

  fprintf(stderr, "%s\n", flag);
}

void menu() {
  fprintf(
      stderr,
      "\n1 - Add note\n2 - List notes\n3 - Delete note\n4 - Print Flag\n5 - "
      "Exit\n>> ");
}

int main() {
  setbuf(stdout, NULL);
  size_t target[3] = {0, 32, 0x31337};

  /* Read the flag */
  char flag[64] = {0};
  FILE *fptr;
  fptr = fopen("flag.txt", "r");
  fgets(flag, 63, fptr);
  fclose(fptr);
  /* ============= */

  unsigned int choice = 0;

  while (1) {
    menu();
    scanf("%u", &choice);

    switch (choice) {
    case 1:
      add_note();
      break;
    case 2:
      list_notes();
      break;
    case 3:
      delete_note();
      break;
    case 4:
      print_flag(flag, target);
      break;
    case 5:
      return 0;
    default:
      continue;
    }
  }

  return 0;
}
