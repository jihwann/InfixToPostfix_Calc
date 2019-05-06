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


// ���� �ʱ�ȭ �Լ�
void init_stack(StackType *s, int size) {
	s->top = -1;
	s->capacity = size;
	s->data = (element *)malloc(size * sizeof(element));
}

// ���� ���� ���� �Լ�
int is_empty(StackType *s) {
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType *s) {
	return (s->top == (s->capacity - 1));
}

// ���ÿ� ���� �Լ�
void push(StackType *s, element item) {
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}

// ���� �Լ�
element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ���� (called pop)\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ���� (called peek)\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

// ������ �켱������ ��ȯ
int prec(char op) {
	switch (op) {
	case '(':	case ')':	return 0;	break;
	case '+':	case '-':	return 1;	break;
	case '*':	case '/':	return 2;	break;
	}
	return -1;
}

// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char *exp) {
	int i = 0;
	int cnt = 0;
	char ch, top_op, temp;
	int len = strlen(exp);
	StackType *s = (StackType *)malloc(sizeof(StackType));
	init_stack(s, len); // ���� �ʱ�ȭ

	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+':	case '-':	case '*':	case '/': // ch�� �������� ���
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
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
		default:	// �ǿ�����
			result[cnt++] = ch;
			break;
		}
	}
	
	// ���ÿ� ����� �����ڵ� ���
	while (!is_empty(s)) { 
		result[cnt++] = pop(s);
	}
	
	for (i = 0; i < cnt; i++) {
		printf("%c", result[i]);
	}
	printf("\n\n");
	printf("��� ��: %d", eval(result));
}

// ���� ǥ�� ���� ���
int eval(char *exp) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType *s = (StackType *)malloc(sizeof(StackType));
	init_stack(s, len);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		// �Է��� �ǿ�����
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			push(s, value);
		}
		else { // �Է��� ������
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