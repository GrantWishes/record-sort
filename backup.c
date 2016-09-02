#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"

int
main(int argc, char *argv[])
{

  char *inFIle = "/no/such/file";
  
  int c;
  opperr = 0;
  while ((c = getopt(argc, argv, "i:")) != -1) {
    switch (c) {
    case 'i':
      inFile = strdup(optarg);
      break;
    }
    
  printf("The input file is %s\n", inFile);

  }







}
