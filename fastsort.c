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
    totalByes  = totalBytes + sizeof(r);
  }
  int numRecs;             // The total number of records in the input file.
  numRecs = totalBytes / 100;

 
  printf("Filesize: %d, total records = %d\n",totalBytes,numRecs);

  printf("If this works, it's the last key: %d\n",r.key); // WHAT YOU NEED TO DO: Figure out how 'r' variable works. I'm pretty sure that's where the records are being read into. From there
                                                      // You need to be able to dynamically allocate space ( malloc? ) and get the records into there. Each record is 100 bytes. From there, gotta find a way
                                                      // to check the first 4 bytes of each, which has the key. Sort by that. Try something like r[] next time you try this!!!!
  rec_t *records;

  records = (struct rec_t *)malloc(total);

  for(int i = 0; i<numRecs; i+1){
    //fill here
    printf("no");



  }


 
  (void) close(fd);  

  return 0;
}








