/*
	C program to get occurrence of particular character or word in english language in the text files

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//structure for count characters in a text file
typedef struct __{
	char letter; 	    //letter
	unsigned int freq;  //frequency of letter occurs
	double percentage;
}count;
//structure for count words in a text
typedef struct _{
    char *str;            //word
    int count; 		  //number of times word occurs
    float per;        
    struct _ *next;       //pointer to next word
} word;
word *phead=NULL;	  //head pointer to word
//function prototypes
void adds(char *nword);
word* createword(char* nword);
void charactercount(char filename[][255],int rows,int scale,int bar);
void wordcount(char filename[][255],int rows,int scale,int bar);

int rows;
int error,bar;
int main(int argc,char *argv[]){

	int check=-1,point=-1,number,i,j,k,checkfiles,n,m,scale,arg;  //declare variables
	char filename[4][255]={"english.txt","exam.50","engineer.hum","big.txt"}; //store text files which we want to read in two dimensional array
	//if no input files were given, only the program name was given
	if(argc==1){
		error=1;
	}
	// invalid -l arguments handling
	i=1;
	while(i<argc && argc>1){
		if(strcmp(argv[i],"-l")==0){
			if(strcmp(argv[argc-1],"-l")==0){
				error=3;
				point=1;
				break;
			}
			if(atoi(argv[i+1])<0){
				error=7;
				point=1;
				break;
			}
			if(isdigit(argv[i+1][0])==0){
				error=5;
				point=1;
				break;
			}
		}
		
		if(point==1){
			break;
		}
		++i;
		if(i==argc){
			point=2;
		}
	}
	//invalid arguments with '-' handling
	if(point==2){
		i=1;
		while(i<argc){
			if(argv[i][0]=='-'){
				if((strcmp(argv[i],"-c")!=0) && (strcmp(argv[i],"-w")!=0) && (strcmp(argv[i],"--scaled")!=0)&&((strcmp(argv[i],"-l")!=0))){
					if(strcmp(argv[i-1],"-l")!=0){
						arg=i;
						error=4;
						point=3;
						break;
					}
				}
			}
			if(point==3){
				break;
			}
			++i;
			if(i==argc){
				point=4;
			}
		}
	}
	//invalid arguments without '-'(such as invlaid text files) 
	if(point==4){
		i=1;
		while(i<argc){
			if(argv[i][0]!='-'){
				if((strcmp(argv[i],"english.txt")!=0) && (strcmp(argv[i],"exam.50")!=0) && (strcmp(argv[i],"engineer.hum")!=0)&&((strcmp(argv[i],"big.txt")!=0))){
					if(strcmp(argv[i-1],"-l")!=0){
						error=2;
						point=5;
						break;
					}
				}
			}
			if(point==5){
				break;
			}
			++i;
			if(i==argc){
				point=6;
			}
		}
	}
	// arguments with only having valid text files
	if(point==6){
		i=1;
		while(i<argc){
			check=9;
			if((strcmp(argv[i],"english.txt")==0) || (strcmp(argv[i],"exam.50")==0) || (strcmp(argv[i],"engineer.hum")==0)||((strcmp(argv[i],"big.txt")==0))){
				check=10;
				
			}
			if(check==9){
				point=7;
				break;
			}
			++i;
			// copy the arguments of text files to another array for passing textfiles to functions
			if(i==argc && check==10){
				k=1;
				checkfiles=0;
				char newfilename[4][255];
				int filecount=0;
				while(k<argc){			
					for(j=0;j<4;++j){
						
						if(strcmp(argv[k],filename[j])==0){
							strcpy(newfilename[filecount],filename[j]);
						
							filecount++;
							checkfiles=1;
						}
					}
					++k;
				}
				wordcount(newfilename,filecount,1,10);
				point=8;
				break;
			}
		}
	}
	//argument handling with "-l"  
	if(point==7 ){
		i=1;
		while(i<argc){
			if(strcmp(argv[i],"-l")==0){
				check=1;
				
				if(isdigit(argv[i+1][0])!=0){
					//store text files in an array
					k=1;
					checkfiles=0;
					char newfilename[4][255];
					int filecount=0;
					while(k<argc){
						
						for(j=0;j<4;++j){
						
							if(strcmp(argv[k],filename[j])==0){
								strcpy(newfilename[filecount],filename[j]);
						
								filecount++;
								checkfiles=1;
							}
						}
						++k;
					}
					//if given arguments(text files) are valid
					if(checkfiles==1){
						j=1;
						n=0;
						error=0;
						while(j<argc){
							//if -w and -c are appeared in same time
							if(strcmp(argv[j],"-w")==0){
								k=1;
								while(k<argc){
									if(strcmp(argv[k],"-c")==0){
										error=6;
										break;
									}
									++k;
								}
								//if having -l argument with -w
								if(error!=6){
									n=1;
									break;
								}
							}
							++j;
							//if no argument as -w
							if(j==argc){
								n=0;
							}
						}
						//check that weather -c argument
						if(n==0 && error!=6){
							j=1;
							while(j<argc){
								if(strcmp(argv[j],"-c")==0){
									m=1;
									break;
								}
								++j;
								if(j==argc){
									m=0;
								}
							}
						}
						//argument handling with -l and with --scaled or without --scaled 
						if(m==0 && n==0 && error!=6){
							j=1;
								
							while(j<argc){
								//with --scaled
								if(strcmp(argv[j],"--scaled")==0){
									wordcount(newfilename,filecount,0,atoi(argv[i+1]));
									check=1;
									break;
								}
								++j;
								//without --scaled
								if(j==argc){
									wordcount(newfilename,filecount,1,atoi(argv[i+1]));
									check=1;
									break;
								}
							}
						}
						//argument handling with -l,-w and with --scaled or withut --scaled
						if(n==1 && error!=6){
							j=1;
							while(j<argc){
								//with --scaled
								if(strcmp(argv[j],"--scaled")==0){
									wordcount(newfilename,filecount,0,atoi(argv[i+1]));
									check=1;
									break;
								}
								++j;
								//without --scaled
								if(j==argc){
									wordcount(newfilename,filecount,1,atoi(argv[i+1]));
									check=1;
									break;
								}
							}
						}
						//argument handling with -l,-c and with --sacled or without --scaled  
						if(m==1 && error!=6){
							j=1;
							while(j<argc){
								//with --sacled
								if(strcmp(argv[j],"--scaled")==0){
									charactercount(newfilename,filecount,0,atoi(argv[i+1]));
									check=1;
									break;
								}
								++j;
								//without --scaled
								if(j==argc){
									charactercount(newfilename,filecount,1,atoi(argv[i+1]));
									check=1;
									break;
								}
							}
						}	
							
					}
					//if input text files are not given as arguments
					else{
						error=1;
						break;
					}
				}
			}
			if(check==1){
				break;
			}
			++i;
			// when "-l" haven't as argument
			if(i==argc){
				check=0;
			}
		}
		//argument handling with "-c" but not have "-l"
		if(check==0){
			i=1;
			while(i<argc){
				// check wether -c in the arguments
				if(strcmp(argv[i],"-c")==0){
					check=2;
					j=1;
					// to give the error when -c and -w are appered together in same command line arguments
					while(j<argc){
						if(strcmp(argv[j],"-w")==0){
							error=6;
							break;
						}
						++j;
					}
					if(error==6){
						break;
					}
					//if no error, check that input text files and store them in an array
					k=1;
					checkfiles=0;
					char newfilename[4][255];
					int filecount=0;
				
					while(k<argc){
					
						for(j=0;j<4;++j){
						
							if(strcmp(argv[k],filename[j])==0){
								strcpy(newfilename[filecount],filename[j]);
						
								filecount++;
								checkfiles=1;
							}
						}
					
						++k;
					}
					// if input text files are valid then check that scale or not
					if(checkfiles==1){
						j=1;
						
						while(j<argc){
							//argument handling with have -c and --scaled 
							if(strcmp(argv[j],"--scaled")==0){
								charactercount(newfilename,filecount,0,10);
								check=2;
								break;
							}
					
							
							++j;
							//without --scaled
							if(j==argc){
								charactercount(newfilename,filecount,1,10);
								check=2;
								break;
							}
						}
						
					}
					//if not give the text files as input arguments
					else{
						error=1;
						break;
					}
				}
				if(check==2){
					break;
				}
				++i;
				//if doesn't present the "-c" as argument
				if(i==argc){
					check=3;
				}
			}
		}
		// argument handling with "-w", but not have "-l" and "-c"
		if(check==3){
			i=1;
			while(i<argc){
				//check that -w is in the arguments
				if(strcmp(argv[i],"-w")==0){
					check=4;
					k=1;
					checkfiles=0;
					char newfilename[4][255];
					int filecount=0;
					//check that input text files and store them in an array
					while(k<argc){
					
						for(j=0;j<4;++j){
						
							if(strcmp(argv[k],filename[j])==0){
								strcpy(newfilename[filecount],filename[j]);
						
								filecount++;
								checkfiles=1;
							}
						}
					
						++k;
					}
					//if valid text files are given, then check that scale or not
					if(checkfiles==1){
						j=1;
						while(j<argc){
							//with --scaled
							if(strcmp(argv[j],"--scaled")==0){
								wordcount(newfilename,filecount,0,10);
								check=4;
								break;
							}
					
						
							++j;
							//without --scaled
							if(j==argc){
								wordcount(newfilename,filecount,1,10);
								check=4;
							}
						}
					}
					//if input text files are not given as argumnets
					else{
						error=1;
						break;
					}
				}
				if(check==4){
					break;
				}
				++i;
				// if "-w" is not in the command line arguments
				if(i==argc){
					check=5;
				}
			}
		}
		//argument handling with "--scaled" but not have "-l","-c","-w"
		if(check==5){
			i=1;
			while(i<argc){
				check=6;
				k=1;
				checkfiles=0;
				char newfilename[4][255];
				int filecount=0;
				//check that input text files and store them in an array
				while(k<argc){
					
					for(j=0;j<4;++j){
						
						if(strcmp(argv[k],filename[j])==0){
							strcpy(newfilename[filecount],filename[j]);
						
							filecount++;
							checkfiles=1;
						}
					}
					
					++k;
				}
				//if have the valid input text files
				if(checkfiles==1){
					j=1;
					while(j<argc){
						//with --scaled without any argument, then it prints the default as word count with 10 bars
						if(strcmp(argv[j],"--scaled")==0){
							wordcount(newfilename,filecount,0,10);
							check=6;
							break;
						}
						++j;
					}
				}
				//if no input text files as arguments
				if(checkfiles==0){
					error=1;
					break;
				}
				if(check==6){
					break;
				}
				++i;
				if(i==argc){
					check=7;
				}
			}
		}
		
	}
	// errors when arguemnt handling
	if(error==1){
		printf("No input files were given\nnusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
	}
	else if(error==2){
		printf("Cannot open one or more given files\n");
	}
	else if(error==3){
		printf("Not enough options for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
	}
	else if(error==4){
		printf("Invalid option [%s]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[arg],argv[0]);
	}
	else if(error==5){
		printf("Invalid options for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
	}
	else if(error==6){
		printf("[-c] and [-w] cannot use together\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
	}
	else if(error==7){
		printf("Invalid option(negative) for [-l]\nusage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
	}
	else{
		return 0;
	}
}
//to get the character count in the text files
void charactercount(char filename[][255],int rows,int scale,int bar)
{
	FILE *fptr; // declare the variable as file pointer
	
	count text[36]; // declare the structer 'count' type array variable to store all alphanumeric characters 
	int i=0,j,rownum=0;
	//initialization of alphabetic charaters, its occurrences and percentage of occurrences
	for(i=0;i<26;++i){
		
		text[i].letter=i+'a';
		text[i].freq=0;
		text[i].percentage=0.0;
	}
	j=0;
	//initialization of numeric characters, its occrences and percentage of occurrences
	for(i=26;i<36;++i){
		text[i].letter=j+'0';
		text[i].freq=0;
		text[i].percentage=0.0;
		++j;
	}
	char c,d,e,f;
	//read the all text files as given in the arguments
	while(rownum<rows){
		fptr=fopen(filename[rownum],"r");  //open a file for reading
	
		c=fgetc(fptr); // read the file, character by character
	
		while(c!=EOF){
			//if character is the number, then it is counted and store it in the array
			if(c>='0' && c<='9'){
				text[c+26-'0'].freq++;
				
			}
			//if the character is not an alphanumeric character, then skip it and read the next character of file
			if((c<'A'&& c>'9') ||(c<'0')|| (c>'Z' && c<'a') || (c>'z') || c=='\n' ){
				c=fgetc(fptr);
			}
			// if character is an alphabatic character, first it is converted to lower case and the it is counted and read the next character
			else{
				d=tolower(c);
				text[d-'a'].freq++;
				c=fgetc(fptr);
			}
		}
		fclose(fptr);  // close the file
		++rownum;      // to iterate until finish reading all input text files
	}
	// get the sum of all characters in the text file
	unsigned int sum=0;
	for(i=0;i<36;++i){
		sum=sum+text[i].freq;
	}
	// sort the count text[36] array in their frequencies
	count temp;
	for(i=0;i<36;++i){
		for(j=i+1;j<36;++j){
			if(text[i].freq<text[j].freq){
				temp=text[j];
				text[j]=text[i];
				text[i]=temp;
			}
			
		}
		
	}
	//after sorting, if same frequiency occured then swap them as given alphanumeric order
	for(i=0;i<36;++i){
		for(j=i+1;j<36;++j){
			if((text[i].freq==text[j].freq) &&(((text[i].letter+'a')>(text[j].letter+'a'))||((text[i].letter+'0')>(text[j].letter+'0')))){
				temp=text[j];
				text[j]=text[i];
				text[i]=temp;
			}
			
		}
		
	}
	
	// get the occurences of each character as percentage
	for(i=0;i<36;++i){
		text[i].percentage=(((double)text[i].freq)/sum)*100;
		
	}
	j=1;
	int k=0;
	float percen;
	int l,m=2,n=3;
	// print the horizontal bar chart
	printf("\n");
	for(i=1;i<=(3*bar+bar);++i){
		//print the first row of each bar
		if(i==j){
			printf("   ");
			printf("\u2502");
			if(scale==1){
				percen=0.7*text[k].percentage;
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			else{
				if(k==0){
					for(l=0;l<70;++l){
				
						printf("\u2591");
					}
				}
				else{
					percen=(70.0/text[0].percentage)*text[k].percentage;
				
					for(l=0;l<(int)percen;++l){
						printf("\u2591");
					}
				
				}
			}
			j=j+4;
		}
		//print the second row of each bar
		else if(i==m){
			printf(" %c ",text[k].letter);
			printf("\u2502");
			if(scale==1){
				percen=0.7*text[k].percentage;
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			else{
				percen=(70.0/text[0].percentage)*text[k].percentage;
					
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			printf("%.2f%%",text[k].percentage);
			
			m=m+4;
		}
		//print the third row of each bar
		else if(i==n){
			printf("   ");
			printf("\u2502");
			if(scale==1){
				percen=0.7*text[k].percentage;
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			else{
				percen=(70.0/text[0].percentage)*text[k].percentage;
				
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			n=n+4;
			++k;
			
		}
		//print the vertical line between two bars
		else{
			printf("   ");
			printf("\u2502");
		}
		printf("\n");
	}
	printf("   ");
	printf("\u2514");
	for(l=1;l<=77;++l){
		printf("\u2500");
	}
	printf("\n");
	
}
// function to get the word occurrences of the text files
void wordcount( char filename[][255],int rows,int scale,int bar)
{
	FILE *fptr1; // declare the file pointer
	char newword[255];  // variable to store a word
	int len=0;
	
	char c1,d1;
	int rownum=0;
	int sumnum=0;
	//read all text files as given in the arguments
	while(rownum<rows){
		fptr1= fopen (filename[rownum], "r"); //open the text file to read
		c1=fgetc(fptr1); // read the text file character by character
		while(c1!=EOF){
			//if charcter is an alphanumeric character
			if((c1>='A'&&c1<='Z')||(c1>='a'&& c1<='z')||(c1>='0'&& c1<='9')){
				while((c1>='A'&&c1<='Z')||(c1>='a'&& c1<='z')||(c1>='0'&& c1<='9')){
					d1=tolower(c1); // to convert the character into lower case
					newword[len++]=d1; // add that character into an array
					c1=fgetc(fptr1); // read the next chacter until found the non alphanumeric charcter
					
					//if character is not the alphanumeric 
					if((c1>='!'&&c1<'0')||(c1>'9' && c1<'A')||(c1>'Z'&& c1<'a')||(c1>'z'&& c1<='~')){
						c1=fgetc(fptr1);
						// get the next characters until found the alphanumeric character
						while(!((c1>='A'&&c1<='Z')||(c1>='a'&& c1<='z')||(c1>='0'&& c1<='9'))&&!(c1<'!')){
							c1=fgetc(fptr1);
						}	
						//if found the alphanumeric character cntinue the same word
						if((c1>='A'&&c1<='Z')||(c1>='a'&& c1<='z')||(c1>='0'&& c1<='9')){
						
							continue;
						}
						// if not break that word and go to the count next word
						else{
							break;
						}
					}
				}
			
			}
			// if not an alphanumeric character skip it and read the next character
			else{
				c1=fgetc(fptr1);
			}
			// if found the word
			if(len>0){
				newword[len]='\0';
				adds(newword);   // word is added by function to list
				c1=fgetc(fptr1);
			}
			len=0; //restore the length of the word to get next new word
		
		}
		++rownum;
	}																						
	word *pcount,*pcount1=NULL,*max;
	int temp;
	char *temp1;
	pcount=phead;
	// sort the list as frequiencies
	while(pcount!=NULL){
		max=pcount;
		
		pcount1=pcount->next;
		while(pcount1!=NULL){
			
			if((pcount1->count)>(max->count)){
				max=pcount1;
			}
			pcount1=pcount1->next;
		}
		if(max!=pcount){
			temp=max->count;
			temp1=max->str;
			max->count=pcount->count;
			max->str=pcount->str;
			pcount->count=temp;
			pcount->str=temp1;
			
		}
			
		
		pcount=pcount->next;
	}
	int sum=0;
	// to get the sum of all occurrences of all words
	pcount=phead;
	while(pcount!=NULL){
		sum=sum+(pcount->count);
		
		pcount=pcount->next;
	}
	// to get the longest word length of the file
	word *pcurrent=phead;
	int i;
	int maxlen=strlen(pcurrent->str);
	for(int i=0;i<bar-1;++i){
		if(strlen(pcurrent->next->str)>maxlen){
			maxlen=strlen(pcurrent->next->str);
			
		}
		pcurrent=pcurrent->next;
	}
	// store the each words' occurrences as percentage
	pcurrent=phead;
	while(pcurrent!=NULL){
		pcurrent->per=((float)(pcurrent->count)/sum)*100;
		pcurrent=pcurrent->next;
	}
	pcurrent=phead;
	float percen;
	int k=0,j=1,m=2,n=3,space=1,l,maxlength;
	maxlength=72-maxlen; // to get length of spaces before the vertical line(y axis) of the graph

	// print the horzontal bar graph
	printf("\n");
	for(i=1;i<=(3*bar+bar);++i){
		space=1;
		//to print the first row of bar
		if(i==j){
			while(space<=maxlen+2){
				printf(" ");
				++space;
			}
			printf("\u2502");
			if(scale==1){
				
				percen=((float)maxlength/100)*(pcurrent->per);
				
				for(l=0;l<(int)(percen);++l){
					printf("\u2591");
				}
			}
			else{
				
				if(pcurrent==phead){
					for(l=0;l<maxlength;++l){
				
						printf("\u2591");
					}
				
				}
				else{
					percen=(maxlength/(phead->per))*pcurrent->per;
				
					for(l=0;l<(int)(percen);++l){
						printf("\u2591");
					}
				
				}
			}
			j=j+4;
		}
		//to print the second row of bar
		else if(i==m){
			printf(" ");
			printf("%s",pcurrent->str);
			int length=strlen(pcurrent->str);
			for(l=length;l<=maxlen;++l){
				printf(" ");
			}
			printf("\u2502");
			if(scale==1){
				percen=((float)maxlength/100)*(pcurrent->per);
				for(l=0;l<(int)(percen);++l){
					printf("\u2591");
				}
			}
			else{
				percen=(maxlength/(phead->per))*pcurrent->per;
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			printf("%.2f%%",((float)(pcurrent->count)/sum)*100);
			m=m+4;
		}
		//to print the third row of bar
		else if(i==n){
			while(space<=maxlen+2){
				printf(" ");
				++space;
			}
			printf("\u2502");
			if(scale==1){
				
				for(l=0;l<(int)(percen);++l){
					printf("\u2591");
				}
			}
			else{
			
				for(l=0;l<(int)percen;++l){
					printf("\u2591");
				}
			}
			n=n+4;
			pcurrent=pcurrent->next;
			++k;
			
		}
		//to print the vertical line between two bars
		else{
			while(space<=maxlen+2){
				printf(" ");
				++space;
			}
			printf("\u2502");
		}
		
		
			
		printf("\n");
	}
	space=1;
	while(space<=maxlen+2){
		printf(" ");
		++space;
	}
	printf("\u2514");
	for(l=0;l<maxlength+5;++l){
		printf("\u2500");
	}
	printf("\n");
	// free the memory spaces
	pcount=phead;
	while(pcount!=NULL){
		free(pcount->str);
		phead=pcount;
		pcount=pcount->next;
		free(phead);
	}
	
}
// function to add word in the text file
void adds(char *nword){
	
	word *pcount=NULL;
	word *plast=NULL;
	//if no any words in the list create the new word and add it to the head of the list
	if(phead==NULL){
		phead=createword(nword);
		return;
	}
	pcount=phead;
	// loop until the end of the list to check that word is in the list
	while(pcount!=NULL){

		//if the read word is in the list, it is counted
		if(strcmp(nword,pcount->str)==0){
			++(pcount->count);
			return;
		}
		plast=pcount;
		pcount=pcount->next;
	}
	// if the word is not in the list create new word
	plast->next=createword(nword);
	plast->next->next=NULL;
}
// function to create new word and add it to the list
word* createword(char* nword){
	static word *pcount=NULL;
	pcount=(word*)malloc(sizeof(word));          // allocate the memory to store a new words' data
	pcount->str=(char*)malloc(strlen(nword)+1);  // alloacte the memory to new string to corresponding to word length
	strcpy(pcount->str,nword);		     // copy the new word into the string
	pcount->count=1;			     // count it as 1
	pcount->next=NULL;			     // point to the next as NULL
	return pcount;
}
