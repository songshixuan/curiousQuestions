#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <time.h>

#define BIGDATA_NUM 100000
#define FILE_NUM 100

// make big data file
char data_file[32] = "big_data.data";
// dataFile + number +".~tmp"
char dataFileName[32] = "dataFile";

int make_big_file()
{
        FILE *out = NULL;
        out = fopen(data_file, "wt");
        if(NULL == out) {
                printf("err of big_data file");
                return -1;
        }

        clock_t start,end;
        start = clock();

        for(int i=0;i<BIGDATA_NUM;i++) {
        //every second print number of data
        end = clock();
                if((end-start) > 100) {
                        printf("make %d of data",i);
                        start = end;
                }

                fprintf(out, "%d\n", (rand()%100) * (rand()%100) );
        }

        printf("make big data file secessed");

        fclose(out);
        return 1;
}

int hash_num(int data)
{
		if(data<0) {
				data = 1;
		}
        while(data >= FILE_NUM){
                data -= FILE_NUM;
        }
        return data;
}

int splitFile()
{
        FILE *in = NULL;
        in = fopen(data_file, "r");
        if(NULL == in) {
                printf("file is not exist");
                return -1;
        }

		clock_t start,end;
        start = clock();

        int data,add;
        FILE *tempFile[FILE_NUM];

		for(int i=0;i<FILE_NUM;i++) {
			tempFile[i] = NULL;
		}

        while(fscanf(in, "%d", &data) != EOF) {

                end = clock();
                if((end-start) > 100) {
                        printf("make %d of data",end-start);
                        start = end;
                }

                char hashfile[512];
                add = hash_num(data);

                if(tempFile[add] == NULL) {
                        sprintf(hashfile, "%s%d.~tmp", dataFileName, add);
                        tempFile[add] = fopen(hashfile, "wt");
                }

                fprintf(tempFile[add], "%d\n", data);
        }

        for(int i=0;i<FILE_NUM;i++) {
			if(tempFile[i] != NULL)
                fclose(tempFile[i]);
        }

		fclose(in);
        return 1;
}
int main(){
    make_big_file();
    splitFile();
    return 0;
}
