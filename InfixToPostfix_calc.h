/*
===================================================================================
Name        : InfixToPostfix_calc.h
Author      : JiHwan Lim
Date		: 2019-05-06
Version     : 1.0
Copyright   : Your copyright notice
Description : Data structure 2nd task (convert infix to postfix and calculate result)
E-mail		: jhim147605@gmail.com
====================================================================================
*/

#pragma once

#define MAX_SIZEOF_POSTFIX 100
typedef char element;
typedef struct StackType {
	element *data;
	int capacity;
	int top;
} StackType;
char result[MAX_SIZEOF_POSTFIX];

// 스택 초기화 함수
void init_stack(StackType *s, int size);

// 공백 상태 검출 함수
int is_empty(StackType *s);

// 포화 상태 검출 함수
int is_full(StackType *s);

// 스택에 삽입 함수
void push(StackType *s, element item);

// 삭제 함수
element pop(StackType *s);

// s->top 값 반환
element peek(StackType *s);

// 연산자 우선순위를 반환
int prec(char op);

// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char *exp);

// 후위 표기 수식 계산
int eval(char *exp);