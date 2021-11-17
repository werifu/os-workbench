#include <stdio.h>
#include <assert.h>

#define FINISHED -2
#define ERROR -1
#define true 1
#define false 0
typedef int bool;

enum Option {
  SHOW_PIDS,
  NUMERIC_SORT,
  VERSION,

  // if the string cannot be parsed
  _UNKNOWN,
};

bool str_equal(const char* s1, const char* s2) {
  int i = 0;
  while (s1[i] && s2[i]) {
    if (s1[i] != s2[i]) return false;
    else i++;
  }
  // one has not finished.
  if (s1[i] || s2[i]) return false;
  return true;
}

enum Option parse_opt_type(char* arg) {
  if (str_equal(arg, "-p") || str_equal(arg, "--show-pids")) return SHOW_PIDS;
  if (str_equal(arg, "-n") || str_equal(arg, "--numeric-sort")) return NUMERIC_SORT;
  if (str_equal(arg, "-V") || str_equal(arg, "--version")) return VERSION;
  return _UNKNOWN;
}
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
    enum Option opt = parse_opt_type(argv[cur_arg]);
    switch (opt)
    {
    case SHOW_PIDS:
      printf("-p OR --show-pids detected\n");
      break;
    case NUMERIC_SORT:
      printf("-n OR --numeric-sort detected\n");
      break;
    case VERSION:
      printf("-V OR --version detected\n");
      break;
    case _UNKNOWN:
      printf("Unknown param detected\n");
      break;
    default:
      printf("You should have not see me...\n");
      break;
    }
    // printf("argv[%d] = %s\n", cur_arg, argv[cur_arg]);
    cur_arg++;
    return true;
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
