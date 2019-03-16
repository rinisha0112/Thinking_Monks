#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>


#define N_ATTR 7  //Number of Attributes as mentioned in dataset characteristics
#define N_CLASSES 2 // Number of classes as mentioned in dataset characteristics
#define N_SAMPLES 300 // No of training Examples
#define OP1 1	// Output value for class1
#define OP2 0	//Output value for class2
#define DATA_FILE "Training_Dataset.txt" // training dataset file
#define LEARNING_RATE 0.2 //value of learning parameter
#define THRESHOLD 0
#define NO_ITERATIONS 100
#define TEST_SAMPLES 256

FILE* file_pointer;
FILE* fptr;
int Activation_Function(float weighted_sum,float threshold)
{
  int ret_val;
  if (weighted_sum > threshold)
  {
  	ret_val=(OP1);
  }
  else
  {
  	ret_val=(OP2);
  }
  return(ret_val);
}

float Check_Output(FILE * ftp, float actual_output)
{
  float expected_output = 0;
  float error = 0;
  fscanf(ftp, "%f ", &expected_output);
  printf("\n");
  fprintf(fptr,"Desired Output: %f \n",expected_output);
  //printf("Expected Output: %.2f\n", expected_output);
  //printf("Actual Output: %.2f\n", actual_output);
  error = expected_output - actual_output;
  return error;
}
int main()
{
	int NO_OF_TRAINING_EXAMPLES=N_SAMPLES;
	int NO_OF_INPUTS=N_ATTR-N_CLASSES+1; //m=No of Attributes
	//int p=N_CLASSES-1; // Classified into p classes
	
	float input[NO_OF_INPUTS+1];
    float weight[NO_OF_INPUTS+1];
    float test_input[NO_OF_INPUTS+1];
    
    int i,count=0,iterations=NO_ITERATIONS,Actual_Output,j,k,l,m,flag=1;
    float WeightedSum=0,err;
    
    int Activation_Function(float weighted_sum,float threshold);
    float Check_Output(FILE * ftp, float actual_output);
    
    //OPENING THE FILE TO READ!
     file_pointer = fopen("Training_Dataset.txt", "r");
    fptr=fopen("train_output.txt","w");
    if (file_pointer == NULL)
    {
        fprintf(stderr, "Cannot open training data file.\n");
        fprintf(stderr, "Check permissions for data file.\n");
        exit(1);
    }  
  if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
	
	//INITIALIZATION
	for(i=0;i<NO_OF_INPUTS+1;i++)
    {
      if(i==0)
      {
        input[i]=1;
      }
      else
      {
        input[i]=0;

      }
     
	
		  weight[i]=((float)(rand()%10)/10);
	
    }  
int epoch=0;
float c;
	while( iterations!=0)    
	{
    flag=0;
    epoch=epoch+1;
    fprintf(fptr,"---------------------------\n");
    fprintf(fptr,"\n\nEPOCH = %d\n",epoch);
    fprintf(fptr,"---------------------------\n\n");
    i=0;
		for(i=0;i<N_SAMPLES;i++)
		{
      fprintf(fptr,"\nTraining Example: %d \n",i);
      k=1;
			for(k=1;k<NO_OF_INPUTS+1;k++)
			{
				count++;
        fscanf(file_pointer,"%f ",&c);
        input[k] = c;
				
				
		  }
		    if(count==N_SAMPLES)
        {
          break;
        }
			
		    //SUMMED WEIGHTS
		    WeightedSum=0;
        l=0;
		    for(l=0;l<NO_OF_INPUTS+1;l++)
		    {
		    	
		    		WeightedSum=WeightedSum+(input[l]*weight[l]);
            
				
			  }
      fprintf(fptr,"Weighted Sum: %f \n",WeightedSum);
			Actual_Output=Activation_Function(WeightedSum,THRESHOLD);
      fprintf(fptr,"Actual Output: %d \n",Actual_Output );
			err=Check_Output(file_pointer,Actual_Output);
      fprintf(fptr,"Error: %f\n",err);
      //fseek(file_pointer, sizeof(struct threeNum), SEEK_END)
      //printf("ERR: %f\n",err);
      //printf("  INPUT: ");
     /* j=0;
      for( j=0;j<NO_OF_INPUTS+1;j++)
      {
        printf(" %f",input[j]);
      }
      printf("\nWeighted Sum= %f\n\n",WeightedSum);*/
      
			if(err!=0)
			{
				fprintf(fptr,"Status: MISCLASSIFIED \n");
		    flag=1;
        m=0;
				for(m=0;m<NO_OF_INPUTS+1;m++)
        {
             weight[m]=weight[m]+(LEARNING_RATE*(err)*input[m]);
        }
         
    	        
			}
      else{
        fprintf(fptr,"Status: CLASSIFIED \n");
      }
      m=0;
        
        fprintf(fptr,"Updated Weights: ");
				for(m=0;m<NO_OF_INPUTS+1;m++)
        {
             fprintf(fptr, "%f ",weight[m]);
        }
        fprintf(fptr,"\n\n");
			
		}
	
	    //GET TRAINING EXAMPLE ONE
	  rewind(file_pointer);
		iterations--;
	}
  i=0;
  fprintf(fptr,"\n\nFINAL WEIGHT VECTOR: ");
	for(i=0;i<NO_OF_INPUTS+1;i++)
	{
		fprintf(fptr,"%f ",weight[i]);
	}	
 // fprintf(fptr,"\n\n");
  fclose(file_pointer);
  fclose(fptr);
  
  //TESTING
  file_pointer = fopen("Testing_Dataset.txt", "r");
  fptr=fopen("test_output.txt","w");
     if (file_pointer == NULL)
    {
        fprintf(stderr, "Cannot open training data file.\n");
        fprintf(stderr, "Check permissions for data file.\n");
        exit(1);
    }
    if(fptr==NULL)
    {
      fprintf(stderr, "Cannot open training data file.\n");
        fprintf(stderr, "Check permissions for data file.\n");
        exit(1);
    }
    fprintf(fptr,"TESTING");
		for(i=0;i<NO_OF_INPUTS+1;i++)
    {
      if(i==0)
      {
        test_input[i]=1;
      }
      else
      {
        test_input[i]=0;

      }
    
    }
    i=0;
    count=0;
    for(i=0;i<TEST_SAMPLES;i++)
		{
      fprintf(fptr,"\nInput: %d",i);
      k=1;
			for(k=1;k<NO_OF_INPUTS+1;k++)
			{
        fscanf(file_pointer,"%f ",&c);
        test_input[k] = c;
				
				
		  }
		   WeightedSum=0;
        l=0;
		    for(l=0;l<NO_OF_INPUTS+1;l++)
		    {
		    	
		    		WeightedSum=WeightedSum+(test_input[l]*weight[l]);
            
				
			  }
        fprintf(fptr,"Weighted Sum: %f\n",WeightedSum);
			Actual_Output=Activation_Function(WeightedSum,THRESHOLD);
      fprintf(fptr,"Actual Output: %d\n",Actual_Output);
			err=Check_Output(file_pointer,Actual_Output);
      fprintf(fptr,"Error: %f\n",err);
      if(err==0)
      {
        fprintf(fptr,"Status: CLASSIFIED\n");
      }
      else
      {
        fprintf(fptr,"Status: MISCLASSIFIED\n");
        count++;
      }
      
  
    }
      fprintf(fptr,"\n\nCLASSIFIED TESTING SAMPLES = %d / %d\n",(TEST_SAMPLES-count),TEST_SAMPLES );
      fprintf(fptr,"MISCLASSIFIED TESTING SAMPLES = %d / %d\n",(count),TEST_SAMPLES );
	   float accuracy=(1-((float)count/TEST_SAMPLES));
     fclose(file_pointer);
    fprintf(fptr,"\n\nACCURACY = %f",accuracy);
    fclose(fptr);
	    
	    
	    
	    
	    
	}
