/*
1. 메모리에서 찾을 값과 타입 입력받기
2. 10진수 루프를 돌리고 이를 8자리 16진수로 바꿔 해당 주소 메모리 탐색 
3. 메모리 값과 찾을 값이 같으면 문자열 이중배열에 값과 주소 10~20개까지 저장 및 출력 (찾은 순번 포함)
4. 일치하는 메모리 값이 최대 갯수보다 많이 탐색될 경우 초과분은 저장하지 않고 일반적 출력 이후 최대갯수를 초과한다는 경고문 출력 

1. 위에 이어서 찾은 순번과 해당 위치에 넣을 값을 입력하면 해당 메모리에 입력한 값을 저장 시도 
2. 자료형이 다르거나 데이터 크기를 초과할 시 자체판정하여 값을 저장하지 않고 경고문 출력
3. 값을 저장해도 근본적 문제는 없을 시 영어 소문자와 숫자로 이루어진 6자리 임의의 확인문을 입력해야 실제로 값을 저장해주도록 함. 

+++++
특정 프로그램에서 캐싱중인? 메모리만을 검색할 수 있다면 좋을 것 같음. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

static unsigned int UINTMAX = 4294967295UL; // unsigned int의 최대값 

void MainLoop(); // 명령어의 입력과 프로그램의 정상적인 종료를 담당하는 함수 
void print_help(); // 사용가능한 모든 명령어와 설명을 출력
void seek_memory(char*); // 메모리에서 입력된 특정 값을 찾고 주소를 출력하는 함수 
void test_seek_memory(char*); // 연속된 10개의 메모리 주소와 이에 들어있는 값을 출력하는 함수 
const char* ten_to_sixteen(unsigned int); // 10진수 정수를 메모리 주소 양식의 문자열으로 변환해 반환하는 함수 


// 사용가능한 모든 명령어와 설명을 출력하는 함수 
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


// 명령어의 입력과 프로그램의 정상적인 종료를 담당하는 함수 
void MainLoop(){
	
	bool End = false; // 반복문 탈출조건 
	char Input[30] = {NULL}; // 명령어를 저장하는 문자열 
	
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


	// 메모리에서 값을 불러오는 방법을 테스트하고자 만들었던 함수 
	// 이미 메모리에서 값을 불러오는 방법을 알아내 더 이상 사용하지 않는 함수임
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
	
	// int타입만을 먼저 수정하였기 때문에 주석처리 
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

	// 메모리를 뒤지는 함수 
void seek_memory(char* in){
	
	// 테스트용 명령어 : seek_all_memory int 10
	
	if (strcmp(in, "int") == 0){
		
		int finding;
		scanf("%d", &finding); // 찾으려는 값 저장 
		
		int data = 0; // 메모리 안의 데이터를 저장하기 위한 변수 
		int count = 0; // 사용한 동적메모리의 갯수 저장, 8680번째 혹은 그 뒤로는 동적메모리를 사용(?)할 수 없음 
		int pool = 1; // 찾으려는 값과 일치하는 값의 갯수를 세는 변수 
		bool check = false; // 메모리에서 NULL을 찾았다는 안내문을 한 번만 띄우게 하는 변수 
		char Address[11]; // 표기용 문자열 주소 
		
		char* i = (char*)malloc(sizeof(int)); // char*이지만 크기는 int인 동적메모리 할당
		// 포인터 연산은 자료형의 크기만큼씩 이루어지기 때문에 char* 사용 
		
		//bool check = false;
		
		unsigned int* dataAdd = NULL;
		
			// 메모리 참조 시작 주소를 0x00000000으로 만들려했던 시도
			// 코드는 정상작동하지만 프로그램이 참조할 수 있는 메모리 갯수를 넘어가 비정상 종료를 유발 
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
			
			strcpy(Address, ten_to_sixteen((unsigned int)i)); // 표기용 문자열으로 주소 저장 
			
			dataAdd = (unsigned int*)i; // 실제주소 저장 
			
			if (*dataAdd!=NULL){ // 메모리 안의 값이 NULL인지 판정 
				
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
			
				// 바로 아래 프린트문을 주석처리할 시 왜인지 프로그램이 정상작동하지 않음
			//printf(" %d is found on %s\n\n", data, Address);
			//printf(" DEBUGGING (%d, %p) (%s, %p)\n\n", dataAdd, dataAdd, Address, i);
			
			// 찾고있는 데이터와 가장 비슷한 값(같은 값)을 찾을 시 주소와 함께 반환
			// 20개 이상의 값을 찾으면 루프 탈출 
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
		
		free(i); // 동적메모리 할당 해제 
	}
	
	else{
		printf("data type error");
	}
	
}


// 십진수를 16진수 주소값 문자열으로 만들어 반환하는 함수
// 주석처리된 부분은 모두 코드 확인용 
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
