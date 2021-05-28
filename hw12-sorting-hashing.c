/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("[----- [이 연규] [2018038038] -----]\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a) // 배열 할당 해제.
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) //선택정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //가장 작은 값을 넣을 변수.
		min = a[i]; //정렬되지 않은 첫번째 배열.
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //가장 작은 값을 찾는다.
		{
			if (min > a[j])//첫번째 위치보다 a[j]가 작은 경우.
			{
				min = a[j]; //min을 a[j]로 설정해준다.
				minindex = j;//j를 가장 작은 값으로 지정해준다
			}
		}
		a[minindex] = a[i]; //a[i]의 값을 a[minindex]에 넣어준다.
		a[i] = min; //a[i]에 제일 작은 값을 넣어준다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) // 삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//t에 a[i]의 값을 넣어준다.
		j = i;
		while (a[j-1] > t && j > 0) //이전 값이 현재값보다 크거나, j가 0이 될때 까지 반복
		{
			a[j] = a[j-1]; //a[j]를 a[j-1]방향으로
			j--; //계속 감소 시킨다.
		}
		a[j] = t;//while문을 탈출한 후에 나온 뒤 a[j]값에 t를 insert해준다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //버블 정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])//이전값이 현재 값보다 클 경우.
			{
				t = a[j-1]; //이전값을 t에 넣어준다.
				a[j-1] = a[j]; //현재값을 이전값에 넣어준다.
				a[j] = t; //이전값을 현재값에 넣어준다.
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a) //셸 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//h의 폭을 1/2로 줄여간다.
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //max_array_size 간격에 있는 요소들을 삽입정렬 한다.
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)//현재값이 이전값보다 크거나 k가 h-1보다 작을때까지 반복
				{
					a[k] = a[k-h];//a[k]값에 a[k-h]를 넣는다.
					k -= h; //k에서 h를 빼준값을 k에 넣는다.
				}
				a[k] = v; //a[k]에 v를 insert해준다.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //pivot
		i = -1; //left
		j = n - 1; // right

		while(1)
		{
			while(a[++i] < v); //v보다 작은 key찾기(왼쪽>오른쪽)
			while(a[--j] > v); //v보다 작은 key찾기(오른쪽>왼쪽)

			if (i >= j) break;
			/*a[i]와a[j]를 바꿔준다.*/
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* a[i]와 a[n-1]을 바꿔준다*/
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		/* i를 중심으로 left, right 구분*/
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) { //테이블의 최대크기-1의 값으로 해시코드를 지정해준다.
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht) // 제산 방식 해싱 함수.
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//테이블 안의 값을 모두 -1로 만들어준다.
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //키값 초기화
	int hashcode = -1; //해시코드 초기화
	int index = -1; //인덱스 초기값
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; //a[i]에 있는 값을 key값으로 받는다.
		hashcode = hashCode(key); //해시코드 함수를 이용해 hashcode를 받는다.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //아직 아무것도 안들어가있다면.
		{
			hashtable[hashcode] = key; //테이블 내 버킷에 키값을 지정해준다.
		} else 	{ // 오버플로우가 발생했을 경우.

			index = hashcode; //해시코드를 인덱스에 넣어준다.

			while(hashtable[index] != -1) //빈 버킷을 찾을때 까지 돌리기.
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // 선형 조사법을 통한 순서에 따른 인덱스값 구하기
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //해시테이블에 정해진 버킷주소에 키값을 저장한다.
		}
	}

	return 0;
}

int search(int *ht, int key) // 키값에 대한 주소를 찾는 함수.
{
	int index = hashCode(key); //key값에 대한 해시코드를 인덱스에 넣어준다.

	if(ht[index] == key) //인덱스 안의 값과 키값이 같다면
		return index; // 인덱스를 리턴해준다.

	while(ht[++index] != key) //인덱스 안의 값과 키값이 같을때 까지반복
	{
		index = index % MAX_HASH_TABLE_SIZE; //인덱스를 1씩 늘려주면서 계산해서 인덱스 값을 순서대로 구한다.
	}
	return index; // 인덱스를 리턴해준다.
}



