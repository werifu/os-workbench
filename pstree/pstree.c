#include <stdio.h>
#include <assert.h>

#define FINISHED -2
#define ERROR -1
#define TRUE 1
#define FALSE 0

enum Option {
  SHOW_PIDS,
  NUMERIC_SORT,
  VERSION,
};



/**
 * @brief parse the opts.
 * 
 * @param argc argc in function main's params
 * @param argv argv in function main's params
 * @param buf the option value buffer, nothing changed if not exists.
 * @return the (type: enum Option) of the next option, -1 error and -2 finished.
 */
int next_opt(int argc, char *argv[], const char* buf) {
  static int cur_arg = 0;
  if (cur_arg < argc) {
    assert(argv[cur_arg]);
    printf("argv[%d] = %s\n", cur_arg, argv[cur_arg]);
    cur_arg++;
    return TRUE;
  }
  return FINISHED;
}

int main(int argc, char *argv[]) {
  char buf[200];
  int type = next_opt(argc, argv, buf);
  while (type != FINISHED) {
    
    type = next_opt(argc, argv, buf);
  }
  assert(!argv[argc]);
  return 0;
}
