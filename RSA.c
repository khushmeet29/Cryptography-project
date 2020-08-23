/* 	RSA ENCRYPTION - It is an asymmetric cryptographic algorithm. Asymmetric means that there are two different keys. This is also 		called public key cryptography, because one of the keys can be given to anyone. The other key must be kept private. The algorithm is 		based on the fact that finding the factors of a large composite number is difficult: when the integers are prime numbers, the 		problem is called  prime factorization. It is also a key pair (public and private key) generator.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

double gcd(double a, double b) { //function to check if two numbers are co-prime or not
	double i=0;
	double gcd = 0;
	for(i=1; i<=a && i<=b ; i++) {
    		if((int)a % (int)i == 0 && (int)b % (int)i == 0) {
        		gcd = i;
    		}
	}
	return gcd;
}

double power(double x, double y, double p) //this function is made to find pow(x,y)(mod p) if x,y,p are of double data type 
{ 
    double res = 1;      // Initialize result 
    x = fmod(x,p); // Update x if it is more than or equal to p 
  
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if ((int)y & 1) {
            res = fmod((res*x),p); 
	}
        // y must be even now 
        y = y/2;
        x = fmod((x*x),p); 
    } 
    return res; 
} 

int main (int argc, char *argv[]) {
	char ch;
	FILE *fp;
	FILE *fp2;
	fp = fopen(argv[1], "rb+");
	fp2 = fopen("z.txt", "w+b");
	
	if(fp == NULL) {
		perror("open failed");
		return errno;
	}
	if(argc < 2){
		printf("bad arguments");
		return errno;
	}

	double a = 23, b = 13; //take two prime numbers
	double n;
	n = a * b; //299
	double e = 5;
	double totient = ((a-1) * (b-1)); //264
	while(e < totient) {
		if(gcd(e, totient) == 1) { //e and totient should be co-prime
			break;
		}
		else {
			e++;
		}
	}
	double x = 1; //any double value can be taken here
	double pkey = (1 + (x * totient)) / e; //this is the private key = 53 here which will be used for decryption

	while((ch = fgetc(fp)) != EOF) {
		double enc = (power((double)ch,e,n)); //encrypting the text file
		fprintf(fp2," %lf  ", enc); //saving the encrypted text in the text file
	}
	
	fclose(fp);
	fclose(fp2);

	int check;
	check = rename("z.txt", argv[1]);
			
	if(check == 0) {
		remove(argv[0]);
		printf("ENCRYPTION COMPLETE.\n"); 
	}
	else { 
		printf("ERROR\n");
		fclose(fp);
		fclose(fp2);
	}

	return 0;
}
	
	
