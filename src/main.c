#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//static 	FILE* fichier;

/*int is_prime( uint64_t p )
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
}*/

void print_prime_factor( uint64_t n )
{
	
	printf("%lu :",n);
	uint64_t i ;
	
	uint64_t racine =(uint64_t)sqrt(n);
	
	for( i= 2 ; i<=racine ; i++)
	{
		if( n%i == 0 )
		{
			
			//c=strcat(c," ");
			//c=strcat(c,itoa(i,c,10));
			printf(" %lu",i);
			n /= i;
			i--;
			
		}
		
		
	}
	printf(" %lu \n",n);
}


/*
void pthreadMain()

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
	
	
	
	

	//printf("nbtokens : %d \n",nbtokens);
	//pthread_exit( (void *)&nbtokens);
}//Fin de pthread Main


/*
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
>>>>>>> cbc81897c10f6326699bdd915a4e749ddc7a6d02
	return 0;
}
* */

