#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

int is_prime( uint64_t p )
{
	uint64_t q = 2;
	for (q = 2; q < (uint64_t)sqrt(p); q++ )
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

int main()
{
	pthread_t pthread1,pthread2;

//	pthread_mutex_init(pthread1,NULL);
//	pthread_mutex_init(pthread2,NULL);
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
			pthread_create(&pthread1,NULL, print_prime_factor,i);
			pthread_create(&pthread1,NULL, print_prime_factor,j);
			pthread_join(pthread1,NULL);
			pthread_join(pthread2,NULL);
		}
	}
		printf(" Pthread end\n");


	return 0;
}
