/*
===================================================================================
Name        : main.c
Author      : JiHwan Lim
Date		: 2019-05-06
Version     : 1.0
Copyright   : Your copyright notice
Description : Data structure 2nd task (convert infix to postfix and calculate result)
E-mail		: jhim147605@gmail.com
====================================================================================
*/

#include "InfixToPostfix_calc.h"

int main(void) {
	int len;
	char *s = "(2+3)*4+9";
	char *s1 = "4*3+6/2-2*2+((2+4)*6/2)-1";
	printf("중위표기수식: %s\n", s1);	
	printf("후위표기수식: ");
	infix_to_postfix(s1);

	return 0;
}