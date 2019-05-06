/*
===================================================================================
Name        : InfixToPostfix_calc.c
Author      : JiHwan Lim
Date		: 2019-05-06
Version     : 1.0
Copyright   : Your copyright notice
Description : Data structure 2nd task (convert infix to postfix and calculate result)
E-mail		: jhim147605@gmail.com
====================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "InfixToPostfix_calc.h"


// 스택 초기화 함수
void init_stack(StackType *s, int size) {
	s->top = -1;
	s->capacity = size;
	s->data = (element *)malloc(size * sizeof(element));
}

// 공백 상태 검출 함수
int is_empty(StackType *s) {
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s) {
	return (s->top == (s->capacity - 1));
}

// 스택에 삽입 함수
void push(StackType *s, element item) {
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러 (called pop)\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러 (called peek)\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

// 연산자 우선순위를 반환
int prec(char op) {
	switch (op) {
	case '(':	case ')':	return 0;	break;
	case '+':	case '-':	return 1;	break;
	case '*':	case '/':	return 2;	break;
	}
	return -1;
}

// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char *exp) {
	int i = 0;
	int cnt = 0;
	char ch, top_op, temp;
	int len = strlen(exp);
	StackType *s = (StackType *)malloc(sizeof(StackType));
	init_stack(s, len); // 스택 초기화

	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+':	case '-':	case '*':	case '/': // ch가 연산자인 경우
			// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(s) && (prec(ch) <= prec(peek(s)))) 
				result[cnt++] = pop(s);
			push(s, ch);
			break;
		case '(':	push(s, ch);	break;
		case ')':
			top_op = pop(s);
			while (top_op != '(') {
				result[cnt++] = top_op;
				top_op = pop(s);
			}
			break;
		default:	// 피연산자
			result[cnt++] = ch;
			break;
		}
	}
	
	// 스택에 저장된 연산자들 출력
	while (!is_empty(s)) { 
		result[cnt++] = pop(s);
	}
	
	for (i = 0; i < cnt; i++) {
		printf("%c", result[i]);
	}
	printf("\n\n");
	printf("결과 값: %d", eval(result));
}

// 후위 표기 수식 계산
int eval(char *exp) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType *s = (StackType *)malloc(sizeof(StackType));
	init_stack(s, len);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		// 입력이 피연산자
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			push(s, value);
		}
		else { // 입력이 연산자
			op2 = pop(s);
			op1 = pop(s);
			switch (ch) {
			case '+':	push(s, op1 + op2);	break;
			case '-':	push(s, op1 - op2);	break;
			case '*':	push(s, op1 * op2);	break;
			case '/':	push(s, op1 / op2);	break;
			}
		}
	}
	return pop(s);
}