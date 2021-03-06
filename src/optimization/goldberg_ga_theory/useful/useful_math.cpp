
#include"useful_math.h"

//return the entropy of a set of variables in a set of samples
//an array of indices forming a variable set is passed as parameter
//and the size of the array variable stored in variable_size
//
//For example, if you want to know the entropy of a unique variable you can set variable_size=1
//and pass in the variable parameter the index of the variable
//
//Note that the entropy of one variable is a number between 0 (minimum uncertainty)
//and 1 (maximum uncertainty). And that the number of a set of variables with size n
//will be 0 (minimum uncertainty) and n (maximum uncertainty)
float entropy(int *variable, int variable_size, int** sample, int sample_size)
{
	int i,j,k;

	float cpc=0;
	float log2= 1/log(2);

	//compute the probability of each setting present in the best_sample
	for(i=0;i<sample_size;i++)
	{
		//if the building block setting was already processed before, 
		//we should disconsider it
		bool repeated_setting=false;
	
		//check if this setting was not already computed
		for(j=0;j<i && repeated_setting==false;j++)
		{

			//consider equal
			repeated_setting=true;

			//check if it is equal
			for(k=0;k<variable_size;k++)
			{
				if(sample[i][variable[k]]!=sample[j][variable[k]])
				{
					repeated_setting=false;
					break;
				}
			}
	

		}
			
		//stop this computation if we have already computed the setting
		if(repeated_setting==true)
		{
			continue;
		}

		int counter=1;
		
		//compute probability of this BB setting
		for(j=(i+1);j<sample_size;j++)
		{
			//consider equal
			repeated_setting=true;

			//check if it is equal
			for(k=0;k<variable_size;k++)
			{
				if(sample[i][variable[k]]!=sample[j][variable[k]])
				{
					repeated_setting=false;
					break;
				}
			}

			if(repeated_setting==true)
			{
				counter++;
			}
						
		}

		float probability= (float)counter/(float)sample_size;

		//printf("prob %f\n", probability);
		cpc+= - probability*log(probability)*log2;

	}

	return cpc;
	
}
