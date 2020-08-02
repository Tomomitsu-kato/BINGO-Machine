#include "io.h"
#include <time.h>

void setMinMax(int* max, int* min);
void disp(int* ip, int min, int num);
void lottery(int* ip, int min, int num);
int isContinue(int* ip, int num);
//-----------------------------------------------------------------------------
//	概要：エントリポイント
//-----------------------------------------------------------------------------
int main(void)
{
	unsigned int min, max;
	int num;
	int *ip;
	min = 0;
	max = 0;

	/* 最初のメッセージ */
	printf("ビンゴを開始します。\n");

	/* 乱数の種を初期化 */
	srand((unsigned)time(NULL));

	/* 最小値と最大値の入力 */
	setMinMax(&max, &min);
	num = max - min + 1;

	/* 抽選結果を格納する配列の初期化 */
	ip = (int *)malloc(num * sizeof(int));

	for (int i = 0; i < num; i++)
	{
		ip[i] = 0;
	}

	/* 抽選開始 */
	printf("抽選を開始します。\n");
	while (isContinue(ip,num))
	{
		printf("（Enterを押してください。）\n");
		char ch = getc(stdin);
		lottery(ip, min, num);
		disp(ip, min, num);
	}

	/* 終了処理 */
	printf("ビンゴを終了します。");
	printf("（Enterを押してください。）\n");
	char ch = getc(stdin);

	free(ip);

	return 0;
}

//-----------------------------------------------------------------------------
//	概要：最小値と最大値を標準入力から取得
//　引数：max　最大値のポインタ
//	引数：min　最小値のポインタ
//-----------------------------------------------------------------------------
void setMinMax(int* max, int* min)
{
	while (1)
	{
		*min = input_uint("最小値を入力してください。", NULL, _CRT_INT_MAX, 1);
		*max = input_uint("最大値を入力してください。", NULL, _CRT_INT_MAX, 1);

		if (*min != *max)
		{
			break;
		}
		else
		{
			printf("最小値と最大値に同じ値が設定されています。再入力してください。\n");
		}
	}

	if (*min > *max)	/* 最小値に大きい数字が入力された場合、入れ替える */
	{
		unsigned int n;
		n = *min;
		*min = *max;
		*max = n;
	}
}

//-----------------------------------------------------------------------------
//	概要：抽選結果の経過を表示
//　引数：ip　抽選結果を格納している配列
//	引数：min　最小値
//	引数：num　抽選対象の個数
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
//	概要：抽選対象からランダムに抽選
//　引数：ip　抽選結果を格納している配列
//	引数：min　最小値
//	引数：num　抽選対象の個数
//-----------------------------------------------------------------------------
void lottery(int* ip, int min, int num)
{
	int rnd;
	while (1)
	{
		rnd = min + (int)(rand() * (num - 1.0 + 1.0) / (1.0 + RAND_MAX));
		if (ip[rnd - min] == 0)
		{
			printf("%dが出ました。\n", rnd);
			ip[rnd - min]++;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
//	概要：抽選を継続するか判定
//　引数：ip　抽選結果を格納している配列
//	引数：num　抽選対象の個数
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