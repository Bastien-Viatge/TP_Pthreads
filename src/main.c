#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static 	FILE* fichier;

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
	if ( n !=1)
		printf(" %lu \n",n);
}




void *pthreadMain()

//Starting function for threads
//call print_prime_factor(i) for each number of the file
{
	//pthread_t tid = pthread_self( );

	uint64_t nbreLu = 1;
	int nbtokens = 1;
	while (nbtokens != 0 && nbtokens != EOF) 
	{ 
		pthread_mutex_lock( &mutex);
		nbtokens=fscanf(fichier,"%lu",&nbreLu);
		pthread_mutex_unlock( &mutex);
		print_prime_factor(nbreLu);

	}
	pthread_exit( NULL);
}



/*
int main() //Question 3
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
	
}//Fin de pthread Main

*/


void *pthreadMainBoucle(void *i)
{
	uint64_t number = (uint64_t)i;
	print_prime_factor(number);
	pthread_exit( NULL);
}



int main() { 
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
		{
			printf("Error : code=%d",crdu); 
			exit ( -1); 
		}
		crdu = pthread_create( &pthread2, NULL, pthreadMain, NULL);
		if ( crdu != 0 ) 
		{ 
			printf("Error : code=%d",crdu);
			exit ( -1);
		} 
		crdu = pthread_join(pthread1, NULL);
		if ( crdu != 0 ) {
			printf("Error : code=%d",crdu);
			exit ( -1);
		} 
		crdu = pthread_join(pthread2, NULL);
		if ( crdu != 0 ) 
		{ 
			printf("Erreur : code=%d",crdu);
			exit ( -1);
		}
	} 
	/*
	//------------------------------------------------Join pthread 
	//---------------------------------------Destruction du mutex 
	crdu = pthread_mutex_destroy( &mutex);
	if ( crdu != 0 ) 
	{ printf("Erreur : code=%d",crdu); exit( -1); } printf(" Pthread end\n"); } */
 
	
	pthread_exit( NULL);
}


