#include <cstdio>
#include <cstring>



#define KEY_SIZE 10
#define TABLE_SIZE 13


#define empty(e) (strlen(e.key)==0)
#define equal(e1,e2) (!strcmp(e1.key,e2.key))



typedef struct//�ؽ� ���̺� ���
{
	bool used;
	char key[KEY_SIZE];

	//�ؿ� ������ ���� ������ �Ǵ� �κ���
	int value;

} element;

element hash_table[TABLE_SIZE];//�ؽ� ���̺�


void initTable(element ht[])//�ؽ� ���̺� �ʱ�ȭ
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = NULL;
	}
}

int transform(char* key)//���ڷ� �� Ž�� Ű�� ���ڷ� ��ȯ
{
	int number = 0;
	while (*key)//�׳� ���� �ϳ��ϳ� �� ��ħ
		number += *key++;

	return number;
}

int hash_func(char* key)//���� �Լ��� ����� �ؽ� �Լ�
{
	return transform(key) % TABLE_SIZE;
}



void hash_lp_add(element item, element ht[])//����������� �̿��� ���̺� Ű ����
{
	int i, hash_value;
	hash_value = i = hash_func(item.key);

	while (!empty(ht[i]))
	{
		if (equal(item, ht[i]))
		{
			fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;

		if (i == hash_value)
		{
			fprintf(stderr, "���̺��� ��á���\n");
			return;
		}
	}
	ht[i] = item;
	ht[i].used = true;
}

void hash_lp_search(char key[], element ht[])//����������� �̿��� ���̺� Ű �˻�
{
	int i, hash_value;
	hash_value = i = hash_func(key);

	while (!empty(ht[i]) || ht[i].used)
	{
		if (!strcmp(key, ht[i].key))
		{
			fprintf(stderr, "Ž�� ���� : ��ġ = %d\n",i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value)
		{
			fprintf(stderr, "���̺� �׵��� �����\n");
			return;
		}
	}
	fprintf(stderr, "���̺� �׵��� �����\n");
}


void hash_lp_delete(char key[], element ht[])//����������� �̿��� ���̺� Ű ����
{
	int i, hash_value;
	hash_value = i = hash_func(key);

	while (!empty(ht[i]) || ht[i].used)
	{
		if (!strcmp(key, ht[i].key))
		{
			fprintf(stderr, "���� ���� : ��ġ = %d\n", i);
			strcpy_s(ht[i].key, "\0");

			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value)
		{
			fprintf(stderr, "���̺� �׵��� �����\n");
			return;
		}
	}
	fprintf(stderr, "���̺� �׵��� �����\n");
}


void hash_lp_print(element ht[])//���̺� �ִ°� ���
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
		printf("���ϴ� ���� �Է� ��Ź 1:�Է� 2:Ž�� 3:����  0:����  =   ");
		scanf_s("%d",&op);

		if (op == 0)return;

		printf("Ű�� �Է����ּ���      =   ");
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