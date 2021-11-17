#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FINISHED -2
#define ERROR -1
#define true 1
#define false 0
#define MAX_ARG_LEN 256
#define MAX_ARG_NUM 20
typedef int bool;

#define TEST
#ifdef TEST
void test();
#endif


enum Option {
  SHOW_PIDS,
  NUMERIC_SORT,
  VERSION,

  // if the string cannot be parsed
  _UNKNOWN,
};

struct OptionValue {
  enum Option type;
  char value[MAX_ARG_LEN];
};
struct OptionValue opt_table[MAX_ARG_NUM];
int opt_num = 0;


/**
 * @return true if s1==s2
 * @return false if s1!=s2
 */
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

/**
 * @brief parse the type from a argument
 * 
 * @param arg one arg of argv
 * @return enum Option return the type of the input argument.
 */
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
 * @return the (type: enum Option) of the current option, -1 error and -2 finished.
 */
int next_opt(int argc, char *argv[], char* buf) {
  static int cur_arg = 1;
  if (cur_arg < argc) {
    assert(argv[cur_arg]);
    enum Option opt = parse_opt_type(argv[cur_arg]);
    // point cur_arg to next arg
    cur_arg++;
    switch (opt)
    {
    case SHOW_PIDS:
      printf("-p OR --show-pids detected\n");
      return SHOW_PIDS;
    case NUMERIC_SORT:
      printf("-n OR --numeric-sort detected\n");
      return NUMERIC_SORT;
    case VERSION:
      printf("-V OR --version detected\n");
      return VERSION;
    case _UNKNOWN:
      printf("Unknown argument '%s' detected\n", argv[cur_arg]);
      return _UNKNOWN;
    default:
      printf("You should have not see me...\n");
      return ERROR;
    }
  }
  return FINISHED;
}

/**
 * @brief parse all the opts and load values into array opt_table
 * 
 * @param argc 
 * @param argv 
 */
void parse_opts(int argc, char* argv[]) {
  char buf[MAX_ARG_LEN];
  int type = next_opt(argc, argv, buf);
  while (type != FINISHED) {
    type = next_opt(argc, argv, buf);
    if (type == _UNKNOWN) continue;
    opt_table[opt_num].type = type;
    strncpy(opt_table[opt_num].value, buf, MAX_ARG_LEN);
    opt_num++;
  }
  assert(!argv[argc]);
}

int main(int argc, char *argv[]) {
  #ifdef TEST
  test();
  #endif
  parse_opts();

  return 0;
}


#ifdef TEST
void test() {
  int argc = 5;
  char* argv[5] = {"a.out", "-p", "-V", "--numeric-sort", "-n"};
  char buf[MAX_ARG_LEN];
  parse_opts();
  assert(opt_num == 4);
  assert(opt_table[0].type == SHOW_PIDS);
}
#endif