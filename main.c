
#include <stdio.h>



static HI_S32 detectWhiteBlockAlg(HI_CHAR * pbuff)
{
	#if 0
	int i2 = 0; 
	for(i2 = 0; i2 < 15*1920; i2++)
	{
		*(pbuff+i2) = 0;
	}
	return 0;
	#endif
	
	char val[3][3] = {
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1},
	};	
	char val1[3][3] = {
		{1, 2, 1},
		{0, 0, 0},
		{-1, -2, 1},
	};	
	short * buff = (short *)malloc(1080*1920*sizeof(short));	
	short * buff1 = (short *)malloc(1080*1920*sizeof(short));		
	if(!buff || !buff1)
	{
		printf("malloc err!\n");
		return -1;
	}
	
	HI_CHAR *pW = NULL;
	HI_S32 h = 0;
	HI_S32 i = 0, j = 0;
	



	for( i = 0; i < 1080; i++)
	{
		for( j = 0; j < 1920; j++)
		{
			if(j > 0 && i > 0)
			{
				*(buff + i*1920 + j) = *(pbuff+(i-1)*1920+(j-1))*val[0][0] + *(pbuff+(i-1)*1920+(j))*val[0][1] + *(pbuff+(i-1)*1920+(j+1))*val[0][2] +\
				*(pbuff+(i)*1920+(j-1))*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				*(pbuff+(i+1)*1920+(j-1))*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;				
			}
			
			else if(i <= 0 && j > 0)
			{
				*(buff + i*1920 + j) = 0*val[0][0] + 0*val[0][1] + 0*val[0][2] +\
				*(pbuff+(i)*1920+(j-1))*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				*(pbuff+(i+1)*1920+(j-1))*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;								
			}
			else if(i <= 0 && j <= 0)
			{
				*(buff + i*1920 + j) = 0*val[0][0] + 0*val[0][1] + 0*val[0][2] +\
				0*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				0*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;								
			}
			else if(i>0 && j <= 0)
			{
				*(buff + i*1920 + j)= 0*val[0][0] + *(pbuff+(i-1)*1920+(j))*val[0][1] + *(pbuff+(i-1)*1920+(j+1))*val[0][2] +\
				0*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				0*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;								
			}		
		}
	}
	memcpy(val, val1, sizeof(val));
	for( i = 0; i < 1080; i++)
	{
		for( j = 0; j < 1920; j++)
		{
			if(j > 0 && i > 0)
			{
				*(buff1 + i*1920 + j) = *(pbuff+(i-1)*1920+(j-1))*val[0][0] + *(pbuff+(i-1)*1920+(j))*val[0][1] + *(pbuff+(i-1)*1920+(j+1))*val[0][2] +\
				*(pbuff+(i)*1920+(j-1))*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				*(pbuff+(i+1)*1920+(j-1))*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;				
			}
			
			else if(i <= 0 && j > 0)
			{
				*(buff1 + i*1920 + j) = 0*val[0][0] + 0*val[0][1] + 0*val[0][2] +\
				*(pbuff+(i)*1920+(j-1))*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				*(pbuff+(i+1)*1920+(j-1))*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;								
			}
			else if(i <= 0 && j <= 0)
			{
				*(buff1 + i*1920 + j) = 0*val[0][0] + 0*val[0][1] + 0*val[0][2] +\
				0*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				0*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;								
			}
			else if(i>0 && j <= 0)
			{
				*(buff1 + i*1920 + j)= 0*val[0][0] + *(pbuff+(i-1)*1920+(j))*val[0][1] + *(pbuff+(i-1)*1920+(j+1))*val[0][2] +\
				0*val[1][0] + *(pbuff+(i)*1920+(j))*val[1][1] + *(pbuff+(i)*1920+(j+1))*val[1][2] + \
				0*val[2][0] + *(pbuff+(i+1)*1920+(j))*val[2][1] + *(pbuff+(i+1)*1920+(j+1))*val[2][2] ;								
			}			
		}
	}	

	for(int i = 0; i < 1080; i++)
	{
		for(int j = 0; j < 1920; j++)
		{
			#if 1
			unsigned short diff = 0;
			diff = (unsigned short)sqrt(pow((*(buff + i*1920 + j)),2) + pow((*(buff1 + i*1920 + j)),2));
			if(diff > 400)
			{
				*(pbuff + i*1920 + j) = 0;
			}
			else
			{
				*(pbuff + i*1920 + j) = 0xff;
			}
			#endif
			//*(pbuff + i*1920 + j) = 0xff;
			
		}			
		//printf("\n");
	}	

	free(buff);
	free(buff1);	
	
}


int main()
{
	
}

