#include "io.h"

//-----------------------------------------------------------------------------
//	概要：文字列が文字を持っているか調べます
//	引数：対象文字列へのポインタ
//	戻り値：false nullptrか空白のみの文字列、true　それ以外
//-----------------------------------------------------------------------------
inline bool str_has_char(const char* str)
{
	if (NULL == str) return false;
	bool ret = false;
	for (; !ret && *str != '\0'; str++) ret = (*str != ' ');
	return ret;
}

//-----------------------------------------------------------------------------
//	概要：bool型変数の値を書き換える
//	引数：io　書き換えるbool型変数へのポインタ、呼び出し後は
//		　ポインタが指す変数にnew_valueが代入される
//	引数：new_value　新しい値
//	戻り値：ioが示すbool型変数がもともと持っていた値
//-----------------------------------------------------------------------------
inline bool exchange_bool(bool* restrict const io, const bool new_value)
{
	const bool tmp = *io;
	*io = new_value;
	return tmp;
}

//-----------------------------------------------------------------------------
//	概要：fgetsで失敗したときにストリームをクリアしてループする関数
//	引数：s　ストリームから読み取った文字列を格納するための領域へのポインタ
//	引数：buf_size　ストリームから読み取った文字列を格納するための領域の大きさ
//	引数：fstream　FILE構造体へのポインタかstdin
//	引数：message_on_error　エラー時に表示してループする
//	戻り値：成功時は0、new line at the end of fileの時は-1
//			短すぎる入力の時は1、長すぎる入力の時は2
//-----------------------------------------------------------------------------
inline int fgets_wrap(char* restrict const s, size_t buf_size, FILE* restrict const fstream, const char* message_on_error)
{
	size_t i = 0;
	for (bool first_flg = true; i < 100 && NULL == fgets(s,buf_size,fstream); i++)
	{
		if (feof(stdin)) {
			return -1;
		}
		if (!exchange_bool(&first_flg, false))
		{
			puts((message_on_error) ? message_on_error : "読み取りに失敗しました。再入力してください。");
		}
	}
	if (100u == i) exit(1);	//無限ループ防止
	if (feof(stdin)) return 0;
	//改行文字が入力を受けた配列にない場合、入力ストリームにごみがある
	const size_t len = strlen(s);
	//短すぎる入力
	if (0 == len || (1 == len && '\n' == s[0]))
	{
		return 1;
	}
	//長すぎる入力
	if ('\n' != s[len - 1])
	{
		//入力ストリームを掃除
		while (fgetc(fstream) != '\n');
		return 2;
	}
	return 0;
}

//-----------------------------------------------------------------------------
//	概要：標準入力から入力を受け、unsigned int型に変換する
//		　fgetsしてstrtodしている。max,minの条件に合わないかエラー時はループ
//		　errorの値を書き換える
//	引数：message　入力を受ける前にputsに渡す文字列。
//		　表示しない場合はnullptrか空白文字のみで構成された文字列へのポインタを渡す
//　引数：message_on_error　エラー時に表示してループする
//	引数：max　入力値を制限する。最大値を指定
//	引数：min　入力値を制限する。最小値を指定
//	戻り値：入力した数字、EOFのときは0
//-----------------------------------------------------------------------------
extern inline unsigned int input_uint(const char* message, const char* restrict message_on_error, const unsigned int max, const unsigned int min)
{
	if (str_has_char(message))puts(message);
	char s[30];
	static_assert(sizeof(unsigned int) < 8, "err");
	unsigned long t = 0;
	size_t i = 0;
	for (char* endptr = s; ((0 == t && endptr == s) || 0 != errno || t < min || max < t) && 1 < 100u; ++i)
	{
		//長すぎる入力以降の無限ループ防止にerrnoをクリアする
		errno = 0;
		switch (fgets_wrap(s,sizeof(s),stdin,message_on_error))
		{
		case -1:return 0;//EOF
		case 1://短すぎる入力
			puts((message_on_error) ? message_on_error : "入力がありません。再入力してください。");
			endptr = s;//ループ制御フラグとして流用
			continue;
		case 2://長すぎる入力
			puts((message_on_error) ? message_on_error : "入力が長すぎます。再入力してください。");
			endptr = s;//ループ制御フラグとして流用
			continue;
		default:
			break;
		}

		t = strtoul(s, &endptr, 10);

		//エラーメッセージ
		if (*endptr != '\n')
		{
			puts((message_on_error) ? message_on_error : "数値を入力してください。");
			endptr = s;	//数字と文字の混ざった入力を確実にエラーにするため
			t = 0;
		}
		else
		{
			if ('-' == s[0])
			{
				puts((message_on_error) ? message_on_error : "入力値が小さすぎます。再入力してください。");
			}
			else
			{
				if (t < min)
				{
					puts((message_on_error) ? message_on_error : "入力値が小さすぎます。再入力してください。");
				}
				else if (t > max)
				{
					puts((message_on_error) ? message_on_error : "入力値が大きすぎます。再入力してください。");
				}
				else
				{
					//問題なし
				}
			}
		}
	}
	if (100 == i) exit(1); //無限ループ防止
	return ((unsigned int)(t));
}
