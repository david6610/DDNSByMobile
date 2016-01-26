/*
;-------------------------------------------------------------------------
; Copyright (c) 2002 Jim Brady
; Do not use commercially without author's permission
; Last revised August 2002
; CKSUM.A51
;
; This computes the internet checksum on an 8051
;
; Call from C program: UINT cksum(UCHAR xdata * buf, UINT length);
; Where * buf is pointer to first char (must be in xdata space)
; and "length" is number of bytes (not words) to sum over
;-------------------------------------------------------------------------
*/
#include "net.h"

unsigned int cksum(unsigned char *check,unsigned intlength) //����У���
{
	long sum=0;
	unsigned int i;
	unsigned int *ptr; 
    ptr=(unsigned int *)check;
	for (i=0;i<(length)/2;i++)
	{
		sum+=*ptr++;
	}
	if (length&0x01)//��ʾ����Ϊ����
	{
		sum=sum+((*ptr)&0xff00);
	}
	sum=(sum&0xffff)+((sum>>16)&0xffff);//��16λ�͵�16λ���
	if(sum&0xffff0000)
	{//��ʾ�н�λ
		sum++;
	}
	return ( (unsigned int)((sum)&0xffff));
//	return ( (UINT)(~((sum)&0xffff)));
}
