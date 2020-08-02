#include "io.h"

//-----------------------------------------------------------------------------
//	�T�v�F�����񂪕����������Ă��邩���ׂ܂�
//	�����F�Ώە�����ւ̃|�C���^
//	�߂�l�Ffalse nullptr���󔒂݂̂̕�����Atrue�@����ȊO
//-----------------------------------------------------------------------------
inline bool str_has_char(const char* str)
{
	if (NULL == str) return false;
	bool ret = false;
	for (; !ret && *str != '\0'; str++) ret = (*str != ' ');
	return ret;
}

//-----------------------------------------------------------------------------
//	�T�v�Fbool�^�ϐ��̒l������������
//	�����Fio�@����������bool�^�ϐ��ւ̃|�C���^�A�Ăяo�����
//		�@�|�C���^���w���ϐ���new_value����������
//	�����Fnew_value�@�V�����l
//	�߂�l�Fio������bool�^�ϐ������Ƃ��Ǝ����Ă����l
//-----------------------------------------------------------------------------
inline bool exchange_bool(bool* restrict const io, const bool new_value)
{
	const bool tmp = *io;
	*io = new_value;
	return tmp;
}

//-----------------------------------------------------------------------------
//	�T�v�Ffgets�Ŏ��s�����Ƃ��ɃX�g���[�����N���A���ă��[�v����֐�
//	�����Fs�@�X�g���[������ǂݎ������������i�[���邽�߂̗̈�ւ̃|�C���^
//	�����Fbuf_size�@�X�g���[������ǂݎ������������i�[���邽�߂̗̈�̑傫��
//	�����Ffstream�@FILE�\���̂ւ̃|�C���^��stdin
//	�����Fmessage_on_error�@�G���[���ɕ\�����ă��[�v����
//	�߂�l�F��������0�Anew line at the end of file�̎���-1
//			�Z��������͂̎���1�A����������͂̎���2
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
			puts((message_on_error) ? message_on_error : "�ǂݎ��Ɏ��s���܂����B�ē��͂��Ă��������B");
		}
	}
	if (100u == i) exit(1);	//�������[�v�h�~
	if (feof(stdin)) return 0;
	//���s���������͂��󂯂��z��ɂȂ��ꍇ�A���̓X�g���[���ɂ��݂�����
	const size_t len = strlen(s);
	//�Z���������
	if (0 == len || (1 == len && '\n' == s[0]))
	{
		return 1;
	}
	//�����������
	if ('\n' != s[len - 1])
	{
		//���̓X�g���[����|��
		while (fgetc(fstream) != '\n');
		return 2;
	}
	return 0;
}

//-----------------------------------------------------------------------------
//	�T�v�F�W�����͂�����͂��󂯁Aunsigned int�^�ɕϊ�����
//		�@fgets����strtod���Ă���Bmax,min�̏����ɍ���Ȃ����G���[���̓��[�v
//		�@error�̒l������������
//	�����Fmessage�@���͂��󂯂�O��puts�ɓn��������B
//		�@�\�����Ȃ��ꍇ��nullptr���󔒕����݂̂ō\�����ꂽ������ւ̃|�C���^��n��
//�@�����Fmessage_on_error�@�G���[���ɕ\�����ă��[�v����
//	�����Fmax�@���͒l�𐧌�����B�ő�l���w��
//	�����Fmin�@���͒l�𐧌�����B�ŏ��l���w��
//	�߂�l�F���͂��������AEOF�̂Ƃ���0
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
		//����������͈ȍ~�̖������[�v�h�~��errno���N���A����
		errno = 0;
		switch (fgets_wrap(s,sizeof(s),stdin,message_on_error))
		{
		case -1:return 0;//EOF
		case 1://�Z���������
			puts((message_on_error) ? message_on_error : "���͂�����܂���B�ē��͂��Ă��������B");
			endptr = s;//���[�v����t���O�Ƃ��ė��p
			continue;
		case 2://�����������
			puts((message_on_error) ? message_on_error : "���͂��������܂��B�ē��͂��Ă��������B");
			endptr = s;//���[�v����t���O�Ƃ��ė��p
			continue;
		default:
			break;
		}

		t = strtoul(s, &endptr, 10);

		//�G���[���b�Z�[�W
		if (*endptr != '\n')
		{
			puts((message_on_error) ? message_on_error : "���l����͂��Ă��������B");
			endptr = s;	//�����ƕ����̍����������͂��m���ɃG���[�ɂ��邽��
			t = 0;
		}
		else
		{
			if ('-' == s[0])
			{
				puts((message_on_error) ? message_on_error : "���͒l�����������܂��B�ē��͂��Ă��������B");
			}
			else
			{
				if (t < min)
				{
					puts((message_on_error) ? message_on_error : "���͒l�����������܂��B�ē��͂��Ă��������B");
				}
				else if (t > max)
				{
					puts((message_on_error) ? message_on_error : "���͒l���傫�����܂��B�ē��͂��Ă��������B");
				}
				else
				{
					//���Ȃ�
				}
			}
		}
	}
	if (100 == i) exit(1); //�������[�v�h�~
	return ((unsigned int)(t));
}
