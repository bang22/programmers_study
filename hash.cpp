#include <cstdio>
#include <cstring>



#define KEY_SIZE 10
#define TABLE_SIZE 13


#define empty(e) (strlen(e.key)==0)
#define equal(e1,e2) (!strcmp(e1.key,e2.key))



typedef struct//해시 테이블 요소
{
	bool used;
	char key[KEY_SIZE];

	//밑에 뭐든지 값을 넣으면 되는 부분임
	int value;

} element;

element hash_table[TABLE_SIZE];//해시 테이블


void initTable(element ht[])//해시 테이블 초기화
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = NULL;
	}
}

int transform(char* key)//문자로 된 탐색 키를 숫자로 변환
{
	int number = 0;
	while (*key)//그냥 문자 하나하나 다 합침
		number += *key++;

	return number;
}

int hash_func(char* key)//제산 함수를 사용한 해싱 함수
{
	return transform(key) % TABLE_SIZE;
}



void hash_lp_add(element item, element ht[])//선형조사법을 이용한 테이블 키 삽입
{
	int i, hash_value;
	hash_value = i = hash_func(item.key);

	while (!empty(ht[i]))
	{
		if (equal(item, ht[i]))
		{
			fprintf(stderr, "탐색키가 중복되었습니다\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;

		if (i == hash_value)
		{
			fprintf(stderr, "테이블이 꽉찼어요\n");
			return;
		}
	}
	ht[i] = item;
	ht[i].used = true;
}

void hash_lp_search(char key[], element ht[])//선형조사법을 이용한 테이블 키 검색
{
	int i, hash_value;
	hash_value = i = hash_func(key);

	while (!empty(ht[i]) || ht[i].used)
	{
		if (!strcmp(key, ht[i].key))
		{
			fprintf(stderr, "탐색 성공 : 위치 = %d\n",i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value)
		{
			fprintf(stderr, "테이블에 그딴건 없어요\n");
			return;
		}
	}
	fprintf(stderr, "테이블에 그딴건 없어요\n");
}


void hash_lp_delete(char key[], element ht[])//선형조사법을 이용한 테이블 키 삭제
{
	int i, hash_value;
	hash_value = i = hash_func(key);

	while (!empty(ht[i]) || ht[i].used)
	{
		if (!strcmp(key, ht[i].key))
		{
			fprintf(stderr, "삭제 성공 : 위치 = %d\n", i);
			strcpy_s(ht[i].key, "\0");

			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value)
		{
			fprintf(stderr, "테이블에 그딴건 없어요\n");
			return;
		}
	}
	fprintf(stderr, "테이블에 그딴건 없어요\n");
}


void hash_lp_print(element ht[])//테이블에 있는거 출력
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		printf("[%d]  %s  \n", i, ht[i].key);
	}
}

void main()
{
	initTable(hash_table);

	element tmp;

	int op;

	while (true)
	{
		printf("원하는 연산 입력 부탁 1:입력 2:탐색 3:삭제  0:종료  =   ");
		scanf_s("%d",&op);

		if (op == 0)return;

		printf("키를 입력해주세요      =   ");
		scanf_s("%s", tmp.key, KEY_SIZE);

		printf("\n\n");

		if (op == 1)
			hash_lp_add(tmp, hash_table);
		else if (op == 2)
			hash_lp_search(tmp.key, hash_table);
		else if (op == 3)
			hash_lp_delete(tmp.key, hash_table);

		hash_lp_print(hash_table);
	}
}