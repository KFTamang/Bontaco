#include <stdarg.h>
#include "sci.h"
#include "iodefine.h"

char sci_put_1byte(unsigned char c){
	unsigned long i=0;
	unsigned short flag=0;
	
	// ���M�o�b�t�@����������̂��|�[�����O�őҋ@
	// �^�C���A�E�g����
	for(i=0;i<0x02000000;i++){
		if(SCI1.SSR.BIT.TEND == 1){
			flag = 1;
			break;
		}
	}
	
	if(flag){
		SCI1.TDR = c;  // ���M�o�b�t�@�Ƀf�[�^�Z�b�g
		return 1;
	}
	return 0;
}


// �����񑗐M
short SCI_putstr(char *str){
	short len;
	
	len = 0;
	
	// �I�[�R�[�h�܂ő��M
	while(*str){
		if(!sci_put_1byte(*(str++))){
			return 0;
		}
		len++;
	}
	
	// ���M��������Ԃ�
	return len;
}

//  10�i���������`�F�b�N
static short isDec(char c){
    if ('0'<=c && c<='9'){
	    return 1;
    }
    return 0;
}

//  ���l��10�i�������ϊ�
static void uint2Dec(unsigned long n, char *buf){
    char c;
    short len = 0;
    short i, half;

    // 10�i������֕ϊ������������J�E���g
    do{
        if(n == 0){
		i = 0;
	}
        else{
		i = n % 10;
	}
        buf[len] = (char)(i + '0');
        len++;
        n /= 10;
    }while(n != 0);

    // �����̕��я��𒼂�
    half = len >> 1;
    for(i=0; i < half; i++){
        c = buf[i];
        buf[i] = buf[(len-1)-i];
        buf[(len-1)-i] = c;
    }

    // �I�[�R�[�h�̑}��
    buf[len]='\0';
}


//  ���l��16�i�������ϊ�
static void uint2Hex(unsigned long n, short upper, char *buf){
    char c;
    char a = 'a';
    short len = 0;
    short i, half;

    // �啶��/�������̐ݒ�
    if(upper) a = 'A';
    
    // 16�i������֕ϊ������������J�E���g
    do{
        i = n & 0x0F;
        if(i > 9){
		buf[len] = (unsigned char)(i + a - 10);
	}
        else{
		buf[len] = (unsigned char)(i + '0');
	}
        len++;
        n >>= 4;
    }while(n != 0);

    // �����̕��я��𒼂�
    half = len >> 1;
    for(i=0; i < half; i++){
        c = buf[i];
        buf[i] = buf[(len-1)-i];
        buf[(len-1)-i] = c;
    }

    // �I�[�R�[�h�̑}�� */
    buf[len]='\0';
}


//  �w��t�H�[�}�b�g�ŕ\������
static void printFormat(char *ptr, short order, short alignLeft, short fillZero, short minus){
    char *str = ptr;
    char pad = ' ';
    short len = 0;
    long  i;

    // �������̃J�E���g
    for(len=0; *str != '\0'; len++, str++);
    
    // �}�C�i�X�Ȃ當��������
    if(minus){ 
    	len++;
    }

    // �������̒���
    if(order){
        if(order>len){
		order -= len;
	}
        else{
		order  = 0;
	}
    }

    // �E�l��
    if( ! alignLeft){
        // �l�ߕ����̐ݒ�
        if(fillZero){
            pad = '0';
            
            // �}�C�i�X�\��
            if(minus){
                sci_put_1byte('-');
                minus = 0;
            }
        }

        for(i=0; i<order; i++){
            sci_put_1byte(pad);
	}
    }

    // �}�C�i�X�\��
    if(minus)  sci_put_1byte('-');

    // �f�[�^�̕\��
    SCI_putstr(ptr);

    /* ���l�� */
    if(alignLeft)
        for(i=0; i<order; i++)
            sci_put_1byte(' ');
}


// �t�H�[�}�b�g�ϊ�
static char *parseFormat(char *str,void *value){
	short alignLeft=0;
	short fillZero=0;
	short order=0;
	short minus=0;
	char buf[12];
	char *ptr=buf;
	
	//���l
	if(*str=='-'){ alignLeft = 1; str++; }
	
	//�[���t�B��
	if(*str=='0'){ fillZero = 1; str++; }
	
	// �������w�蔻��
	if(isDec(*str)){
		for(order=0;isDec(*str);){
			order *= 10;
			order += (*str - '0');
			str++;
		}
	}

	// ��ޔ���,�\������
	switch(*str){
		case 'd':  // �����t10�i��(short�^)
		case 'D':  // �����t10�i��(short�^)
			if((signed short)value >= 0){
				uint2Dec((unsigned short)value , buf);
			}else{
				uint2Dec((unsigned short)(-(signed short)value) , buf); 
				minus = 1;
			}
			break;
		case 'l':  // �����t10�i��(long�^)
		case 'L':  // �����t10�i��(long�^)
			if((signed long)value >= 0){
				uint2Dec((unsigned long)value , buf);
			}else{
				uint2Dec((unsigned long)(-(signed long)value) , buf); 
				minus = 1;
			}
			break;
		case 'u':   // �����Ȃ�10�i��
		case 'U':   // �����Ȃ�10�i��
			uint2Dec((unsigned short)value , buf);
			break;
		case 'x':   // ������16�i��
			uint2Hex((unsigned long)value , 0 , buf);
			break;
		case 'X':   // �啶��16�i��
			uint2Hex((unsigned long)value , 1 , buf);
			break;
		case 's':   // ������
		case 'S':   // ������
			ptr = (char *)value;
			break;
		case 'c':   // 1����
		case 'C':   // 1����
			buf[0] = (char)((unsigned long)value & 0xFF);
			buf[1] = '\0';
			break;
		default: 
			buf[0] = '\0';
			break;
	}

	// �\��
	printFormat(ptr,order,alignLeft,fillZero,minus);
	
	str++;
	return(str);
	
}


// ������\��printf
short sci_printf(char *str , ...){
	va_list ap;
	char *ptr;
	
	ptr = str;
	
	// �ψ����̏�����
	va_start(ap,str);
	
	while(*ptr){
		// ���ꕶ��
		if(*ptr=='%'){
			ptr++;
			
			if(*ptr=='%'){
				sci_put_1byte('%'); 
				ptr++;	
			} 
			else{
				ptr = parseFormat(ptr,va_arg(ap,void *));
				if(ptr == 0){ 
					return -1;
				}
			}
		}
		// �ʏ핶��
		else{
			sci_put_1byte(*ptr);
			ptr++;
		}
	}
	va_end(ap);
	return (ptr-str);  // ���M������
}