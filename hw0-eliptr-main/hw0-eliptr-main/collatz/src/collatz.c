#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	
	if (argc != 3) {
	    printf("again\n");
	    return 1;
	}
	
	long long s = atoi(argv[1]); //κατω οριο
	long long f = atoi(argv[2]); //ανω οριο

	int maxc = 0, c; 

	if (s>0) {  //ελεγχει αν το κατω οριο ειναι παω απο 0, αλλιως δεν τρεχει καμια επαναληψη
	    
   	  for (long long i = s; i <=f; i++) {
		  long long nu = i;
		  c = 1;
		  while (nu != 1) {
	                 if (nu % 2 == 0) {
		 		 if (nu % 8 == 0) {
					 nu = nu/8;
					 c = c +3;

			         } else if (nu % 4 == 0 && nu!=4) {
					  nu = ((nu/4)*3 +1)/2;
					  c = c+4;
				  
				 } else if (nu == 4) {
					 c = c+2;
					 
					 break; 
			         } else if (nu != 2) {
					   
					  nu = ((nu /2)*3 +1)/2;
					  c = c + 3;
				  
				 } else {
					  c++;
					  break;
				 }
			  } else {
				  nu = (nu * 3 + 1)/2;
				  c = c + 2;
			  }
	              /*  printf("%u\n", nu); */
		  }
		  if (c > maxc) maxc = c;
		  
	  } 
		
	}

	printf("%d\n", maxc);
	return 0;
}
