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

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType *s, int size);

// ���� ���� ���� �Լ�
int is_empty(StackType *s);

// ��ȭ ���� ���� �Լ�
int is_full(StackType *s);

// ���ÿ� ���� �Լ�
void push(StackType *s, element item);

// ���� �Լ�
element pop(StackType *s);

// s->top �� ��ȯ
element peek(StackType *s);

// ������ �켱������ ��ȯ
int prec(char op);

// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char *exp);

// ���� ǥ�� ���� ���
int eval(char *exp);