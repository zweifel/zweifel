

#include"read_arff.h"

void printDataset(double** dataset, int number_of_instances, int number_of_attributes)
{

	int i,j;

	printf("\nDataset:\n");

	for(i=0;i<number_of_instances;i++)
	{
		for(j=0;j<number_of_attributes;j++)
		{
			printf("%.2f ",dataset[i][j]);
		}
		printf("\n");
	}

}

//Reads an ARFF file, 
//
//Note:
//	- Some ARFF has (for no reason) empty lines after the @DATA
//	to solve this, any DATA line with size < 3 is discarded (considered empty)
double** readARFF(const char* filename, int& number_of_instances, int& number_of_attributes, double** & uncertainty)
{
	FILE* fp;
	int max_size= 1024;
	char* buffer= (char*)malloc(sizeof(char)*max_size);
	char* type= (char*)malloc(sizeof(char)*max_size);
	int attribute_counter=0;
	arff_type_t* dataset_converter=NULL;
	double** dataset=NULL;
	int i;
	
	fp= fopen(filename,"r");

	while( !feof(fp) )
	{
		int last_position= ftell(fp);
		
		if(fgets(buffer, max_size, fp)!=NULL)
		{
			//remove comments
			//if(buffer[0]!='%')
			//{
				//printf("%s",buffer);
			//}

			//get all attributes
			if(!strncasecmp(buffer,"@ATTRIBUTE",10)) 
			{

				for( ; !strncasecmp(buffer,"@attribute",10) ; )
				{
					if(fgets(buffer, max_size, fp)!=NULL)
					{
						attribute_counter++;	
					}
					else
					{
						printf("ERROR: Abrupt end of file\n");
						exit(1);
					}
				}

				number_of_attributes=attribute_counter;

				//allocate space for the types
				dataset_converter=(arff_type_t*)malloc(sizeof(arff_type_t)*number_of_attributes);
				

				//rewind to the position before reading the attributes
				fseek(fp, (last_position), SEEK_SET);

				printf("ATTRIBUTES: %d\n",number_of_attributes);
				//set types
				for(i=0; i<number_of_attributes; i++)
				{
					//read the definition of the attribute
					//if(fscanf(fp,"%*s %*s %[^\n]",buffer)!=0)
					if(fscanf(fp,"%*s %[^\n]",buffer)!=0)
					{
						//printf("%s\n",buffer);

						//when attributes names have the symbol (') they might have spaces 
						//so parse the entire name inbetween the (')
						if(buffer[0]=='\'')
						{
							buffer=strtok(buffer,"'");
							buffer=strtok(NULL,"}");
							sscanf(buffer," %[^\n] ",buffer);
						}
						//otherwise, just exclude the useless attribute name :)
						else
						{
							sscanf(buffer,"%*s %[^\n] ",buffer);
						}

						
						//printf("%s\n",buffer);
						//exit(1);
						
						if(!strncasecmp(buffer,"real",4)||!strncasecmp(buffer,"numeric",7)||!strncasecmp(buffer,"integer",7))
						{
							//printf("real\n");
							dataset_converter[i].type= NUMERIC;

						}
						else if(buffer[0]=='{')
						{

							dataset_converter[i].type= NOMINAL;
							dataset_converter[i].nominal= (nominal_t*)malloc(sizeof(nominal_t));

							bool done=false;
							int counter=0;

							queue<string> nominal_queue;
							
							char* token= NULL;
							token= strtok(buffer,",");

							//printf("size of %d",sizeof(token));
							

							if(token==0)
							{
								done=true;
							}
							else
							{
								sscanf(token," { %s ",type);
								//token=trimWhiteSpaces(token);
								nominal_queue.push( string(type));
							//	printf("%s,",type);

							}

							while(!done)
							{
								//strtok(buffer,',');
								//sscanf("%[^\t\n],",)
								
								token= strtok(NULL,",");

								if(token==0)
								{
									done=true;
								}
								else
								{
									//printf("%s",token);

									sscanf(token," %[^}\n,] ",type);
									//token=trimWhiteSpaces(token);
									nominal_queue.push( string(type));

							//		printf("%s,",type);
								}
									
								counter++;
							}
							
							dataset_converter[i].nominal->size=(int*)malloc(sizeof(int)*nominal_queue.size());
							dataset_converter[i].nominal->names=(char**)malloc(sizeof(char*)*nominal_queue.size());
							dataset_converter[i].nominal->number_of_names=nominal_queue.size();

							int j=0;
							for( ; !nominal_queue.empty() ; )
							{
								//printf("%s",nominal_queue.front().c_str());
								dataset_converter[i].nominal->names[j]=(char*)malloc(sizeof(char)*nominal_queue.front().size()+1);
								dataset_converter[i].nominal->names[j]=strcpy(dataset_converter[i].nominal->names[j],nominal_queue.front().c_str());
								dataset_converter[i].nominal->size[j]=nominal_queue.front().size();

								nominal_queue.pop();
								j++;
							}
							
							
							//printf("\n");
							for(j=0 ; j<dataset_converter[i].nominal->number_of_names ; j++)
							{
								//printf("%s type %d attribute %d index %d\n", dataset_converter[i].nominal->names[j], dataset_converter[i].type, i, j);
								
							}
							//printf("nominal with %d names\n",counter);
						}
						else
						{
							if(buffer[0]=='?')
							{

							}
							else
							{
								printf("ERROR: Non-recognizable format of ATTRIBUTE: %s\n",buffer);
								exit(1);
							}
						}


					}
					else
					{
						printf("ERROR: attribute mal formatted\n");
						exit(1);
					}
				}
				

			}
				
			
			//get all instances (process data)
			if(!strncasecmp(buffer,"@DATA",5)) 
			{

				last_position= ftell(fp);


				int instance_counter=0;
					
				if(fgets(buffer, max_size, fp)==NULL)
				{
					printf("ERROR 1: Could not read any further, while reading the DATA\n");
					exit(1);
				}
				
				//count the number of instances
				for( ; !feof(fp) ; )
				{
					
					//printf("DATA %s strlen %d\n",buffer, strlen(buffer));

					//ignore comments (%)
					if(buffer[0]=='%')
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						
					}
					//ignore empty lines
					else if(strlen(buffer)<3)
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						
					}
					else
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						instance_counter++;	
					}
				}

				printf("instances %d\n",instance_counter);

				number_of_instances= instance_counter;
				
				//allocate space for the dataset
				dataset=(double**)malloc(sizeof(double*)*number_of_instances);
				uncertainty=(double**)malloc(sizeof(double*)*number_of_instances);
				
				int j;
				for(j=0;j<number_of_instances;j++)
				{
					dataset[j]=(double*)malloc(sizeof(double)*number_of_attributes);
					uncertainty[j]=(double*)malloc(sizeof(double)*number_of_attributes);
				}
				
				//rewind to the position before reading the data
				fseek(fp, (last_position), SEEK_SET);



				instance_counter=0;
				

				for(; instance_counter < number_of_instances ; instance_counter++)
				{
				
					//get the first line of DATA
					if(fgets(buffer, max_size, fp)==NULL)
					{
						printf("ERROR 4: Could not read any further, while reading the DATA\n");
						exit(1);
					}
					
					//ignore comments (%)
					if(buffer[0]=='%')
					{
						instance_counter--;
						continue;
					}
					//ignore empty lines
					else if(strlen(buffer)<3)
					{
						instance_counter--;
						continue;
					}

					
					//printf("DATA %s\n",buffer);
					
					bool done=false;
					char* token= NULL;
					int attribute_counter=0;

					token= strtok(buffer,",");

					

					//printf("size of %d",sizeof(token));
					if(token==NULL)
					{
						done=true;
					}
					else
					{
						//trim the token, in order to ignore spaces at the beginning and at the end
						sscanf(token," %s ",type);
						//token=trimWhiteSpaces(type);

						//converting the types of data into a float representation and 
						//storying them into the dataset array
						if(type[0]=='?')
						{
							//printf("?\n");
							dataset[instance_counter][attribute_counter]=0.0;
							uncertainty[instance_counter][attribute_counter]=0.0;

						}
						else
						{
							convertTypeAndStore(dataset_converter, dataset, type,instance_counter, attribute_counter);
							uncertainty[instance_counter][attribute_counter]=1.0;
						}
						
						//printf("%s - %f\n",type,dataset[instance_counter][attribute_counter]);


					}
					
					attribute_counter++;

					while(!done)
					{
						//strtok(buffer,',');
						//sscanf("%[^\t\n],",)
						
						token= strtok(NULL,",");

						if(token==NULL)
						{
							done=true;
						}
						else
						{
							//trim the token, in order to ignore spaces at the beginning and at the end
							sscanf(token," %s ",type);
							//token=trimWhiteSpaces(type);

							//converting the types of data into a float representation and 
							//storying them into the dataset array
							if(type[0]=='?')
							{
								//printf("?\n");
								dataset[instance_counter][attribute_counter]=0.0;
								uncertainty[instance_counter][attribute_counter]=0.0;
							}
							else
							{
								convertTypeAndStore(dataset_converter, dataset, type, instance_counter, attribute_counter);
								uncertainty[instance_counter][attribute_counter]=1.0;
							}
							//printf("%s - %f\n",type,dataset[instance_counter][attribute_counter]);
						}
							
						attribute_counter++;
					}

				}
	
				fclose(fp);
				free(type);
				free(dataset_converter);
				
				return dataset;

			}


		
		}

	}


	fclose(fp);

	free(buffer);
	free(type);
	free(dataset_converter);

	return dataset;
}

//Reads an ARFF file, 
//
//Know Problems:  
//	- Do not consider the unknow value (?), specially in nominal attributes
//
//Note:
//	- Some ARFF has (for no reason) empty lines after the @DATA
//	to solve this, any DATA line with size < 3 is discarded (considered empty)

double** readARFF(const char* filename, int& number_of_instances, int& number_of_attributes)
{
	FILE* fp;
	int max_size= 1024;
	char* buffer= (char*)malloc(sizeof(char)*max_size);
	char* type= (char*)malloc(sizeof(char)*max_size);
	int attribute_counter=0;
	arff_type_t* dataset_converter=NULL;
	double** dataset=NULL;
	int i;
	
	fp= fopen(filename,"r");

	while( !feof(fp) )
	{
		int last_position= ftell(fp);
		
		if(fgets(buffer, max_size, fp)!=NULL)
		{
			//remove comments
			//if(buffer[0]!='%')
			//{
				//printf("%s",buffer);
			//}

			//get all attributes
			if(!strncasecmp(buffer,"@ATTRIBUTE",10)) 
			{

				for( ; !strncasecmp(buffer,"@attribute",10) ; )
				{
					if(fgets(buffer, max_size, fp)!=NULL)
					{
						attribute_counter++;	
					}
					else
					{
						printf("ERROR: Abrupt end of file\n");
						exit(1);
					}
				}

				number_of_attributes=attribute_counter;

				//allocate space for the types
				dataset_converter=(arff_type_t*)malloc(sizeof(arff_type_t)*number_of_attributes);
				

				//rewind to the position before reading the attributes
				fseek(fp, (last_position), SEEK_SET);

				printf("ATTRIBUTES: %d\n",number_of_attributes);
				//set types
				for(i=0; i<number_of_attributes; i++)
				{
					//read the definition of the attribute
					//if(fscanf(fp,"%*s %*s %[^\n]",buffer)!=0)
					if(fscanf(fp,"%*s %[^\n]",buffer)!=0)
					{
						//printf("%s\n",buffer);

						//when attributes names have the symbol (') they might have spaces 
						//so parse the entire name inbetween the (')
						if(buffer[0]=='\'')
						{
							buffer=strtok(buffer,"'");
							buffer=strtok(NULL,"}");
							sscanf(buffer," %[^\n] ",buffer);
						}
						//otherwise, just exclude the useless attribute name :)
						else
						{
							sscanf(buffer,"%*s %[^\n] ",buffer);
						}

						
						//printf("%s\n",buffer);
						//exit(1);
						
						if(!strncasecmp(buffer,"real",4)||!strncasecmp(buffer,"numeric",7)||!strncasecmp(buffer,"integer",7))
						{
							//printf("real\n");
							dataset_converter[i].type= NUMERIC;

						}
						else if(buffer[0]=='{')
						{

							dataset_converter[i].type= NOMINAL;
							dataset_converter[i].nominal= (nominal_t*)malloc(sizeof(nominal_t));

							bool done=false;
							int counter=0;

							queue<string> nominal_queue;
							
							char* token= NULL;
							token= strtok(buffer,",");

							//printf("size of %d",sizeof(token));
							

							if(token==0)
							{
								done=true;
							}
							else
							{
								sscanf(token," { %s ",type);
								//token=trimWhiteSpaces(token);
								nominal_queue.push( string(type));
							//	printf("%s,",type);

							}

							while(!done)
							{
								//strtok(buffer,',');
								//sscanf("%[^\t\n],",)
								
								token= strtok(NULL,",");

								if(token==0)
								{
									done=true;
								}
								else
								{
									//printf("%s",token);

									sscanf(token," %[^}\n,] ",type);
									//token=trimWhiteSpaces(token);
									nominal_queue.push( string(type));

							//		printf("%s,",type);
								}
									
								counter++;
							}
							
							dataset_converter[i].nominal->size=(int*)malloc(sizeof(int)*nominal_queue.size());
							dataset_converter[i].nominal->names=(char**)malloc(sizeof(char*)*nominal_queue.size());
							dataset_converter[i].nominal->number_of_names=nominal_queue.size();

							int j=0;
							for( ; !nominal_queue.empty() ; )
							{
								//printf("%s",nominal_queue.front().c_str());
								dataset_converter[i].nominal->names[j]=(char*)malloc(sizeof(char)*nominal_queue.front().size()+1);
								dataset_converter[i].nominal->names[j]=strcpy(dataset_converter[i].nominal->names[j],nominal_queue.front().c_str());
								dataset_converter[i].nominal->size[j]=nominal_queue.front().size();

								nominal_queue.pop();
								j++;
							}
							
							
							//printf("\n");
							for(j=0 ; j<dataset_converter[i].nominal->number_of_names ; j++)
							{
								//printf("%s type %d attribute %d index %d\n", dataset_converter[i].nominal->names[j], dataset_converter[i].type, i, j);
								
							}
							//printf("nominal with %d names\n",counter);
						}
						else
						{
							printf("ERROR: Non-recognizable format of ATTRIBUTE: %s\n",buffer);
							exit(1);
						}


					}
					else
					{
						printf("ERROR: attribute mal formatted\n");
						exit(1);
					}
				}
				

			}
				
			
			//get all instances (process data)
			if(!strncasecmp(buffer,"@DATA",5)) 
			{

				last_position= ftell(fp);


				int instance_counter=0;
					
				if(fgets(buffer, max_size, fp)==NULL)
				{
					printf("ERROR 1: Could not read any further, while reading the DATA\n");
					exit(1);
				}
				
				//count the number of instances
				for( ; !feof(fp) ; )
				{
					
					//printf("DATA %s strlen %d\n",buffer, strlen(buffer));

					//ignore comments (%)
					if(buffer[0]=='%')
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						
					}
					//ignore empty lines
					else if(strlen(buffer)<3)
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						
					}
					else
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						instance_counter++;	
					}
				}

				printf("instances %d\n",instance_counter);

				number_of_instances= instance_counter;
				
				//allocate space for the dataset
				dataset=(double**)malloc(sizeof(double*)*number_of_instances);
				
				int j;
				for(j=0;j<number_of_instances;j++)
				{
					dataset[j]=(double*)malloc(sizeof(double)*number_of_attributes);
				}
				
				//rewind to the position before reading the data
				fseek(fp, (last_position), SEEK_SET);



				instance_counter=0;
				

				for(; instance_counter < number_of_instances ; instance_counter++)
				{
				
					//get the first line of DATA
					if(fgets(buffer, max_size, fp)==NULL)
					{
						printf("ERROR 4: Could not read any further, while reading the DATA\n");
						exit(1);
					}
					
					//ignore comments (%)
					if(buffer[0]=='%')
					{
						instance_counter--;
						continue;
					}
					//ignore empty lines
					else if(strlen(buffer)<3)
					{
						instance_counter--;
						continue;
					}

					
					//printf("DATA %s\n",buffer);
					
					bool done=false;
					char* token= NULL;
					int attribute_counter=0;

					token= strtok(buffer,",");

					

					//printf("size of %d",sizeof(token));
					if(token==NULL)
					{
						done=true;
					}
					else
					{
						//trim the token, in order to ignore spaces at the beginning and at the end
						sscanf(token," %s ",type);
						//token=trimWhiteSpaces(type);

						//converting the types of data into a float representation and 
						//storying them into the dataset array
						convertTypeAndStore(dataset_converter, dataset, type,instance_counter, attribute_counter);
						
						
						//printf("%s - %f\n",type,dataset[instance_counter][attribute_counter]);


					}
					
					attribute_counter++;

					while(!done)
					{
						//strtok(buffer,',');
						//sscanf("%[^\t\n],",)
						
						token= strtok(NULL,",");

						if(token==NULL)
						{
							done=true;
						}
						else
						{
							//trim the token, in order to ignore spaces at the beginning and at the end
							sscanf(token," %s ",type);
							//token=trimWhiteSpaces(type);

							//converting the types of data into a float representation and 
							//storying them into the dataset array
							convertTypeAndStore(dataset_converter, dataset, type, instance_counter, attribute_counter);
							
							//printf("%s - %f\n",type,dataset[instance_counter][attribute_counter]);
						}
							
						attribute_counter++;
					}

				}
	
				fclose(fp);
				free(type);
				free(dataset_converter);
				
				return dataset;

			}


		
		}

	}


	fclose(fp);

	free(buffer);
	free(type);
	free(dataset_converter);

	return dataset;
}

//Reads an ARFF file, 
//
//Know Problems:  
//	- Do not consider the unknow value (?), specially in nominal attributes
//
//Note:
//	- Some ARFF has (for no reason) empty lines after the @DATA
//	to solve this, any DATA line with size < 3 is discarded (considered empty)

double** readVerboseARFF(const char* filename, int& number_of_instances, int& number_of_attributes)
{
	FILE* fp;
	int max_size= 1024;
	char* buffer= (char*)malloc(sizeof(char)*max_size);
	char* type= (char*)malloc(sizeof(char)*max_size);
	int attribute_counter=0;
	arff_type_t* dataset_converter=NULL;
	double** dataset=NULL;
	int i;
	
	fp= fopen(filename,"r");

	while( !feof(fp) )
	{
		int last_position= ftell(fp);
		
		if(fgets(buffer, max_size, fp)!=NULL)
		{
			//remove comments
			//if(buffer[0]!='%')
			//{
				//printf("%s",buffer);
			//}

			//get all attributes
			if(!strncasecmp(buffer,"@ATTRIBUTE",10)) 
			{

				for( ; !strncasecmp(buffer,"@attribute",10) ; )
				{
					if(fgets(buffer, max_size, fp)!=NULL)
					{
						attribute_counter++;	
					}
					else
					{
						printf("ERROR: Abrupt end of file\n");
						exit(1);
					}
				}

				number_of_attributes=attribute_counter;

				//allocate space for the types
				dataset_converter=(arff_type_t*)malloc(sizeof(arff_type_t)*number_of_attributes);
				

				//rewind to the position before reading the attributes
				fseek(fp, (last_position), SEEK_SET);

				printf("ATTRIBUTES: %d\n",number_of_attributes);
				//set types
				for(i=0; i<number_of_attributes; i++)
				{
					//read the definition of the attribute
					//if(fscanf(fp,"%*s %*s %[^\n]",buffer)!=0)
					if(fscanf(fp,"%*s %[^\n]",buffer)!=0)
					{
						//printf("%s\n",buffer);

						//when attributes names have the symbol (') they might have spaces 
						//so parse the entire name inbetween the (')
						if(buffer[0]=='\'')
						{
							buffer=strtok(buffer,"'");
							buffer=strtok(NULL,"}");
							sscanf(buffer," %[^\n] ",buffer);
						}
						//otherwise, just exclude the useless attribute name :)
						else
						{
							sscanf(buffer,"%*s %[^\n] ",buffer);
						}

						
						//printf("%s\n",buffer);
						//exit(1);
						
						if(!strncasecmp(buffer,"real",4)||!strncasecmp(buffer,"numeric",7)||!strncasecmp(buffer,"integer",7))
						{
							//printf("real\n");
							dataset_converter[i].type= NUMERIC;

						}
						else if(buffer[0]=='{')
						{

							dataset_converter[i].type= NOMINAL;
							dataset_converter[i].nominal= (nominal_t*)malloc(sizeof(nominal_t));

							bool done=false;
							int counter=0;

							queue<string> nominal_queue;
							
							char* token= NULL;
							token= strtok(buffer,",");

							//printf("size of %d",sizeof(token));
							

							if(token==0)
							{
								done=true;
							}
							else
							{
								sscanf(token," { %s ",type);
								//token=trimWhiteSpaces(token);
								nominal_queue.push( string(type));
							//	printf("%s,",type);

							}

							while(!done)
							{
								//strtok(buffer,',');
								//sscanf("%[^\t\n],",)
								
								token= strtok(NULL,",");

								if(token==0)
								{
									done=true;
								}
								else
								{
									//printf("%s",token);

									sscanf(token," %[^}\n,] ",type);
									//token=trimWhiteSpaces(token);
									nominal_queue.push( string(type));

							//		printf("%s,",type);
								}
									
								counter++;
							}
							
							dataset_converter[i].nominal->size=(int*)malloc(sizeof(int)*nominal_queue.size());
							dataset_converter[i].nominal->names=(char**)malloc(sizeof(char*)*nominal_queue.size());
							dataset_converter[i].nominal->number_of_names=nominal_queue.size();

							int j=0;
							for( ; !nominal_queue.empty() ; )
							{
								//printf("%s",nominal_queue.front().c_str());
								dataset_converter[i].nominal->names[j]=(char*)malloc(sizeof(char)*nominal_queue.front().size()+1);
								dataset_converter[i].nominal->names[j]=strcpy(dataset_converter[i].nominal->names[j],nominal_queue.front().c_str());
								dataset_converter[i].nominal->size[j]=nominal_queue.front().size();

								nominal_queue.pop();
								j++;
							}
							
							
							printf("\n");
							for(j=0 ; j<dataset_converter[i].nominal->number_of_names ; j++)
							{
								printf("%s type %d attribute %d index %d\n", dataset_converter[i].nominal->names[j], dataset_converter[i].type, i, j);
								
							}
							printf("nominal with %d names\n",counter);
						}
						else
						{
							printf("ERROR: Non-recognizable format of ATTRIBUTE: %s\n",buffer);
							exit(1);
						}


					}
					else
					{
						printf("ERROR: attribute mal formatted\n");
						exit(1);
					}
				}
				
				printf("ATTRIBUTES\n");
		
				//printing the types
				int j;
				for(j=0;j<number_of_attributes;j++)
				{
					printf("type %d  %d\n",j, dataset_converter[j].type);
				}

			}
				
			
			//get all instances (process data)
			if(!strncasecmp(buffer,"@DATA",5)) 
			{

				last_position= ftell(fp);


				int instance_counter=0;
					
				if(fgets(buffer, max_size, fp)==NULL)
				{
					printf("ERROR 1: Could not read any further, while reading the DATA\n");
					exit(1);
				}
				
				//count the number of instances
				for( ; !feof(fp) ; )
				{
					
					//printf("DATA %s strlen %d\n",buffer, strlen(buffer));

					//ignore comments (%)
					if(buffer[0]=='%')
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						
					}
					//ignore empty lines
					else if(strlen(buffer)<3)
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						
					}
					else
					{
						//this time we do not check for the EOF in the return of fgets
						//because we will surely get the EOF by the feof() directly above
						//And, we just want to count the instances; 
						//so a EOF is not anything abrupt here, it is indeed expected!
						fgets(buffer, max_size, fp);
						instance_counter++;	
					}
				}

				printf("instances %d\n",instance_counter);

				number_of_instances= instance_counter;
				
				//allocate space for the dataset
				dataset=(double**)malloc(sizeof(double*)*number_of_instances);
				
				int j;
				for(j=0;j<number_of_instances;j++)
				{
					dataset[j]=(double*)malloc(sizeof(double)*number_of_attributes);
				}
				
				//rewind to the position before reading the data
				fseek(fp, (last_position), SEEK_SET);



				instance_counter=0;
				

				for(; instance_counter < number_of_instances ; instance_counter++)
				{
				
					//get the first line of DATA
					if(fgets(buffer, max_size, fp)==NULL)
					{
						printf("ERROR 4: Could not read any further, while reading the DATA\n");
						exit(1);
					}
					
					//ignore comments (%)
					if(buffer[0]=='%')
					{
						instance_counter--;
						continue;
					}
					//ignore empty lines
					else if(strlen(buffer)<3)
					{
						instance_counter--;
						continue;
					}

					
					//printf("DATA %s\n",buffer);
					
					bool done=false;
					char* token= NULL;
					int attribute_counter=0;

					token= strtok(buffer,",");

					

					//printf("size of %d",sizeof(token));
					if(token==NULL)
					{
						done=true;
					}
					else
					{
						//trim the token, in order to ignore spaces at the beginning and at the end
						sscanf(token," %s ",type);
						//token=trimWhiteSpaces(type);

						//converting the types of data into a float representation and 
						//storying them into the dataset array
						convertTypeAndStore(dataset_converter, dataset, type,instance_counter, attribute_counter);
						
						
						//printf("%s - %f\n",type,dataset[instance_counter][attribute_counter]);


					}
					
					attribute_counter++;

					while(!done)
					{
						//strtok(buffer,',');
						//sscanf("%[^\t\n],",)
						
						token= strtok(NULL,",");

						if(token==NULL)
						{
							done=true;
						}
						else
						{
							//trim the token, in order to ignore spaces at the beginning and at the end
							sscanf(token," %s ",type);
							//token=trimWhiteSpaces(type);

							//converting the types of data into a float representation and 
							//storying them into the dataset array
							convertTypeAndStore(dataset_converter, dataset, type, instance_counter, attribute_counter);
							
							//printf("%s - %f\n",type,dataset[instance_counter][attribute_counter]);
						}
							
						attribute_counter++;
					}

				}
	
				fclose(fp);
				free(type);
				free(dataset_converter);
				
				return dataset;

			}


		
		}

	}


	fclose(fp);

	free(buffer);
	free(type);
	free(dataset_converter);

	return dataset;
}

void convertTypeAndStore(arff_type_t* dataset_converter, double** dataset, const char* type, int instance_counter, int attribute_counter)
{
	switch(dataset_converter[attribute_counter].type)
	{
		case NUMERIC:
		{
			dataset[instance_counter][attribute_counter]= strtod(type,NULL);
		}
		break;

		case NOMINAL:
		{
			bool found=false;
			int j=0;

			nominal_t* nominal_tmp= dataset_converter[attribute_counter].nominal;

			for(; j < nominal_tmp->number_of_names ; j++)
			{
				//printf("type %s %s\n",type,nominal_tmp->names[j]);

				if(!strncmp(type,nominal_tmp->names[j],nominal_tmp->size[j]))
				{
					found=true;
					break;
				}
			}

			if(!found)
			{
				printf("ERROR: Instance %d with an unrecognizable NOMINAL attribute %d:\n %s\n",instance_counter,attribute_counter, type);
				exit(1);
			}

			dataset[instance_counter][attribute_counter]= (double) j;
		}
		break;
	}
			
}

// Used from the site: 
// http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
char* trimWhiteSpaces(char* str)
{
	char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if(*str == 0)  // All spaces?
	return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}
