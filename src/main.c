#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static 	FILE* fichier;

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
	char * c;
	c = strcat((char *)n," :");
	uint64_t i = 2 ;
	while( i<n)
	{
		while ( !is_prime(i) )
			i++;
		while( n%i == 0 )
		{
			c=strcat(c," ");
			c=strcat(c,(char *)i);
			n /= i;
		}
	if ( n%i != 0 )
		i++;
	}
	printf("%s\n",c);
}

void *pthreadMainBoucle()
//Starting function for threads
//call print_prime_factor(i) for each number of the file
{
		pthread_t tid = pthread_self( );

		uint64_t i = 1;
		int nbtokens = 1;

			pthread_mutex_lock( &mutex);
			nbtokens=fscanf(fichier,"%lu",&i);
			pthread_mutex_unlock( &mutex);
			print_prime_factor(i);
			printf("nbtokens : %d \n",nbtokens);
	pthread_exit( (void *)&nbtokens);
}//Fin de pthread Main

int main()

{
	//Open "numbers.txt"
	fichier = fopen("numbers.txt","r+");
	if( fichier != NULL )
	{
		pthread_t pthread1,pthread2;
		int crdu;

		//--------------------------------------Initialisation du mutex
		pthread_mutex_init(&mutex,NULL);

		//---------------------------------------------Creating pthread
		// In order to enter in while : nbtoki = 1
		int * nbtok1 = 1;
		int * nbtok2 = 1;
		while(*nbtok1 >0 && *nbtok2>0)
		{
			crdu = pthread_create( &pthread1, NULL, pthreadMainBoucle, NULL);
			if ( crdu != 0 )
			{	printf("Error : code=%d",crdu);
			exit ( -1);
			}
			crdu = pthread_create( &pthread2, NULL, pthreadMainBoucle,NULL);
			if ( crdu != 0 )
			{	printf("Error : code=%d",crdu);
			exit ( -1);
			}

			//------------------------------------------------Join pthread
			crdu = pthread_join(pthread1,(int *)nbtok1);
			if ( crdu != 0 )
			{	printf("Error : code=%d",crdu);
			exit ( -1);
			}
			crdu = pthread_join(pthread2,(int *)nbtok2);
			if ( crdu != 0 )
			{	printf("Erreur : code=%d",crdu);
			exit ( -1);
			}
		}
		//----------------------------------------Destruction du mutex
		crdu = pthread_mutex_destroy( &mutex);
		if ( crdu != 0 )
		{   printf("Erreur : code=%d",crdu);
		exit( -1);
		}

		printf(" Pthread end\n");
	}
	return 0;
}
