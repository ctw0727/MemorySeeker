/*
1. �޸𸮿��� ã�� ���� Ÿ�� �Է¹ޱ�
2. 10���� ������ ������ �̸� 8�ڸ� 16������ �ٲ� �ش� �ּ� �޸� Ž�� 
3. �޸� ���� ã�� ���� ������ ���ڿ� ���߹迭�� ���� �ּ� 10~20������ ���� �� ��� (ã�� ���� ����)
4. ��ġ�ϴ� �޸� ���� �ִ� �������� ���� Ž���� ��� �ʰ����� �������� �ʰ� �Ϲ��� ��� ���� �ִ밹���� �ʰ��Ѵٴ� ��� ��� 

1. ���� �̾ ã�� ������ �ش� ��ġ�� ���� ���� �Է��ϸ� �ش� �޸𸮿� �Է��� ���� ���� �õ� 
2. �ڷ����� �ٸ��ų� ������ ũ�⸦ �ʰ��� �� ��ü�����Ͽ� ���� �������� �ʰ� ��� ���
3. ���� �����ص� �ٺ��� ������ ���� �� ���� �ҹ��ڿ� ���ڷ� �̷���� 6�ڸ� ������ Ȯ�ι��� �Է��ؾ� ������ ���� �������ֵ��� ��. 

+++++
Ư�� ���α׷����� ĳ������? �޸𸮸��� �˻��� �� �ִٸ� ���� �� ����. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

static unsigned int UINTMAX = 4294967295UL; // unsigned int�� �ִ밪 

void MainLoop(); // ��ɾ��� �Է°� ���α׷��� �������� ���Ḧ ����ϴ� �Լ� 
void print_help(); // ��밡���� ��� ��ɾ�� ������ ���
void seek_memory(char*); // �޸𸮿��� �Էµ� Ư�� ���� ã�� �ּҸ� ����ϴ� �Լ� 
void test_seek_memory(char*); // ���ӵ� 10���� �޸� �ּҿ� �̿� ����ִ� ���� ����ϴ� �Լ� 
const char* ten_to_sixteen(unsigned int); // 10���� ������ �޸� �ּ� ����� ���ڿ����� ��ȯ�� ��ȯ�ϴ� �Լ� 


// ��밡���� ��� ��ɾ�� ������ ����ϴ� �Լ� 
void print_help(){
	
	printf("help : show all the commands we have\n");
	printf("test_sixteen (unsigned int) : test transforming decimal to hexadecimal\n");
	printf("seek_all_memory (type) (data) : find memories with inputed data. type should be int or double\n");
	printf("seek_ten_memory (type) : seek 10 memories and print. type should be int or double\n");
}

int main(void){
	
	MainLoop();
	
	return 0;
}


// ��ɾ��� �Է°� ���α׷��� �������� ���Ḧ ����ϴ� �Լ� 
void MainLoop(){
	
	bool End = false; // �ݺ��� Ż������ 
	char Input[30] = {NULL}; // ��ɾ �����ϴ� ���ڿ� 
	
	do {
		scanf("%s", Input);
		
		
		if (strcmp(Input, "help") == 0){
			
			print_help();
		}
		
		
		if (strcmp(Input, "test_sixteen") == 0){
			
			unsigned int in;
			scanf("%u", &in);
			
			printf("\ninputed value was %u\n\n", in);
			printf("%s", ten_to_sixteen(in));
		}
		
		/*
		if (strcmp(Input, "seek_ten_memory") == 0){
			
			scanf("%s", Input);
			
			char* Buffer = Input;
			test_seek_memory(Buffer);
		}
		*/
		
		if (strcmp(Input, "seek_all_memory") == 0){
			
			scanf("%s", Input);
			
			char* Buffer = Input;
			seek_memory(Buffer);
		}
		
		printf("//////////////\n\n");
		
	} while(End != true);
}


	// �޸𸮿��� ���� �ҷ����� ����� �׽�Ʈ�ϰ��� ������� �Լ� 
	// �̹� �޸𸮿��� ���� �ҷ����� ����� �˾Ƴ� �� �̻� ������� �ʴ� �Լ���
/*
void test_seek_memory(char* in){
	
	//printf("\ninputed type value was %s\n\n", in);
	
	if (strcmp(in, "int") == 0){
		printf("It's int. seeking 10 memories\n");
		
		int data, pool = 1;
		
		int* Address = ((int*)0x00000000);
		data = *Address;
		printf(" %d\t%d is found on %s\n", pool, data, Address);
	}
	
	// intŸ�Ը��� ���� �����Ͽ��� ������ �ּ�ó�� 
	/*else if (strcmp(in, "double") == 0){
		printf("It's double.");
		
		double data;
		
		unsigned int i = 0;
		char* Address = (char*)malloc(sizeof(char) * 8);
		do{
			
			strcpy(Address, ten_to_sixteen(i));
			data = *Address;
			
			printf("%lf", data);
		}while(i++ < UINTMAX);
	}
	
	
	else{
		printf("data type error");
	}
	
}
*/

	// �޸𸮸� ������ �Լ� 
void seek_memory(char* in){
	
	// �׽�Ʈ�� ��ɾ� : seek_all_memory int 10
	
	if (strcmp(in, "int") == 0){
		
		int finding;
		scanf("%d", &finding); // ã������ �� ���� 
		
		int data = 0; // �޸� ���� �����͸� �����ϱ� ���� ���� 
		int count = 0; // ����� �����޸��� ���� ����, 8680��° Ȥ�� �� �ڷδ� �����޸𸮸� ���(?)�� �� ���� 
		int pool = 1; // ã������ ���� ��ġ�ϴ� ���� ������ ���� ���� 
		bool check = false; // �޸𸮿��� NULL�� ã�Ҵٴ� �ȳ����� �� ���� ���� �ϴ� ���� 
		char Address[11]; // ǥ��� ���ڿ� �ּ� 
		
		char* i = (char*)malloc(sizeof(int)); // char*������ ũ��� int�� �����޸� �Ҵ�
		// ������ ������ �ڷ����� ũ�⸸ŭ�� �̷������ ������ char* ��� 
		
		//bool check = false;
		
		unsigned int* dataAdd = NULL;
		
			// �޸� ���� ���� �ּҸ� 0x00000000���� ������ߴ� �õ�
			// �ڵ�� �����۵������� ���α׷��� ������ �� �ִ� �޸� ������ �Ѿ ������ ���Ḧ ���� 
		/*do{
			//printf("value is %d (%p)\n", i, i);
			
			if ((unsigned int)i == 0){
				printf("value is %d, ending loop\n", i);
				break;
			}
			
			dataAdd = (unsigned int*)i; //get address
				
			if (*dataAdd!=NULL){
				printf("DATA WAS NOT NULL\n");
				data = (int)*dataAdd;
				printf(" %d is found, %p\n\n", data, dataAdd);
			}
		}while((unsigned int)i-- > 0);*/
		
		do{
			if (++count >= 8680){
				printf("\n\n [WARNING] can\'t seek more memory due to it\'s over 8680\'s\n\n");
				count = 0;
				break;
			}
			
			strcpy(Address, ten_to_sixteen((unsigned int)i)); // ǥ��� ���ڿ����� �ּ� ���� 
			
			dataAdd = (unsigned int*)i; // �����ּ� ���� 
			
			if (*dataAdd!=NULL){ // �޸� ���� ���� NULL���� ���� 
				
				printf("DATA WAS NOT NULL\n");
				check = false;
				
				data = (int)*dataAdd;
			}
			else{
				
				if (check == false){
					printf("   data was NULL\n\n");
					check = true;
				}
				continue;
			}
			
				// �ٷ� �Ʒ� ����Ʈ���� �ּ�ó���� �� ������ ���α׷��� �����۵����� ����
			//printf(" %d is found on %s\n\n", data, Address);
			//printf(" DEBUGGING (%d, %p) (%s, %p)\n\n", dataAdd, dataAdd, Address, i);
			
			// ã���ִ� �����Ϳ� ���� ����� ��(���� ��)�� ã�� �� �ּҿ� �Բ� ��ȯ
			// 20�� �̻��� ���� ã���� ���� Ż�� 
			if (data == finding){
				if (pool <= 20){
					printf(" %d\t%d is found on %s\n", pool, data, Address);
					printf(" DEBUGGING (%d, %p) (%s, %p)\n\n", dataAdd, dataAdd, Address, i);
					pool++;
				}
				else{
					printf("data is too many to find all (more than 20)\n");
					break;
				}
			}
			
		}while ( (unsigned int)++i <= UINTMAX );
		
		free(i); // �����޸� �Ҵ� ���� 
	}
	
	else{
		printf("data type error");
	}
	
}


// �������� 16���� �ּҰ� ���ڿ����� ����� ��ȯ�ϴ� �Լ�
// �ּ�ó���� �κ��� ��� �ڵ� Ȯ�ο� 
const char* ten_to_sixteen(unsigned int ten){
	
	char sixteen[11] = {'0','x','0','0','0','0','0','0','0','0','\0'};
	int i, mem;
	
	for(i = 0; i < 8; i++){
		
		//printf("loop is starting, starting loop %d\n", i+1);
		
		mem = ten % 16;
		ten = ten / 16;
		
		if (mem <= 9){
			//printf("mem was smaller then 10 (%d), looped %d times\n\n", mem, i+1);
			mem += 48;
			sixteen[9-i] = mem;
		}
		else{
			//printf("mem was bigger then 9 (%d), looped %d times\n\n", mem, i+1);
			mem += 55;
			sixteen[9-i] = mem;
		}
		
		if (ten == 0){
			//printf("input been 0, looped %d times\n\n", i+1);
			break;
		}
	}
	
	//printf("returning result (%s), looped %d times\n", sixteen, i+1);
	char* res = sixteen;
	return res;
}
