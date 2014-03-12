#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int is_prime( uint64_t p )
{
	int q =2;
	//for (uint64_t q ; q < sqrt(p); q++ )

	while( q*q < p)
	{
		if ( p%q == 0 )
		{
			return 0;
		}
		q++;
	}
	return 1;
}

void is_prime_factor( uint64_t n )
{
	uint64_t i = 2 ;
	printf("%lu : ", n );
	while( i<n)
	{
		while ( !is_prime(i) )
		i++;
		while( n%i == 0 )
		{
			printf( "%lu ",i);
			n /= i;
		}
	i++;
	}
}


int main()
{
	printf("Entree dans Pthread \n");
	FILE* fichier = fopen("bumers.txt");
	if( fichier != NULL )
	{
		int i;
		while(getline(fichier))
		{
			is_prime_factor();
		}
		printf("Fin de Pthread \n");
	}
	return 0;
}
