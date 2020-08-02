#include "io.h"
#include <time.h>

void setMinMax(int* max, int* min);
void disp(int* ip, int min, int num);
void lottery(int* ip, int min, int num);
int isContinue(int* ip, int num);
//-----------------------------------------------------------------------------
//	�T�v�F�G���g���|�C���g
//-----------------------------------------------------------------------------
int main(void)
{
	unsigned int min, max;
	int num;
	int *ip;
	min = 0;
	max = 0;

	/* �ŏ��̃��b�Z�[�W */
	printf("�r���S���J�n���܂��B\n");

	/* �����̎�������� */
	srand((unsigned)time(NULL));

	/* �ŏ��l�ƍő�l�̓��� */
	setMinMax(&max, &min);
	num = max - min + 1;

	/* ���I���ʂ��i�[����z��̏����� */
	ip = (int *)malloc(num * sizeof(int));

	for (int i = 0; i < num; i++)
	{
		ip[i] = 0;
	}

	/* ���I�J�n */
	printf("���I���J�n���܂��B\n");
	while (isContinue(ip,num))
	{
		printf("�iEnter�������Ă��������B�j\n");
		char ch = getc(stdin);
		lottery(ip, min, num);
		disp(ip, min, num);
	}

	/* �I������ */
	printf("�r���S���I�����܂��B");
	printf("�iEnter�������Ă��������B�j\n");
	char ch = getc(stdin);

	free(ip);

	return 0;
}

//-----------------------------------------------------------------------------
//	�T�v�F�ŏ��l�ƍő�l��W�����͂���擾
//�@�����Fmax�@�ő�l�̃|�C���^
//	�����Fmin�@�ŏ��l�̃|�C���^
//-----------------------------------------------------------------------------
void setMinMax(int* max, int* min)
{
	while (1)
	{
		*min = input_uint("�ŏ��l����͂��Ă��������B", NULL, _CRT_INT_MAX, 1);
		*max = input_uint("�ő�l����͂��Ă��������B", NULL, _CRT_INT_MAX, 1);

		if (*min != *max)
		{
			break;
		}
		else
		{
			printf("�ŏ��l�ƍő�l�ɓ����l���ݒ肳��Ă��܂��B�ē��͂��Ă��������B\n");
		}
	}

	if (*min > *max)	/* �ŏ��l�ɑ傫�����������͂��ꂽ�ꍇ�A����ւ��� */
	{
		unsigned int n;
		n = *min;
		*min = *max;
		*max = n;
	}
}

//-----------------------------------------------------------------------------
//	�T�v�F���I���ʂ̌o�߂�\��
//�@�����Fip�@���I���ʂ��i�[���Ă���z��
//	�����Fmin�@�ŏ��l
//	�����Fnum�@���I�Ώۂ̌�
//-----------------------------------------------------------------------------
void disp(int *ip,int min, int num)
{
	int j = 0;
	int k = 0;
	printf("| B | I | N | G | O |\n");
	for (j = 0; j <= num / 5; j++)
	{
		printf(" ");
		for (k = 0; k < 5 && (5 * j + k) < num; k++)
		{
			if (ip[5 * j + k] == 0)
			{
				printf(" _ ");
			}
			else
			{
				printf(" %d ", min + (5 * j) + k);
			}
		}
		printf("\n\r");
	}
}

//-----------------------------------------------------------------------------
//	�T�v�F���I�Ώۂ��烉���_���ɒ��I
//�@�����Fip�@���I���ʂ��i�[���Ă���z��
//	�����Fmin�@�ŏ��l
//	�����Fnum�@���I�Ώۂ̌�
//-----------------------------------------------------------------------------
void lottery(int* ip, int min, int num)
{
	int rnd;
	while (1)
	{
		rnd = min + (int)(rand() * (num - 1.0 + 1.0) / (1.0 + RAND_MAX));
		if (ip[rnd - min] == 0)
		{
			printf("%d���o�܂����B\n", rnd);
			ip[rnd - min]++;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
//	�T�v�F���I���p�����邩����
//�@�����Fip�@���I���ʂ��i�[���Ă���z��
//	�����Fnum�@���I�Ώۂ̌�
//-----------------------------------------------------------------------------
int isContinue(int *ip, int num)
{
	
	for (int i = 0; i < num; i++) {
		if (ip[i] == 0) {
			return 1;
		}
	}
	return 0;
}