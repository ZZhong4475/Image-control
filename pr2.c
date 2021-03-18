//Name:Zheng Zhong

#include <stdio.h>
#include <string.h>
#include <math.h>

/* This program changes the coloring of the image.
   Each pixel is made from a combination of Red, Green, Blue.
   For each of these 3 colors, there is a number indicating the intensity or brightness.
   These numbers range from 0 (none) to 255 (full).  The program interchanges 
   the intensities of the green and blue components. 
   The blue sky becomes green.   The green tree becomes purple/blue.
   The red things remain red.
*/      

#define HEADER_SIZE 54
#define MAXRGB 255

int main(void) {

   // Asks User to input the image name
    char fName[10];
    unsigned int HEIGHT,WIDTH;
    puts("Enter the file name(please make sure the image is located at the same dictory with the program):");
    scanf(" %s",fName);
    
   //combines the .bmp suffix with the input string
    sprintf(fName,"%s.bmp",fName);
    
    //sets up the input files and output files
    FILE *infile = fopen(fName, "rb");
    FILE *sepiaOut = fopen("Sepia.bmp", "wb");  
    FILE *popOut = fopen("pop.bmp", "wb"); 
    FILE *Flip = fopen("Flip.bmp", "wb"); 
    FILE *Mirror = fopen("Mirror.bmp", "wb"); 
    FILE *Suprise = fopen("Suprise.bmp", "wb"); 


    puts("Please enter height and width(in pixels):");
    scanf(" %u %u", &HEIGHT,&WIDTH);
    
    // sets up an array for bmp header
    char header[HEADER_SIZE]; 
   

    // reads header from the image into the header array
     fread( header, 1 , HEADER_SIZE , infile);

    // sets up two 2d arrays: original and copy 
    unsigned char original[HEIGHT][WIDTH * 3];
    unsigned char copy[HEIGHT][WIDTH * 3];
 
   
   
    // reads image into the original matrix
    fread( original, 1 , HEIGHT * WIDTH * 3 , infile);
   
     
    int r,c;
  

/*Sepia image algorithm*/

  
   memcpy(copy,original,sizeof(original));

   // Processes sepia algorithm
    for( r = 0; r < HEIGHT; r++) {
	
	
        for ( c =0; c < WIDTH*3; c += 3) {
          unsigned char B = copy[r][c],G = copy[r][c+1],R = copy[r][c+2];
	
	  unsigned int newBlue = R*0.272+G*0.534+B*0.131,newGreen=R*0.349+G*0.686+B*0.168,newRed=R*0.393+G*0.769+B*0.189;
	  if(newBlue >MAXRGB){
	   newBlue = MAXRGB;	
	   }
	   if(newGreen>MAXRGB){
	   newGreen = MAXRGB;	
	   }
	   if(newRed > MAXRGB){
	   newRed = MAXRGB;	
	   }
	   copy[r][c]=newBlue;
	   copy[r][c+1]=newGreen;
	   copy[r][c+2]=newRed;
	
            }

	
	
      }
   
    puts("The Sepia picture has been generated\n");
    // writes the header to the output file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  sepiaOut);
    // writes the matrix to the output file
    fwrite( copy, sizeof(char)  , HEIGHT * WIDTH * 3  ,  sepiaOut);
    fclose(sepiaOut);

    // end of Sepia


/*Color Pop image algorithm*/


  

    memcpy(copy,original,sizeof(original));
    
    //sets up three cells for the middle pixel
    unsigned char midPixBlue = original[HEIGHT/2][WIDTH*3/2];
    unsigned char midPixGreen =  original[HEIGHT/2][(WIDTH*3/2)+1];
    unsigned char midPixRed =  original[HEIGHT/2][(WIDTH*3/2)+2];

  
    //processes color pop operation
     for( r = 0; r < HEIGHT; r++) {
	

        
	
         for ( c =0; c < WIDTH*3; c += 3) {
         
         //calculate distance between pixels and the middle pixels
         unsigned char B = copy[r][c],G = copy[r][c+1],R = copy[r][c+2];
         int p1 = (midPixBlue - B)*(midPixBlue-B);
         int p2 = (midPixGreen-G)*(midPixGreen-G);
         int p3 = (midPixRed-R)*(midPixRed-R);
         int distance = sqrt(p1+p2+p3);
         
         //if distance is greater than 55, set the color to gray
         if(distance >= 55){

         int avg= (B+G+R)/3;
         copy[r][c]=avg;
         copy[r][c+1]=avg;
         copy[r][c+2]=avg;


        }



       }

   }

  
    puts("The color pop picture has been generated\n");
    // writes the header to the output file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  popOut);
    // writes the matrix to the output file
    fwrite( copy, sizeof(char)  , HEIGHT * WIDTH * 3  ,  popOut);

    fclose(popOut);// end of Color Pop


   /*Vertical Axis Flip Algorithm*/

  memcpy(copy,original,sizeof(original));

 //Processes Vertical Axis Flip
 for(r=0;r<HEIGHT-1;r++){
  for(c= 0 ;c<WIDTH*3;c+=3){

   //reversely copies the pixels from the original pixel matrix.
   //Matrix copying starts from the right pixels of copied matrix, pixels are replaced by the left pixels of original matrix.
  
   copy[r][WIDTH*3-1-2-c]=original[r][c];
   copy[r][WIDTH*3-1-1-c]=original[r][c+1];
   copy[r][WIDTH*3-1-c]=original[r][c+2];
   
   



 }

 }

   puts("The vertical axis flip picture has been generated\n");
  // writes the header to the output file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  Flip);
    // writes the matrix to the output file
    fwrite( copy, sizeof(char)  , HEIGHT * WIDTH * 3  ,  Flip);
    fclose(Flip);// end of Aix Flip
 

 
   /*Horizontal Mirror algorithm*/


  memcpy(copy,original,sizeof(original));
  

 //processes Horizontal mirror algorithm
  
  for(c=0;c<WIDTH*3;c++){
  
  //sets up two pointer, one for top pixels , and other one for bottom pixels
  int start = 0, end = HEIGHT-1;
  
  //Before two pointers meet, copy top pixels to bottom pixels
  while(start<=end){
  copy[start][c]=original[end][c];

  start++;
  end--;

  }
  
}
  
  
 
puts("The horizontal axis mirror picture has been generated\n");
  // writes the header to the output file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  Mirror);
    // writes the matrix to the output file
    fwrite( copy, sizeof(char)  , HEIGHT * WIDTH * 3  ,  Mirror);
    fclose(Mirror);// end of Mirror
 


 /*suprise algorithm:reverse filter*/

 memcpy(copy,original,sizeof(original));

 //processes reverse filter algorithm

 for( r = 0; r < HEIGHT; r++) {



	
	// The reverse filter is difference of 255 - RGB values of a color
         for ( c =0; c < WIDTH*3; c += 3) {
          unsigned char B = copy[r][c],G = copy[r][c+1],R = copy[r][c+2];
	
	  unsigned int newBlue =255-B,newGreen=255-G,newRed=255-R;

	if(newBlue >MAXRGB){
	  newBlue = MAXRGB;	
	}
	if(newGreen>MAXRGB){
	  newGreen = MAXRGB;	
	}
	if(newRed > MAXRGB){
	  newRed = MAXRGB;	
	}
	copy[r][c]=newBlue;
	copy[r][c+1]=newGreen;
	copy[r][c+2]=newRed;
	
         }


    


	
	
    }


   
    

  puts("The suprise picture has been generated\n");
// writes the header to the output file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  Suprise);
    // writes the matrix to the output file
    fwrite( copy, sizeof(char)  , HEIGHT * WIDTH * 3  ,  Suprise);
    fclose(Suprise);// end of Mirror
    


  fclose(infile);//close the input file

 
  puts("Done. Check the generated images");
    return 0;

}
