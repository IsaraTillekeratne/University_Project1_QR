#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define SIZE1 125
#define SIZE2 135


void positionsquare(int color); //function to print a single position identification square
void printbasicframe1(int color); //function to print the basic design for a shorter url
void charpattern(unsigned char ch,int color); //function to print the corresponding pattern for a single character 
void printbasicframe2(int color); //function to print the basic design for a longer url
void printQR132(unsigned char finalstr[],int size,int color); //function to print the final QR code for longer url
void printQR24(unsigned char finalstr[],int size,int color); //function to print the final QR code for shorter url



int main(int argc,char *argv[]){ //main funtion, with argc(number of arguments & argv[](array of strings) parameters

	//declare the variables 
	int hashedlen,urllen,i,j,a,b,c,d=0,toreverse,color;

	//declare the arrays
	unsigned char url[SIZE1];
	unsigned char hashedstr[SIZE2];
	unsigned char reversedarray[SIZE2];
	unsigned char finalstr[SIZE2];
	

	//very first task is to handle command line arguments
	
	if(argc==1){ //if no arguments are given QR should be printed in black and white
		color=40; //for black
	}

	else if((argc==2)&&(strcmp(argv[1],"-h")==0)){ //when -h argument is given correctly 
		printf("usage :\n");
		printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
		printf("%s -h for the help about the program\n",argv[0]);
		return 0;
	}

	//if -c is given with one another argument

	else if((argc==3)&&(strcmp(argv[1],"-c")==0)){

		//since color is not case sensitive argv[2] converts to all simple

		a=strlen(argv[2]);
		char str1[a]; //str1 is created to store the simple letter form of argv[2]
		for(i=0;i<a;i++){
			str1[i]=tolower(argv[2][i]);
		}
	
		//str1 is created with all simple and str1 is compared with allowing colors

		if(strcmp(str1,"black")==0){ //for black
			color=40;			
		}
		else if(strcmp(str1,"red")==0){ //for red
			color=41;			
		}
		else if(strcmp(str1,"green")==0){ //for green
			color=42;			
		}
		else if(strcmp(str1,"yellow")==0){ //for yellow
			color=43;			
		}
		else if(strcmp(str1,"blue")==0){ //for blue
			color=44;			
		}
		else if(strcmp(str1,"magenta")==0){ //for magenta
			color=45;			
		}
		else if(strcmp(str1,"cyan")==0){ //for cyan
			color=46;			
		}
		else{ //when argument for color is invalid
			printf("Invalid argument for color.\n");
			printf("usage :\n");
			printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
			printf("%s -h for the help about the program\n",argv[0]);
			return 0;
		}
	}

	//if any faulse argument is given
	else{

		printf("Incorrect usage of arguments.\n");
		printf("usage :\n");
		printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
		printf("%s -h for the help about the program\n",argv[0]);
		return 0;

	}

	//Get URL as user input
	

     	printf("Enter the URL: ");
	scanf("%s",url);

	urllen=(strlen(url)); //length of url input
	
	//checks input is shorter than 4 characters
	if(urllen<=3){
		printf("String is too short. Not supported by available QR versions\n");
	}

	//checks input is lpnger than 119 characters
	else if(urllen>=120){
		printf("String is too long. Not supported by available QR versions\n");
	}

	//if not,code proceeds to build the hashed url
	else{

		//clear screen
		{
		system("tput clear");
		}

		if(urllen<=20){ //checks if url length is smaller than or equal to 20
			hashedlen = 24; //length of hashed url should be 24
			hashedstr[0]=urllen+50; //first element of hashed string

			a=(hashedlen-1)/urllen; //calculates no of urllen's to be filled
			b=(hashedlen-1)%urllen; //calculates no of elements to be filled further
			for(i=0;i<a;i++){ //loop runs through no of urllen's
				for(j=1+urllen*i;j<=urllen+urllen*i;j++){ //loop to run through next set of elemnts
										
					hashedstr[j]=url[d]+i; //+i part changes the ascii value 
					d++;
				}
				d=0;
							
			}
			
			c=1+(a*urllen);	//calculates no of elements that are filled so far		
			for(i=0;i<b;i++){ //loop to fill the rest of the elements
				hashedstr[c+i]=url[i]+a; //+a part changes the ascii value
			}
			
			//upto now- hashedstr is built without reversing
		

			//to reverse the latter part of the array

			//first half

			toreverse=hashedlen-(1+urllen);
			d=hashedlen-1;
			for(i=0;i<(toreverse/2);i++){
				
				reversedarray[i]=hashedstr[d];
				d--;
			}
			//second half
			
			
			if(toreverse%2==1){ //if toreverse is an odd number
				
				d=urllen+(toreverse/2);
				reversedarray[i]=hashedstr[d+1];
				for(j=i+1;j<=toreverse;j++){
					reversedarray[j]=hashedstr[d];	
					d--;
					
				
				}

			}
			else{ //if toreverse is an even number
				
				d=urllen+(toreverse/2);
				for(j=i;j<=toreverse;j++){
					reversedarray[j]=hashedstr[d];	
					d--;
					
				
				}
			}

			//reversedarray is created, now reversed array should be assigned to hashed str in relavant positions
			d=0;
			for(i=urllen+1;i<=(hashedlen-1);i++){
				hashedstr[i]=reversedarray[d];
				d++;
			}

			//to get rid of garbage values that may assign to hashedstr array, new array finalstr is taken
			for(i=0;i<hashedlen;i++){
				finalstr[i]=hashedstr[i];

			}

			
			//hashed string is created
			printQR24(finalstr,24,color); //to print final QR for smaller version
			printf("\n");
		}

		//when urllen is larger than 20
		else{
			hashedlen = 132; //hashedlen is now 132, only this part is changed
			hashedstr[0]=urllen+50; //first element of hashed string

			a=(hashedlen-1)/urllen; //calculates no of urllen's to be filled
			b=(hashedlen-1)%urllen; //calculates no of elements to be filled further
			for(i=0;i<a;i++){ //loop runs through no of urllen's
				for(j=1+urllen*i;j<=urllen+urllen*i;j++){ //loop to run through next set of elemnts
										
					hashedstr[j]=url[d]+i; //+i part changes the ascii value 
					d++;
				}
				d=0;
							
			}
			
			c=1+(a*urllen);	//calculates no of elements that are filled so far		
			for(i=0;i<b;i++){ //loop to fill the rest of the elements
				hashedstr[c+i]=url[i]+a; //+a part changes the ascii value
			}
			
			//upto now- hashedstr is built without reversing
		

			//to reverse the latter part of the array

			//first half

			toreverse=hashedlen-(1+urllen);
			d=hashedlen-1;
			for(i=0;i<(toreverse/2);i++){
				
				reversedarray[i]=hashedstr[d];
				d--;
			}
			//second half
			
			
			if(toreverse%2==1){ //if toreverse is an odd number
				
				d=urllen+(toreverse/2);
				reversedarray[i]=hashedstr[d+1];
				for(j=i+1;j<=toreverse;j++){
					reversedarray[j]=hashedstr[d];	
					d--;
					
				
				}

			}
			else{ //if toreverse is an even number
				
				d=urllen+(toreverse/2);
				for(j=i;j<=toreverse;j++){
					reversedarray[j]=hashedstr[d];	
					d--;
					
				
				}
			}

			//reversedarray is created, now reversed array should be assigned to hashed str in relavant positions
			d=0;
			for(i=urllen+1;i<=(hashedlen-1);i++){
				hashedstr[i]=reversedarray[d];
				d++;
			}

			//to get rid of garbage values that may assign to hashedstr array, new array finalstr is taken
			for(i=0;i<hashedlen;i++){
				finalstr[i]=hashedstr[i];

			}
			//hashed string for larger QR generated
			printQR132(finalstr,132,color); //to print final qr
			printf("\n");

		}

	}

	return 0;
}
void positionsquare(int color){ //to print position identification square

	int i,j; //variables declared
	for(i=1;i<=6;i++){ //loop to print the outer most square

		for(j=1;j<=6;j++){		
			printf("\x1B[%dm  ",color); //given color is used and spaces are printed whith given color
			printf("\x1B[0m"); //reset code
			
		}
		printf("\x1B[1B"); //cursor moves down once
		printf("\x1B[12D"); //cursor moves left 12 times
		

	}

	
	printf("\x1B[5A"); //cursor moves 5 times up
	printf("\x1B[2C"); //cursor moves two times right
	for(i=1;i<=4;i++){ //loop to print white square in middle
		
		for(j=1;j<=4;j++){		
			printf("\x1B[47m  "); //prints in white
			printf("\x1B[0m"); //reset code
			
		}
		printf("\x1B[1B"); //cursor moves down once
		printf("\x1B[8D"); //cursor moves left 8 times
		

	}
	printf("\x1B[3A"); //cursor moves 3 times up
	printf("\x1B[2C"); //cursor moves two times right
	for(i=1;i<=2;i++){ //loop to print the inner most square
		
		for(j=1;j<=2;j++){		
			printf("\x1B[%dm  ",color); 
			printf("\x1B[0m");//reset code
			
		}
		printf("\x1B[1B"); //cursor moves down once
		printf("\x1B[4D"); //cursor moves left 4 times
		

	}

	//position identification square is printed
	printf("\x1B[2B"); //these codes takes the cursor under the bottom left corner of the box 
	printf("\x1B[4D");
	
}
void charpattern(unsigned char ch,int color){ // to print the pattern for a single char

	int array1[10]; //arrays declared
	int reversedarray[10];
	int a,i=0,j,k,bit; //variables declared
	
	while(ch!=1){ //loop to convert decimal to binary of ascii value
		
		a=ch%2;
		array1[i]=a; //ones and zeroes are stored in an array
		ch=ch/2;
		i++;
	}
	a=ch;
	array1[i]=a; //adds the last elemnt

	
	for(j=i+1;j<9;j++){
		array1[j]=0; //zeros added to complete nine bits
	}

	//reverse the array

	for(i=8,j=0;i>=0;--i,++j){ //even if there were more than 9 ,in here first 9 are only considered
		reversedarray[j]=array1[i]; //reversed array is created
	}

	//prints the pattern
	k=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			
			bit=reversedarray[k];
			if(bit==1){ //for 1 it prints the color
				printf("\x1B[%dm  ",color); //41 should be changed to color
				printf("\x1B[0m");
			}
			else{ //for 0 it prints white
				printf("\x1B[47m  "); //when bit is zero ,white printed
				printf("\x1B[0m");
			}
			k++;
		}
		printf("\x1B[1B"); //cursur moves down once
		printf("\x1B[6D"); //cursor moves left 6, cursor is moved to the bottom of the left bottom corner of the pattern printed
	}



}

void printbasicframe1(int color){ //prints general pattern for short url

	int i,j;

	//this loop prints big box
	for(i=0;i<20;i++){ //CHANGE1 : 20 to size

		for(j=0;j<20;j++){

			printf("\x1B[47m  ");	
			printf("\x1B[0m");
		}
		printf("\n");			
	}
		
	printf("\x1B[19A"); //cursor goes 19 lines up
	printf("\x1B[2C"); //cursor moves right once(one square)
	for(j=1;j<=18;j++){ //to empty the middle part leaving the borderonly
		
		for(i=1;i<=18;i++){
			printf("  ");
		}
		printf("\x1B[1B"); //cursor moves one line down
		printf("\x1B[36D"); //cursor moves 18 squares left
	}
	//basic frame for smaller version is printed
	
	//takes cursor to normal position
	printf("\x1B[2D");
	printf("\x1B[1B");
	
	printf("\x1B[19A"); //cursor goes 19 up
	printf("\x1B[2C"); //cursor moves right once(one square)
	positionsquare(color); //position identification square 1 printed

	printf("\x1B[6A"); //cursor goes 6 up
	printf("\x1B[24C"); //cursor moves right 24 times
	positionsquare(color); //position identification square 2 printed

	printf("\x1B[24D"); //cursor moves left 24 times
	printf("\x1B[6B"); //cursor moves down 6
	positionsquare(color); //position identification square 3 printed

	//takes cursor to normal position
	printf("\x1B[2D");
	printf("\x1B[1B");

}

void printbasicframe2(int color){ //to print the basic frame with position iden. squares for larger qr version

	int i,j;

	//to get a white border, 1st prints a white box
	for(i=0;i<38;i++){ //first prints a 38*38 white box

		for(j=0;j<38;j++){

			printf("\x1B[47m  ");	//white spaces printed
			printf("\x1B[0m");
		}
		printf("\n");			
	}
		
	printf("\x1B[37A"); //cursor goes 37 lines up
	printf("\x1B[2C"); //cursor moves right once(one square)
	for(j=1;j<=36;j++){ //loop to cut off a 36*36 box and make the white the frame
		
		for(i=1;i<=36;i++){
			printf("  "); //spaces printed 
		}
		printf("\x1B[1B"); //cursor moves one line down
		printf("\x1B[72D"); //cursor moves 72 squares left
	}
	//basic frame for larger version is printed
	
	//takes cursor to normal position
	printf("\x1B[2D"); //moves left 2
	printf("\x1B[1B"); //moves down 1

	//to print position ident. square 1	
	printf("\x1B[37A"); //cursor goes 37 up
	printf("\x1B[2C"); //cursor moves rigt 2
	positionsquare(color);

	//to print position ident. square 2	
	printf("\x1B[6A"); //cursor goes 6 up
	printf("\x1B[60C"); //cursor moves right 60 times
	positionsquare(color);

	//to print position ident. square 3
	printf("\x1B[60D"); //cursor moves left 60 times
	printf("\x1B[24B"); //cursor moves down 24
	positionsquare(color);

	//takes cursor to normal position
	printf("\x1B[2D"); //moves left 2
	printf("\x1B[1B"); //moves 1 down

}

void printQR24(unsigned char finalstr[],int size,int color){ //prints final qr for short url

	int i,j,d;
	printbasicframe1(color); //basic frame is printed with position squares

	printf("\x1B[13A"); //cursor up 13
	printf("\x1B[14C"); //cursor right 14

	//characters from 1 to 16 
	d=0;
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			charpattern(finalstr[d],color);
			printf("\x1B[6C"); //cursor right 6
			printf("\x1B[3A"); //cursor up 3 ,cursor took to the position where next box should be printed
			d++;
		}
			
		printf("\x1B[3B"); //cursor down 3
		printf("\x1B[24D"); //cursor left 24 ,cursor took to the position where next box should be printed
	}
	printf("\x1B[18A"); //cursor up 18

	//characters from 17 to 20 
	for(i=1;i<=2;i++){
		for(j=1;j<=2;j++){
			charpattern(finalstr[d],color);
			printf("\x1B[6C"); //cursor right 6
			printf("\x1B[3A"); //cursor up 3 ,cursor took to the position where next box should be printed
			d++;
		}
			
		printf("\x1B[3B"); //cursor down 3
		printf("\x1B[12D"); //cursor left 12 ,cursor took to the position where next box should be printed
	}
	printf("\x1B[12D"); //cursor left 12

	//characters from 20 to 24 
	for(i=1;i<=2;i++){
		for(j=1;j<=2;j++){
			charpattern(finalstr[d],color);
			printf("\x1B[6C"); //cursor right 6
			printf("\x1B[3A"); //cursor up 3 ,cursor took to the position where next box should be printed
			d++;
		}
			
		printf("\x1B[3B"); //cursor down 3
		printf("\x1B[12D"); //cursor left 12 ,cursor took to the position where next box should be printed
	}
	printf("\x1B[7B"); //cursor down 7
	printf("\x1B[2D"); //cursor left 2 ,cursor moved to a new line
}


void printQR132(unsigned char finalstr[],int size,int color){ //function to print the final larger qr version

	int i,j,d;
	printbasicframe2(color); //basic frame with position squares printed

	printf("\x1B[31A"); //cursor up 31
	printf("\x1B[14C"); //cursor right 14

	//characters from 1 to 100 
	d=0;
	for(i=1;i<=10;i++){
		for(j=1;j<=10;j++){
			charpattern(finalstr[d],color);
			printf("\x1B[6C"); //cursor right 6
			printf("\x1B[3A"); //cursor up 3 ,cursor took to the position where next box should be printed
			d++;
		}
			
		printf("\x1B[3B"); //cursor down 3
		printf("\x1B[60D"); //cursor left 60 ,cursor took to the position where next box should be printed
	}
	printf("\x1B[36A"); //cursor up 36

	//characters from 101 to 116 
	for(i=1;i<=2;i++){
		for(j=1;j<=8;j++){
			charpattern(finalstr[d],color);
			printf("\x1B[6C"); //cursor right 6
			printf("\x1B[3A"); //cursor up 3 ,cursor took to the position where next box should be printed
			d++;
		}
			
		printf("\x1B[3B"); //cursor down 3
		printf("\x1B[48D"); //cursor left 48 ,cursor took to the position where next box should be printed
	}
	printf("\x1B[12D"); //cursor left 12

	//characters from 117 to 132
	for(i=1;i<=8;i++){
		for(j=1;j<=2;j++){
			charpattern(finalstr[d],color);
			printf("\x1B[6C"); //cursor right 6
			printf("\x1B[3A"); //cursor up 3 ,cursor took to the position where next box should be printed
			d++;
		}
			
		printf("\x1B[3B"); //cursor down 3
		printf("\x1B[12D"); //cursor left 12 ,cursor took to the position where next box should be printed
	}
	printf("\x1B[7B"); //cursor down 7
	printf("\x1B[2D"); //cursor left 2 ,cursor moved to a new line
		
}

