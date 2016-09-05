#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"

#define RECORD_SIZE (100)   // Each rec_t is 100 bytes.

int compare(const void* a, const void* b) 
{
    // compare function for qsort()
    int one = (*(rec_t *)a).key;
    int two = (*(rec_t *)b).key;
    return (one-two);
}  

int usage()
{
    fprintf(stderr, "Usage: fastsort -i inputfile -o outputfile\n");
    exit(1);
}


int main(int argc, char *argv[]) 
{
    char *inFile;
    char *outFile;  

    int c;
    opterr = 0;

    if(argc != 4){
      usage();  
    }

    while ((c = getopt(argc, argv, "i:o:")) != -1) {
        // code based off of the dump.c provided!
        switch (c) {
            case 'i':
                inFile = strdup(optarg);
                break;
            case 'o':
                outFile = strdup(optarg); 
                break;
            default:
                usage();
        }
    }
  
    int fd = open(inFile, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Cannot open file %s\n", inFile);
        exit(1);
    }
 
    int totalBytes; // the total number of bytes in the record
    rec_t r;
    while (1) {
        // reads in all of the records
        int rc;
        rc = read(fd, &r, sizeof(rec_t)); 
        if (rc == 0)
             break;
        if (rc < 0) {
             perror("read");
             exit(1);
        }

        // gets the total bytes inputed, also used to find the number of records
        totalBytes  = totalBytes + sizeof(r);

    }

    (void) close(fd);  
   
    int numRecs;
    // the total number of records in the input file.
    numRecs = totalBytes / RECORD_SIZE;

    // 
    rec_t *data;
    data = (rec_t *)malloc(totalBytes);
    if(data == NULL) {
        // if malloc fails:
        perror("memory");
        exit(1);
    } 

    // opening the file again. probably a better way to do this... couldn't figure out rewind()
    fd = open(inFile, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Cannot open file %s\n", inFile);
        exit(1);
    }

    for(int i = 0; i<numRecs; i++) {
        // putting the values into the array
        int rc;
        rc = read(fd, &r, sizeof(rec_t)); 
        data[i] = r;
    }  

    // thank you, standard libraries! sort in ascending order.
    qsort(data, numRecs, RECORD_SIZE, compare);

// Debugging print: prints each key, hopefully sorted.
//    for(int j = 0; j < numRecs; j++) {
//        printf("%d: Will this work?: %u\n",j,data[j].key);
//    }

    // Prepping the output file to be written to.
    fd = open(outFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
    if (fd < 0) {
        fprintf(stderr, "Error: Cannot open file %s\n", outFile);    
        exit(1);
    }

    for(int i = 0; i < numRecs; i++){
        // write each record
        int rc;
        rc = write(fd, &data[i], sizeof(rec_t));
        if (rc != sizeof(rec_t)) {
            perror("write");
            exit(1);
        }
    }

    (void) close(fd);  

    return 0;

}








