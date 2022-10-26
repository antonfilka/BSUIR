#include <iostream>
#include <limits>
#include <pthread.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/sem.h>
using namespace std;

#define COUNT_OF_PRODUSERS_AND_CONSUMERS 100
#define KEY 10
#define COUNT_OF_SEM 5
#define MSGSZ 102

vector<bool> producersTerm_fl;
vector<bool> consumersTerm_fl;


union semun arg;

struct m_msg
{
	long type;
	char text[MSGSZ];
};

char* randStr();
void *threadProducer(void *thrParam);
void *threadConsumer(void *thrParam);

int main() {
	unsigned int cCounter = 0, pCounter = 0;
	key_t key = KEY; 
	int msqId, semId;

	producersTerm_fl.reserve(COUNT_OF_PRODUSERS_AND_CONSUMERS);
	consumersTerm_fl.reserve(COUNT_OF_PRODUSERS_AND_CONSUMERS);
	
	for(int i = 0; i < COUNT_OF_PRODUSERS_AND_CONSUMERS; i++)
	{
		producersTerm_fl[i] = false;
		consumersTerm_fl[i] = false;
	}	

	if((semId = semget(key, COUNT_OF_SEM, (IPC_CREAT | 0666))) == -1)
	{
		cout << endl<< endl<<"Can't get semId" << endl << "Error: "<< strerror(errno) << endl;
		exit(errno);
	}
	if((msqId = msgget(key, (IPC_CREAT | 0666))) == -1)
	{
		cout << endl<< endl<<"Can't get msqId" << endl << "Error: "<< strerror(errno) << endl;
		exit(errno);
	}

	arg.array = new unsigned short[COUNT_OF_SEM];
	arg.array[0] = 1;  		// бинареый мьютекс
	arg.array[1] = 100;		// свободная память (переполнение)
	arg.array[2] = 0;		// элементы в наличии
	arg.array[3] = 0;		// кол-во отправленных собщений
	arg.array[4] = 0;		// кол-во получ сообщений

	if(semctl(semId, 0, SETALL, arg) == -1)
	{
		cout << endl<< endl<<"Can't set semaphores value" << endl << "Error: "<< strerror(errno) << endl;
		exit(errno);
	}
	delete []arg.array;
	
	char c;	
	do {
		putchar('$');
		 c = cin.get();
        if (cin.eof())
        {
            cin.clear();
            continue;
        }
		switch(c) {
			case 'p': 
			{
				if(pCounter == COUNT_OF_PRODUSERS_AND_CONSUMERS)
				{
					cout << "Max count of produsers" << endl;
					break;
				}
				pthread_t thread;
				int *tempId = new int;
				*tempId = pCounter;

				if (pthread_create(&thread, NULL, threadProducer, tempId))
            	{
            	    cout << endl << "Unable to create a thread" << endl<<"Error : "<<strerror(errno)<<endl;
            	    exit(errno);
        	    }
    	
				while(producersTerm_fl[pCounter]);
				cout << "Producer_"<<pCounter<<" is created" <<endl;
				pCounter++;
				break;
			}
			case 'c': 
			{
				if(cCounter == COUNT_OF_PRODUSERS_AND_CONSUMERS)
				{
					cout << "Max count of consumers" << endl;
					break;
				}
				pthread_t thread;
				int *tempId = new int;
				*tempId = cCounter;

				if (pthread_create(&thread, NULL, threadConsumer, tempId))
            	{
            	    cout << endl << "Unable to create a thread" << endl<<"Error : "<<strerror(errno)<<endl;
            	    exit(errno);
        	    }
    	       
				while(consumersTerm_fl[cCounter]);
				cout << "Consumer_"<< cCounter <<" is created" <<endl;
				cCounter++;
				break;
			}
			case '-':
	 			c = cin.get();
        		if (cin.eof() || (c != 'p' && c != 'c'))
        		{
            		cin.clear();
					cout << "Unknown comand. "
                 		 << "Please use only 'p', 'c', '-p', '-c'" << endl;
            		break;
        		}
				if(c == 'p')
				{
					if (pCounter == 0) {
						cout << "Producers amount: 0" << endl;
						break;
					}
					pCounter--;
					producersTerm_fl[pCounter] = true;
					cout << "Producer : " << pCounter << " was deleted" << endl;
				}
				else
				{
					if (cCounter == 0) {
						cout << "Consumers amount: 0" << endl;
						break;
					}
					cCounter--;
					consumersTerm_fl[cCounter] = true;
					cout << "Consumer : " << cCounter << " was deleted" << endl;
				}
				break;
			case 'q':
				if(-1 == semctl(semId, 0, IPC_RMID))
				{
					cout << endl<< endl<<"Can't remove semId" << endl << "Error: "<< strerror(errno) << endl;
					exit(errno);
				}
				if(-1 == msgctl(msqId, IPC_RMID, 0))
				{
					cout << endl<< endl<<"Can't remove msqId" << endl << "Error: "<< strerror(errno) << endl;
					exit(errno);
				}
				exit(0); 
			default:
				 cout << "Unknown comand. "<< endl;
				break;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while(c);
}


void *threadProducer(void *thrParam)
{
	int *id = (int *)thrParam;
	int semId, msqId;
	key_t key = KEY;
    m_msg buffer;
	timespec tw = {5,0};
    timespec tr;
	sembuf sops[3];

	srand(time(NULL));

	if(-1 == (semId = semget(key, 0, IPC_CREAT | 0666)))
	{
		cout << endl<< endl<<"Can't get semId" << endl << "Error: "<< strerror(errno);
		exit(errno);
	}
	if(-1 == (msqId = msgget(key, IPC_CREAT  | 0666)))
	{
		cout << endl<< endl<<"Can't get msqId" << endl << "Error: "<< strerror(errno);
		exit(errno);
	}

	buffer.type = 1;
	while (!producersTerm_fl[*id]) {
		nanosleep(&tw, &tr);

		for(int i = 0; i < MSGSZ; i++)
			buffer.text[i] = 0;
		strcpy(buffer.text, randStr());

		sops[0].sem_num = 1;	
		sops[0].sem_op = -1;

		sops[1].sem_num = 0;	
		sops[1].sem_op = -1;

		semop(semId, sops, 2);		

		if (msgsnd(msqId, &buffer, MSGSZ, 0)) 
			pthread_exit(0);
			
		sops[0].sem_num = 2;	
		sops[0].sem_op =  1;

		sops[1].sem_num = 3;	
		sops[1].sem_op =  1;
			
		semop(semId, sops, 2);

		cout << endl << endl << "Name: " << *id << endl 
							 << "TID : "<< pthread_self() << endl
							 << "Number messages: " << semctl(semId, 3, GETVAL) << endl 
							 << "Text: " << buffer.text << endl;
							 
			
		sops[0].sem_num = 0;	
		sops[0].sem_op = 1;

		
		semop(semId, sops, 1);
	}
	producersTerm_fl[*id]= false;
     pthread_exit(0);
}
void *threadConsumer(void *thrParam)
{
	int *id = (int *)thrParam;
	int semId, msqId;
	int recivedMsgCounter = 0;
	key_t key = KEY;
    m_msg buffer;
    size_t buf_length;
	timespec tw = {5,0};
    timespec tr;
	sembuf sops[3];

	srand(time(NULL));
	
	if(-1 == (semId = semget(key, 0, IPC_CREAT | 0666)))
	{
		cout << endl<< endl<<"Can't get semId" << endl << "Error: "<< strerror(errno);
		exit(errno);
	}
	if(-1 == (msqId = msgget(key, IPC_CREAT  | 0666)))
	{
		cout << endl<< endl<<"Can't get msqId" << endl << "Error: "<< strerror(errno);
		exit(errno);
	}

	while(!consumersTerm_fl[*id]) {	
		nanosleep(&tw, &tr);

		sops[0].sem_num = 2;		
		sops[0].sem_op = -1;


		sops[1].sem_num = 0;		
		sops[1].sem_op = -1;


		semop(semId, sops, 2);

		if (-1 == msgrcv(msqId, &buffer, MSGSZ, 1, 0))
			pthread_exit(0);

		sops[0].sem_num = 1;		
		sops[0].sem_op = -1;


		sops[1].sem_num = 4;		
		sops[1].sem_op = 1;

		semop(semId, sops, 2);

		cout << endl << endl << "Name: " << *id << endl 
							 << "TID: "<< pthread_self() << endl
							 << "Number of recived messages: " << semctl(semId, 4, GETVAL) << endl 
							 << "Text: " << buffer.text << endl;
		 					 
			
		sops[0].sem_num = 0;	
		sops[0].sem_op = 1;
		
		semop(semId, sops, 1);
	}
	consumersTerm_fl[*id]= false;
    pthread_exit(0);
}

char* randStr() {

	size_t size = rand() % (MSGSZ-2) + 2;
	char* str = new char[size];

	size_t i = 0;
	for (i = 0; i < size; i++) {
		str[i] = (char)(rand()%26 + 97);
	}
	str[i] = '\0';
	return str;
}