/**************************** cforth.c **********************************
 * Name: Cforth	0.3.2							*
 * Copyright: ear & xiaohao						*
 * Author: ear & xiaohao						*
 * Date: 27-06-12 12:28							*
 * Description: Cforth is a forth interpreter, using C language		*
 ************************************************************************/	 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_words.h"
#include "colon_words.h"
#define COMPILER	0
#define INTERPRETER	1
#define COREWORDS_NUM	19
#define WORD_WIDTH	20


/*使用函数指针在解释模式下挨个搜索字典中的词*/
const char word_str[COREWORDS_NUM][WORD_WIDTH] = 
{	".s",	".rs",	".",	"swap",	">r",
	"r>",	"dup",	"drop",	"2drop","2dup",
	"over",	"+",	"-",	"*",	"/",
	"/d",	"%",	"--",	"++"		};		
typedef void (*pType) (void) ;
pType word_pointer[COREWORDS_NUM] = 
{	showDS,	showRS,	showTop,swap,	tor,
	rto,	dup,	drop,	drop2,	dup2,
	over,	add,	sub,	mul,	ddiv,
	divv,	mod,	sub1,	add1		}; 


/************************************************************************/ 


/************************************************************************
 *cforth主控制结构							*/  
int main()
{
	printf("Cforth 0.3.2, ear & xiaohao Copyright (C) 2008-2012 \n");
	printf("Cforth comes with ABSOLUTELY NO WARRANTY.\n");
	printf("Enjoy it and have a good time! Type 'bye' to exit\n");

	int status = INTERPRETER;
	char word_buff[WORD_WIDTH];
	while (status == INTERPRETER){ 
		scanf("%s", &word_buff);
		interpret_words(word_buff);
	}
	
	return 0;
} 
/************************************************************************/ 


/************************************************************************
 *cforth解释器函数							*/ 
int interpret_words(char *str)
{
	int i;
	for (i = 0; i <= COREWORDS_NUM; i++) {
		if( isNum(str) ) {
			push(atoi(str));
			break;
		}
		else if(!strcmp(word_str[i],str)) {
			word_pointer[i]();
			break;
		}
		else if( !strcmp("bye",str) ) 
			exit(0);
			
		else if(i == COREWORDS_NUM){
			printf("Undifine word!\n>>>%s<<<\n",str);
			clean_ds();
			break;
		}
	}
	
	return 0;	
}
/*数值字符串判断函数，是int型则返回1，否则返回0				*/ 
int isNum(char *str) 
{
	if(*str=='-' && *(str+1)=='\0')
		return 0;
	if((*str<'0' || *str>'9') && *str!='-')
		return 0;
	str++;
	for(; *str!='\0'; str++) {
		if(*str<'0' || *str>'9')
			return 0;
	}
	return 1;
}
/************************************************************************/ 