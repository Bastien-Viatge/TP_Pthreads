#include <stdio.h>
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
	c+= (char *)n +" :";
	uint64_t i = 2 ;
	while( i<n)
	{
		while ( !is_prime(i) )
			i++;
		while( n%i == 0 )
		{
			c+=" "+ (char *)i;
			n /= i;
		}
	if ( n%i != 0 )
		i++;
	}
	printf("%s\n",c);
}

void *pthreadMain()
//Starting function for threads
//call print_prime_factor(i) for each number of the file
{
	//	pthread_t tid = pthread_self( );
		// In order to enter in while : i = 1
		uint64_t i = 1;
		int nbtokens = 1;
		while(nbtokens != 0 && nbtokens != EOF)
		{
			pthread_mutex_lock( &mutex);
			nbtokens=fscanf(fichier,"%lu",&i);
			pthread_mutex_unlock( &mutex);
			print_prime_factor(i);
			printf("nbtokens : %d \n",nbtokens);
		}
	pthread_exit( NULL);
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
		crdu = pthread_create( &pthread1, NULL, pthreadMain, NULL);
		if ( crdu != 0 )
		{	printf("Error : code=%d",crdu);
		exit ( -1);
		}
		crdu = pthread_create( &pthread2,NULL, pthreadMain,NULL);
		if ( crdu != 0 )
		{	printf("Error : code=%d",crdu);
		exit ( -1);
		}

		//------------------------------------------------Join pthread
		crdu = pthread_join(pthread1,NULL);
		if ( crdu != 0 )
		{	printf("Error : code=%d",crdu);
		exit ( -1);
		}
		crdu = pthread_join(pthread2,NULL);
		if ( crdu != 0 )
		{	printf("Erreur : code=%d",crdu);
		exit ( -1);
		}

		//----------------------------------------Destruction du mutex
		crdu = pthread_mutex_destroy( &mutex);
		if ( crdu != 0 )
		{   printf("Erreur : code=%d",crdu);
		exit( -1);
		}

		printf(" Pthread end\n");
		pthread_exit ( NULL );
	}
}
