#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct range {
  int start;
  int stop;
  int step;

  int _cur;
  bool _finished;
};
typedef struct range range;

void range_init(range *r) {
  r->_cur = r->start;
  r->_finished = false;
};

bool range_run(range *r) { return r->_cur <= r->stop; };
void range_next(range *r) { r->_cur += r->step; };
int range_get(range *r) { return r->_cur; };

bool argparse(int argc, char *argv[], int *start, int *stop, int *step) {
  if ((argc < 2) || (argc > 4)) {
    return false;
  }

  int _start = 0;
  int _step = 1;
  int _stop;

  if (argc == 2) {
    _stop = atoi(argv[1]);
  }
  if (argc == 3) {
    _start = atoi(argv[1]);
    _stop = atoi(argv[2]);
  }
  if (argc == 4) {
    _start = atoi(argv[1]);
    _stop = atoi(argv[2]);
    _step = atoi(argv[3]);
  }

  if ((_step < 0) || (_stop < _start)) {
    return false;
  }

  *start = _start;
  *stop = _stop;
  *step = _step;

  return true;
};

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("You have to pass different number of parameters Program behaviour "
           "in different cases would be:\n");
    printf("One parameter N : returns sequence [0, 1, 2, ..., N-1]\n");
    printf("Two parameters M, N : returns sequence [M, M+1, M+2, ..., N-1]\n");
    printf("Three parameters M, N, S : returns sequence [M, M+S, M+2S, ..., "
           "N-1]\n");
    return 0;
  }

  range I;

  if (!argparse(argc, argv, &I.start, &I.stop, &I.step)) {
    fprintf(stderr, "Bad range\n");
    return 1;
  };

  for (range_init(&I); range_run(&I); range_next(&I))
    printf("%d\n", range_get(&I));
  return 0;
}
