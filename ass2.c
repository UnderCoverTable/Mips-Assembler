#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void fileValidity(FILE *fp);
int findFunctBinary(char* functName, char* returnFunctBinary);
int findRegisterBinary(char* registersLine, char* returnBinary,int isImmediate);
long deciToBin(int decimal);
void stripBlank(char fileName[]);


int main(int argc, char *argv[])
{
    FILE *infile;

	if(argc != 2)
	{
		printf("Need to have a file name in the arguments of this program\n");
		exit(0);
	}

    infile = fopen(argv[1],"r");
	fileValidity(infile);
	char fname[100];
	strcpy(fname,argv[1]);

	stripBlank(fname);
	

	char* buff = (char*) malloc(sizeof(char)*100000000);
	char* temp_funct = (char*) malloc(sizeof(char)*1000000);
	char* temp_registers = (char*) malloc(sizeof(char)*1000000);

	char* funct = (char*) malloc(sizeof(char)*1000000);
	char* registers = (char*) malloc(sizeof(char)*1000000);
	char* opI = (char*) malloc(sizeof(char)*1000000);
	char opR[7] = "000000";
	char shamtR[6] = "00000";
	

	int isImmediate = 0;
	int i = 0;
	int j = 0;

	while(fgets(buff,100000000,infile) != NULL){

		i = 0;
		j = 0;
		isImmediate = 0;
		memset(temp_funct,0,1000000);
		memset(temp_registers,0,1000000);
		memset(funct,0,1000000);
		memset(registers,0,1000000);

		while(buff[i] != ' '){
			temp_funct[j] = buff[i];
			j++;
			i++;
		}

		if(strstr(temp_funct,"i") != NULL){
			isImmediate = 1;
		}

		if(isImmediate == 0){
			findFunctBinary(temp_funct,funct);

		}
		if(isImmediate == 1){
			findFunctBinary(temp_funct,opI);
		}

		i++;
		j = 0;
		while(buff[i] != '\0'){
			temp_registers[j] = buff[i];
			i++;
			j++;
		}
		//printf("%s",temp_registers);

		findRegisterBinary(temp_registers,registers,isImmediate);
		//printf("%s",registers);

		if(isImmediate == 0){ // Prints R type
			int c = 0;
			printf("%s",opR);

			while(registers[c] != '\n'){
				printf("%c",registers[c]);
				c++;
			}
			printf("%s%s\n",shamtR,funct);
		}

		if(isImmediate == 1){
			int c = 0;
			printf("%s",opI);

			while(registers[c] != '\n'){
				if(registers[c] == ' '){
					c++;
				}
				else{
					printf("%c",registers[c]);
					c++;
				}
				
			}
			printf("%c",'\n');
		}

		
	}
    
}

void fileValidity(FILE *fp){
	if (fp == NULL){ // Prints an error and exits if file doesnt open
			printf("File did not open correctly. Ending process\n");
			exit(0);
		}
}


int findFunctBinary(char* functName, char* returnFunctBinary)
{	
	/*
		This returns the binary value of the function thats given as input
	*/

	FILE* functsFile;
	functsFile = fopen("funct_binaries","r");
    fileValidity(functsFile);

	

	char* buff1 = (char*) malloc(sizeof(char)*10000);
	char* temp_buff = (char*) malloc(sizeof(char)*10000);
	char* funct_binary = (char*) malloc(sizeof(char)*10000);

	int i = 0;
	int j = 0;

	while(fgets(buff1,10000,functsFile) != NULL){
		i = 0;
		j = 0;
		//memset(temp_buff,0,10000);
		memset(funct_binary,0,10000);

		if(strstr(buff1,functName) != NULL){

			while(buff1[i] != '='){
				temp_buff[i] = buff1[i];
				i++;
			}

			if(strcmp(temp_buff,functName) == 0){
				i++;
				while(buff1[i] != '\n'){
					funct_binary[j] = buff1[i];
					i++;
					j++;
				}
				//printf("%s",funct_binary);
				strcpy(returnFunctBinary,funct_binary);
				//printf("%s",returnBinary);

				fclose(functsFile);

				return 0;

				
			}


	}


}
	
}


long deciToBin(int decimal)
{
	int remainder = 1; 
	int temp = 1;
    long binary = 0;

    while (decimal!=0)
    {
        remainder = decimal%2;
        decimal = decimal / 2;
        binary = binary + remainder*temp;
        temp = temp * 10;
    }
    return binary;
}

int findRegisterBinary(char* registersLine, char* returnBinary, int isImmediate){
	
	FILE* registersFile;
	registersFile = fopen("register_binaries","r");

	char* buff2 = (char*) malloc(sizeof(char)*1000);
	char* rs = (char*) malloc(sizeof(char)*1000);
	char* rt = (char*) malloc(sizeof(char)*1000);
	char* rd = (char*) malloc(sizeof(char)*1000);
	char* imm = (char*) malloc(sizeof(char)*1000);

	
	int i = 0;
	int j = 0;


	if(isImmediate == 0){
			
			while(registersLine[i] != ','){
				rd[j] = registersLine[i];
				i++;
				j++;
			}
			j=0;
			i++;
			while(registersLine[i] != ','){
				rs[j] = registersLine[i];
				i++;
				j++;
			}
			j=0;
			i++;
			while(registersLine[i] != '\n'){
				rt[j] = registersLine[i];
				i++;
				j++;
			}

			//printf("%s %s %s\n",rd,rs,rt);

			i = 0;
			j = 0;
			while(fgets(buff2,1000,registersFile) != NULL){
				if(strstr(buff2,rd) != NULL){

					while(buff2[i] != '=')i++;

					memset(rd,0,1000);
					i++;
					while(buff2[i] != '\n'){
						rd[j] = buff2[i];
						i++;
						j++;
					}
					//printf("%s %s\n",buff2,rd);

				}

			}

			i = 0;
			j = 0;
			memset(buff2,0,1000);
			rewind(registersFile);
			while(fgets(buff2,1000,registersFile) != NULL){
				if(strstr(buff2,rs) != NULL){

					while(buff2[i] != '=')i++;

					memset(rs,0,1000);
					i++;
					while(buff2[i] != '\n'){
						rs[j] = buff2[i];
						i++;
						j++;
					}
					//printf("%s %s\n",buff2,rs);

				}

			}

			i = 0;
			j = 0;
			memset(buff2,0,1000);
			rewind(registersFile);
			while(fgets(buff2,1000,registersFile) != NULL){
				if(strstr(buff2,rt) != NULL){

					while(buff2[i] != '=')i++;

					memset(rt,0,1000);
					i++;
					while(buff2[i] != '\n'){
						rt[j] = buff2[i];
						i++;
						j++;
					}
					//printf("%s %s\n",buff2,rt);
				}

			}

			strcat(returnBinary,rs);
			//strcat(returnBinary," ");
			strcat(returnBinary,rt);
			//strcat(returnBinary," ");
			strcat(returnBinary,rd);
			strcat(returnBinary,"\n");

			//printf("%s",returnBinary);

			//fclose(registersFile);
			

			return 0;
	 }


	if(isImmediate == 1){
		while(registersLine[i] != ','){
			rs[j] = registersLine[i];
			i++;
			j++;
		}
		j=0;
		i++;

		while(registersLine[i] != ','){
			rt[j] = registersLine[i];
			i++;
			j++;
		}
		j=0;
		i++;
		while(registersLine[i] != '\n'){
			imm[j] = registersLine[i];
			i++;
			j++;
		}
		//printf("%s %s %s\n",rs,rt,imm);

		i = 0;
		j = 0;
		while(fgets(buff2,1000,registersFile) != NULL){
			if(strstr(buff2,rs) != NULL){

				while(buff2[i] != '=')i++;

				memset(rs,0,1000);
				i++;
				while(buff2[i] != '\n'){
					rs[j] = buff2[i];
					i++;
					j++;
				}
				//printf("%s %s\n",buff2,rd);

			}

		}

		i = 0;
		j = 0;
		memset(buff2,0,1000);
		rewind(registersFile);
		while(fgets(buff2,1000,registersFile) != NULL){
			if(strstr(buff2,rt) != NULL){

				while(buff2[i] != '=')i++;

				memset(rt,0,1000);
				i++;
				while(buff2[i] != '\n'){
					rt[j] = buff2[i];
					i++;
					j++;
				}
				//printf("%s %s\n",buff2,rs);

			}

		}

		int decimal = atoi(imm);
		int bin_converted = deciToBin(decimal);
		memset(imm,0,1000);
		sprintf(imm,"%d",bin_converted);

		if(strlen(imm) < 16){
			int diff = 16 - strlen(imm);
			char temp_zero[17] = " ";
			char temp_imm[17] = " ";
			strcpy(temp_imm,imm);

			int i = 0;
			while(i != diff){
				i++;
				temp_zero[i] = '0';
				
			}
			
			//printf("%s%s\n",temp_zero,temp_imm);
			memset(imm,0,1000);
			strcat(imm,temp_zero);
			strcat(imm,temp_imm);
			//printf("%s\n",imm);
		}


		//printf("%s %s %s\n",rs,rt,imm);

		strcat(returnBinary,rt);
		//strcat(returnBinary," ");
		strcat(returnBinary,rs);
		//strcat(returnBinary," ");
		strcat(returnBinary,imm);
		strcat(returnBinary,"\n");

		return 0;
	}
}


void stripBlank(char fileName[]){
    /*
        Function will remove any blank lines from the file and updates the out1.c file.
    */

    // Creating file handlers
    FILE *SourceFile;
    FILE *TempFile;
    FILE *OutFile;

    // Open the source file from previous function(For Reading) and create a temp file(For Writing)
    SourceFile = fopen(fileName,"r");
    TempFile = fopen("Temp","w+");

    char* buffer = (char*) malloc(sizeof(char)*100000); // Memory allocated 

    // Reads the file character by character and writes it to the temp file
    char currC = ' ';
    currC = fgetc(SourceFile);

    while(currC != EOF){
        fputc(currC,TempFile);
        currC = fgetc(SourceFile);
    }

    fclose(SourceFile);
    fclose(TempFile);


    // Opens the temp file(For reading) and the Out1.c file(For writing)
    TempFile = fopen("Temp", "r");
    OutFile = fopen(fileName,"w+");
    
    // Reads the temp file and writes each line to the buffer
    while(fgets(buffer,100000,TempFile) != NULL){
        int i = 0;
        int check = 1; // Flag to see if there is text at any point in the line

        if(buffer[0] == '\n' ) continue;
           
        
        if(buffer[0] == ' ' || buffer[0] == '\t' ){         // Will see if the line starts with a space or tab
            while(buffer[i] == ' ' || buffer[i] == '\t' ){ //  It will then see if the line has any text in it
                i++;

                if(buffer[i] == '\n' || buffer[i] == '\0'){ // Line has no text in it so it is not written to out file
                    check = 0;
                    break;
                }
                 
            }
        
            if(check == 1) fprintf(OutFile,"%s",buffer); // The line has some text in it so it will be written to out file
            
             
        }
        else fprintf(OutFile,"%s",buffer); // If the line starts with any text it is written to the out file
    }
	//fprintf(OutFile,"%c",'\n');
    fclose(TempFile);
    remove("Temp"); // Temp file is deleted
    fclose(OutFile);
}