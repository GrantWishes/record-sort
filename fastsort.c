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

  char *inFile = "/no/such/file";
  char *outFile = "no/such/file";  

  int c;
  opterr = 0;
  while ((c = getopt(argc, argv, "i:o:")) != -1) {
    switch (c) {
    case 'i':
      inFile = strdup(optarg);
      break;
    case 'o':
      outFile = argv[4];
      break;
    }
  }  
 printf("The input file is %s and the output file is %s\n", inFile, outFile);

  int fd = open(inFile, O_RDONLY);
  if (fd < 0) {
    perror("open");
    exit(1);

  }
  int total; // the total number of bytes in the record
  rec_t r;
  while (1) {
    int rc;
    rc = read(fd, &r, sizeof(rec_t)); // &r gives the pointer to the record list, r.
    if (rc == 0)
      break;
    if (rc < 0) {
      perror("read");
      exit(1);
        }
    total = total + sizeof(r);
  }
  
  printf("Filesize: %d\n",total);

  
  (void) close(fd);  

  return 0;
}








