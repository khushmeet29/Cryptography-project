/*	ALPHA QWERTY CIPHER - It intends to extend the original 26 character VIGENÈRE CIPHER to a 92 characters case sensitive cipher 		including digits and some other symbols commonly used in the English language and can be written from a computer keyboard. The     		alpha- qwerty cipher also changes the mapping sequence used in the VIGENÈRE CIPHER. The mapping takes from a extended alphabet  	sequence to extended qwerty keyboard sequence. To decrypt the code reverse mapping takes place (compliment of encryption) that is 		from extended QWERTY keyboard to extended alphabet sequence.
	
	Plain text sequence is:
	a-z, A-Z, 0-9, ` ~ ! @ # $ % ^ & * ( ) _ - = + { } [ ] | ; : " <> , . ? /
	Cipher text sequence is:
	q-z, Q-Z, ` ~ ! @ # $ % ^ & * ( ) _ - = + { } [ ] | ; : " <> , . ? / , 0-9
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	FILE *fp2;
	
	fp = fopen(argv[1], "rb+");
	fp2 = fopen("t.txt", "w+b");	
	
	if(fp == NULL) {
		perror("open failed");
		return errno;
	}
	
	if(argc < 2) {
		printf("bad arguments");
		return errno;
	}
	
	int i = 0, j = 0;
	char ch;
	char c[100] = {}, key[5] = "shaan";
	int try[100];
	
	for(i = 0, j = 0; i < 5; i++) { //converting key to upper case
  		if(key[i % 5] != ' ') {
   			key[j] = toupper(key[i]);   
   			j++;
  		}
 	}
 	key[j] = '\0';
	
	while(!feof(fp)) {
		
		fscanf(fp, "%s ", c); //reading stings from file
		int len = strlen(c);	

		for(i = 0, j = 0; i < len; i++) { //converting all text to upper case
			if(c[i] != ' ') {
				c[j] = toupper(c[i]);   
				j++;
			}
 		}
		c[j] = '\0'; 
		 
    		for(i = 0; i < len; i++) { //encrytion process
				try[i] = c[i] + key[i % 5]; 
    		}

    		for(i = 0; i < len; i++) { //if value out of range, substract 92 to bring the values in range
     			if(try[i] > 92) {
      				try[i] = try[i] - 92;
    			}
   		}

		for(i = 0; i < len; i++) { //saving the encrypted text in the file
      			fprintf(fp2, "%c", ((try[i] % 92))); 
    		}

		fprintf(fp2, "%s", " ");
		memset(c, 0, sizeof(c));
		
	}

	fclose(fp);
	fclose(fp2);
	
	int check;
	check = rename("t.txt", argv[1]);
			
	if(check == 0) {
		remove(argv[0]);		
		printf("ENCRYPTION COMPLETE\n"); 		
	}
	else { 
		printf("ERROR\n");
		fclose(fp);
		fclose(fp2);
	}

	return 0;
}







	
	
