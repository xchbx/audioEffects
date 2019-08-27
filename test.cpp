#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "effects.h"

using namespace effects;

int main()
{
    Volume testvol;
    float level = 0.0;
	int16_t data[160];
    for(int i = 1;i<=200;i+=10)
    {
        level = i/100.0;
        testvol.SetLevel(level);
		printf("SetLevel = %6f, i = %d,GetLevel = %6f\r\n",level,i,testvol.GetLevel());
		FILE* fin = fopen("./input.pcm", "rb");
		if (NULL == fin)
		{
			printf("fopen input.pcm failed\n");
			continue;
		}
		
		char fname[64];
		snprintf(fname,64,"./output_%f.pcm",level);
		FILE* fout = fopen(fname, "wb");
		if (NULL == fout)
		{
			printf("fopen %s failed\n",fname);
			continue;
		}
		
		while(1)
		{
			int i = 0;
			int readlen;
			if ((readlen = fread(data, sizeof(short), 160, fin) )!= 160)
			{
				printf("process all data, exiting...\n");
				break;
			}else{
				//printf("readlen = %d\r\n",readlen);
			}

			testvol.Process(data,160);
			fwrite(data, sizeof(short), 160, fout);
		}
		fclose(fin);
		fclose(fout);
		usleep(10*1000*1000);
		
        
    }
}
