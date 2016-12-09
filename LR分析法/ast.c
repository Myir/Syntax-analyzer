
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"


void showAst(past node, int nest)
{
	if (node == NULL)
		return;

	int i = 0;
	for (i = 0; i < nest; i++)
		printf("  ");
	if (node->ivalue == NULL)
		printf("%s \n", node->nodeType);
	else
		printf("%s %s\n", node->nodeType, node->ivalue);
	showAst(node->left, nest + 1);
	showAst(node->mid, nest + 1);
	showAst(node->right, nest + 1);

}


past newAstNode()
{
	past node = malloc(sizeof(ast));
	if(node == NULL)
	{
		printf("run out of memory.\n");
		exit(0);
	}
	memset(node, 0, sizeof(ast));
	return node;
}

past newNum(char* x)
{
	past var = newAstNode();
	strcpy(var->nodeType , "NUMBER");
	strcpy(var->ivalue, x);
	return var;
}
past newSTR(char* x)
{
	past var = newAstNode();
	strcpy(var->nodeType , "STRING");
	strcpy(var->ivalue, x);
	return var;
}
past newID(char* x)
{
	past var = newAstNode();
	strcpy(var->nodeType , "ID");
	strcpy(var->ivalue, x);
	return var;
}
past newTYPE(char* x)
{
	past var = newAstNode();
	strcpy(var->nodeType , "TYPE");
	strcpy(var->ivalue, x);
	return var;
}


past newExpr(char* nodeType, past left, past mid, past right)
{
	past var = newAstNode();
	strcpy(var->nodeType,nodeType);
	var->left = left;
	var->mid = mid;
	var->right = right;
	return var;
}