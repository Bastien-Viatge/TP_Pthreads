#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

int is_prime( uint64_t p )
{
	uint64_t q = 2;
	for (q = 2; q < (uint64_t)sqrt(p); q++ )  //comparaison jusqu'à la racine seulement
	{
		if ( p%q == 0 )
		{
			return 0;
		}
	}
	return 1;
}

void print_prime_factor( uint64_t n )
{
	uint64_t i = 2 ;
	printf("%lu : ", n );
	while( i<n)
	{
		while ( !is_prime(i) )
		{
			i++;
		}
		while( n%i == 0 )
		{
			printf( "%lu ",i);
			n /= i;
		}
	i++;
	}
	printf("\n");
}

/*
void pthreadMain()
//Starting function for threads
{
	FILE* fichier = fopen("numbers.txt","r+");
	if( fichier != NULL )
	{
		// In order to enter in while =1
		uint64_t i = 1;
		uint64_t j = 1;
		int nbtokens = 1;
		while(nbtokens != 0 && nbtokens != EOF)
		{
			nbtokens=fscanf(fichier,"%lu %lu",&i,&j);
			print_prime_factor(i);
		}
	}
}
*/


int main()
{
	FILE* fichier = fopen("numbers.txt","r+");
	if( fichier != NULL )
	{
		// In order to enter in while =1
		uint64_t i = 1;
		int nbtokens;
		//int64_t j = 1;
		nbtokens=fscanf(fichier,"%lu",&i);
		while(nbtokens != 0 && nbtokens != EOF)
		{
			printf("nbtokens %d : ",nbtokens);
			print_prime_factor(i);
			nbtokens=fscanf(fichier,"%lu",&i);

		}
	}
	
	/*
	int crdu;
	pthread_t = tid1,tid2;
	
	
	
	
	*/
	
	
	
	
	return 0;
}
