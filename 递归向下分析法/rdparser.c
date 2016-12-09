#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum yytokentype {
	INT = 258,
	EOL = 259,
	CHAR, STR, VOID, ID, NUMBER, PRINT, WHILE, RETURN, ASSIGN, STRING, ELSE, CMP, IF
};

extern int yylex();
extern char yylval_x[20];
extern char* yytext;


int tok;


void advance()
{
	tok = yylex();
	printf("tok: %s\n", yytext);
	
}

typedef struct _ast ast;
typedef struct _ast *past;
struct _ast{
	char* ivalue;
	char* nodeType;
	past left;
	past mid;
	past right;
};

past newAstNode()
{
	past node = malloc(sizeof(ast));
	if (node == NULL)
	{
		printf("run out of memory.\n");
		exit(0);
	}
	memset(node, 0, sizeof(ast));
	return node;
}

past ASTNUMBER()
{
	past var = newAstNode();
	var->nodeType = "NUMBER";
	
	return var;
}
past ASTSTRING()
{
	past var = newAstNode();
	var->nodeType = "STRING";
	
	return var;
}
past ASTID()
{
	past var = newAstNode();
	var->nodeType = "ID";
	
	return var;
}
past ASTTYPE()
{
	past var = newAstNode();
	var->nodeType = "TYPE";
	
	return var;
}
past newprogram(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "program";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newdecl_or_stmt(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "decl_or_stmt";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newdecl_list(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "decl_list";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newintstr_list(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "intstr_list";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newparameter_list(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "parameter_list";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newstmt_list(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "stmt_list";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}

past newparameter(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "parameter";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newexpr_list(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "expr_list";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newexpr_stmt(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "expr_stmt";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newid_list(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "id_list";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newmul_expr(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "mul_expr";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newexpr(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "expr";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newcmp_expr(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "cmp_expr";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}
past newadd_expr(past left, past right)
{
	past var = newAstNode();
	var->nodeType = "add_expr";
	var->ivalue = "0";
	var->left = left;
	var->right = right;
	return var;
}

past newex_decl(past left, past mid, past right)
{
	past var = newAstNode();
	var->nodeType = "ex_decl";
	var->ivalue = "0";
	var->left = left;
	var->mid = mid;
	var->right = right;
	return var;
}
past newdecl(past left, past mid, past right)
{
	past var = newAstNode();
	var->nodeType = "decl";
	var->ivalue = "0";
	var->left = left;
	var->mid = mid;
	var->right = right;
	return var;
}
past newstmt(past left, past mid, past right)
{
	past var = newAstNode();
	var->nodeType = "stmt";
	var->ivalue = "0";
	var->left = left;
	var->mid = mid;
	var->right = right;
	return var;
}
past newprimary_expr(past left, past mid, past right)
{
	past var = newAstNode();
	var->nodeType = "primary_expr";
	var->ivalue = "0";
	var->left = left;
	var->mid = mid;
	var->right = right;
	return var;
}

past ASTprogram();
past ASTex_decl();
past ASTdecl_or_stmt();
past ASTdecl_list();
past ASTintstr_list();
past ASTdecl();
past ASTparameter_list();
past ASTstmt();
past ASTstmt_list();
past ASTparameter();
past ASTexpr_stmt();
past ASTexpr_list();
past ASTid_list();
past ASTmul_expr();
past ASTprimary_expr();
past ASTexpr();
past ASTcmp_expr();
past ASTadd_expr();


past ASTprogram()
{
	past l = ASTex_decl();
	past list = newprogram(NULL, l);
	while (tok)
	{
		l = ASTex_decl();
		list = newprogram(list, l);
	}
	return list;
}
past ASTex_decl()
{
	past result = NULL;
	past t = ASTTYPE();
	advance();
	past d = ASTdecl();
	past ds = ASTdecl_or_stmt();
	result = newex_decl(t, d, ds);
	return result;
}
past ASTdecl_or_stmt()
{
	past list = NULL;
	if (tok == '{')
	{
		advance();
		if (tok == '}')
		{
			advance();
			return list;
		}
		else
		{
			list = newdecl_or_stmt(NULL, ASTstmt_list());
			advance();
			return list;
		}
	}
	if (tok == ',')
	{
		advance();
		list = newdecl_or_stmt(NULL, ASTdecl_list());
		advance();
		return list;
	}
	if (tok == ';')
	{
		advance();
		return list;
	}
}
past ASTdecl_list()
{
	past list = newdecl_list(NULL, ASTdecl());
	while (tok == ',')
	{
		advance();
		list = newdecl_list(list, ASTdecl());
	}
	return list;
}
past ASTintstr_list()
{
	past list = NULL;
	if (tok == NUMBER)
	{
		
		past list = newdecl_list(NULL, ASTNUMBER());
		advance();
	}
	if (tok == STRING)
	{
		
		past list = newdecl_list(NULL, ASTSTRING());
		advance();
	}
	while (tok == ',')
	{
		advance();
		if (tok == NUMBER)
		{
			
			past list = newdecl_list(list, ASTNUMBER());
			advance();
		}
		if (tok == STRING)
		{
			
			past list = newdecl_list(list, ASTSTRING());
			advance();
		}
	}
	return list;
}
past ASTdecl()
{
	
	past result = newdecl(NULL, NULL, ASTID());
	advance();
	if (tok == '=')
	{
		advance();
		result = newdecl(NULL, ASTexpr(), ASTID());

	}
	if (tok == '(')
	{
		advance();
		if (tok == ')')
			advance();
		else
		{
			result = newdecl(NULL, ASTparameter_list(), ASTID());
			advance();
		}
	}
	if (tok == '[')
	{
		advance();
		if (tok == ']')
		{
			advance();
			if (tok == '=')
			{
				advance();
				advance();
				result = newdecl(NULL, ASTintstr_list(), ASTID());
				if (tok == '}')
					advance();

			}
		}
		else
		{
			result = newdecl(NULL, ASTexpr(), ASTID());
			advance();
			if (tok == '=')
			{
				advance();
				advance();
				result = newdecl(ASTintstr_list(), ASTexpr(), ASTID());
				if (tok == '}')
					advance();
			}
		}
	}
	return result;
}
past ASTparameter_list()
{
	past list = newparameter_list(NULL, ASTparameter());
	while (tok == ',')
	{
		advance();
		list = newparameter_list(list, ASTparameter());
	}
	return list;
}
past ASTstmt()
{
	past result = NULL;
	if (tok == INT || tok == STR || tok == VOID||tok==CHAR)
	{
		
		result = newstmt(NULL, NULL, ASTTYPE());
		advance();
		result = newstmt(NULL, ASTdecl_list(), ASTTYPE());
		advance();
	}
	if (tok == '{')
	{
		advance();
		result = newstmt(NULL, NULL, ASTstmt_list());
		advance();
	}
	if (tok == IF)
	{
		advance();
		advance();
		result = newstmt(NULL, NULL, ASTexpr());
		advance();
		result = newstmt(NULL, ASTstmt(), ASTexpr());
		if (tok == ELSE)
		{
			advance();
			result = newstmt(ASTstmt(), ASTstmt(), ASTexpr());
		}
	}
	if (tok == WHILE)
	{
		advance();
		advance();
		result = newstmt(NULL, NULL, ASTexpr());
		advance();
		result = newstmt(NULL, ASTstmt(), ASTexpr());
	}
	if (tok == RETURN)
	{
		advance();
		if (tok == ';')
			advance();
		else
		{
			result = newstmt(NULL, NULL, ASTexpr());
			advance();
		}
	}
	if (tok == PRINT)
	{
		advance();
		if (tok == ';')
			advance();
		else
		{
			result = newstmt(NULL, NULL, ASTexpr_list());
			advance();
		}
	}
	else
	{
		result = newstmt(NULL, NULL, ASTexpr_stmt());
	}
	return result;
}
past ASTstmt_list()
{
	past l = ASTstmt();
	past list = newstmt_list(NULL,l);
	while (tok)
	{
		l = ASTstmt();
		list = newstmt_list(list, l);
	}
	return list;
}
past ASTparameter()
{
	past list = NULL;
	
	list = newparameter(NULL, ASTTYPE());
	advance();
	
	list = newparameter(ASTID(), ASTTYPE());
	advance();

	return list;
}
//past ASTYPE
past ASTexpr_stmt()
{
	past list = NULL;
	if (tok == ';')
		advance();
	else
	{
		list = newexpr_stmt(NULL, ASTexpr());
		advance();
	}
	return list;
}
past ASTexpr_list()
{
	past list = newexpr_list(NULL, ASTexpr());
	while (tok == ',')
	{
		advance();
		list = newexpr_list(list, ASTexpr());
	}
	return list;
}
past ASTid_list()
{
	
	past list = newid_list(NULL, ASTID());
	advance();
	while (tok == ',')
	{
		advance();
		
		list = newid_list(list, ASTID());
		advance();
	}
	return list;
}
past ASTmul_expr()
{
	past list = newmul_expr(NULL, ASTprimary_expr());
	while (tok == '*' || tok == '/' || tok == '%')
	{
		advance();
		list = newmul_expr(list, ASTprimary_expr());
	}
	if (tok == '-')
	{
		advance();
		list = newmul_expr(NULL, ASTprimary_expr());
	}
	return list;
}
past ASTprimary_expr()
{
	past result = NULL;
	if (tok == ID)
	{
		
		result = newprimary_expr(NULL, NULL, ASTID());
		advance();
		if (tok == '(')
		{
			advance();
			if (tok == ')')
				advance();
			else
			{
				result = newprimary_expr(NULL, ASTexpr_list(), ASTID());
				advance();
			}
		}
		if (tok = ASSIGN)
		{
			advance();

			result = newprimary_expr(NULL, ASTexpr(), ASTID());
		}
		if (tok == '=')
		{
			advance();
			result = newprimary_expr(NULL, ASTexpr(), ASTID());
		}
		if (tok == '[')
		{
			advance();
			result = newprimary_expr(NULL, ASTexpr(), ASTID());
			advance();
			if (tok == '=')
			{
				advance();
				result = newprimary_expr(ASTexpr(), ASTexpr(), ASTID());
			}
		}
	}
	if (tok == '(')
	{
		advance();
		result = newprimary_expr(NULL, NULL, ASTexpr());
		advance();
	}
	if (tok == NUMBER)
	{
		
		result = newprimary_expr(NULL, NULL, ASTNUMBER());
		advance();
	}
	if (tok == STRING)
	{
		
		result = newprimary_expr(NULL, NULL, ASTSTRING());
		advance();
	}
	return result;
}
past ASTexpr()
{
	past list = newexpr(NULL, ASTcmp_expr());
	return list;
}
past ASTcmp_expr()
{
	past list = newcmp_expr(NULL, ASTadd_expr());
	while (tok == CMP)
	{
		advance();
		list = newcmp_expr(list, ASTadd_expr());
	}
	return list;
}
past ASTadd_expr()
{
	past list = newadd_expr(NULL, ASTmul_expr());
	while (tok == '+' || tok == '-')
	{
		advance();
		list = newadd_expr(list, ASTmul_expr());
	}
	return list;
}






void showAst(past node, int nest)
{
	if (node == NULL)
		return;

	int i = 0;
	for (i = 0; i < nest; i++)
		printf("  ");
	if (strcmp(node->nodeType, "NUMBER") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "STRING") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "TYPE") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "ID") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "program") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "ex_decl") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "decl_or_stmt") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "decl_list") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "intstr_list") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "decl") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "parameter_list") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "stmt_list") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "parameter") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "expr_stmt") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "expr_list") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "id_list") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "mul_expr") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "primary_expr") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "expr") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "cmp_expr") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "add_expr") == 0)
		printf("%s \n", node->nodeType);
	if (strcmp(node->nodeType, "stmt") == 0)
		printf("%s \n", node->nodeType);
	showAst(node->left, nest + 1);
	showAst(node->mid, nest + 1);
	showAst(node->right, nest + 1);

}



int main(int argc, char **argv)
{
	advance();
	past rr = ASTprogram();
	showAst(rr, 0);


	return 0;
}