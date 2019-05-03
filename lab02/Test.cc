#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "MyString.h"

void test1() {
  const char *s1 = "Hello world";
  char * s2 = strdup(s1);
  MyString ms1(s2);
  *s2 = NULL;
  assert( !strcmp(ms1.cStr(),s1 ));
  printf("s1=\"%s\"\n", ms1.cStr());
  printf("Test 1 passed\n");
}

void test2() {
  const char *s1 = "Hello world";
  char * s2 = strdup(s1);
  MyString ms1(s2);
  MyString ms2(ms1);
  *s2 = NULL;
  assert( !strcmp(ms2.cStr(),s1 ));
  printf("s1=\"%s\"\n", ms2.cStr());
  printf("Test 2 passed\n");
}

void test3() {
  const char *s1 = "Hello world";
  char * s2 = strdup(s1);
  MyString ms1(s2);
  MyString ms2(ms1);
  *s2 = NULL;
  assert( ms2.length() == strlen(s1) );
  printf("len=%d\n", ms2.length());
  printf("Test 3 passed\n");
}

void test4() {
  MyString ms1;
  assert( ms1.cStr()[0] == 0 );
  printf("str=\"%s\"\n", ms1.cStr());
  printf("Test 4 passed\n");
}

void test5() {
  const char *s1 = "Hello world";
  char * s2 = strdup(s1);
  MyString ms1(s2);
  *s2 = NULL;
  MyString ms2;
  ms2 = ms1.substring(2,3);
  printf("substr(2,3) of \"%s\"=\"%s\"\n", ms1.cStr(), ms2.cStr());
  assert(!strcmp(ms2.cStr(),"llo"));
  printf("Test 5 passed\n");
}

void test6() {
  const char *s1 = "Hello world";
  char * s2 = strdup(s1);
  MyString ms1(s2);
  *s2 = NULL;
  MyString ms2;
  ms2 = ms1.substring(7,8);
  printf("substr(7,8) of \"%s\"=\"%s\"\n", ms1.cStr(), ms2.cStr());
  assert(!strcmp(ms2.cStr(),"orld")); 
  printf("Test 6 passed\n");
}

void test7() {
  const char *s1 = "Hello world";
  char * s2 = strdup(s1);
  MyString ms1(s2);
  *s2 = NULL;
  ms1.remove(2,3);
  printf("remove(2,3) of \"%s\"=\"%s\"\n", s1, ms1.cStr());
  assert(!strcmp(ms1.cStr(),"He world"));
  printf("Test 7 passed\n");
}

void test8() {
  MyString ms1("Hello");
  MyString ms2("world");
  MyString ms3("Hello");  
  assert(ms1!=ms2);
  assert(ms1==ms3);
  printf("Test 8 passed\n");
}

void usage() {fprintf(stderr, "TestMyString test1|test2|....|test11\n");}

int main( int argc, char ** argv) {
  if (argc == 1) {
    usage();
    exit(1);
  }

  if ( !strcmp(argv[1], "test1")) {
    test1();
  }
  else if ( !strcmp(argv[1], "test2")) {
    test2();
  }
  else if ( !strcmp(argv[1], "test3")) {
    test3();
  }
  else if ( !strcmp(argv[1], "test4")) {
    test4();
  }
  else if ( !strcmp(argv[1], "test5")) {
    test5();
  }
  else if ( !strcmp(argv[1], "test6")) {
    test6();
  }
  else if ( !strcmp(argv[1], "test7")) {
    test7();
  }
  else if ( !strcmp(argv[1], "test8")) {
    test8();
  }
  else {
    usage();
    exit(1);
  }
  exit(0);
}