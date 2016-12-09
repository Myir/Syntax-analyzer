#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum yytokentype {
	INT = 258,
	EOL = 259,
	CHAR, STR, VOID, ID, NUMBER, PRINT, WHILE, RETURN, ASSIGN, STRING, ELSE, CMP, IF
};

extern int yylex();
extern int yylval;
extern char* yytext;

void advance();
void program();
void ex_decl();
void decl_or_stmt();
void decl_list();
void intstr_list();
void decl();
void parameter_list();
void stmt();
void stmt_list();
void parameter();
void type();
void expr_stmt();
void expr_list();
void id_list();
void mul_expr();
void primary_expr();
void expr();
void cmp_expr();
void add_expr();
int tok;


void advance()
{
	tok = yylex();
	printf("tok:%s\n",yytext);
	if (tok == '\0')
		exit(0);
}
void program()
{
	ex_decl();
	while (tok != '\0')
	{
		ex_decl();
	}
}
void ex_decl()
{
	type();
	decl();
	decl_or_stmt();
}
void decl_or_stmt()
{
	if (tok == '{')
	{
		advance();
		if (tok == '}')
		{
			advance();
		}
		else
		{
			stmt_list();
			if (tok == '}')
				advance();
			else
				printf("error,need '}'\n");
		}
	}
	if (tok == ',')
	{
		advance();
		decl_list();
		if (tok == ';')
			advance();
		else
			printf("error,need xxx';'");
	}
	if (tok == ';')
		advance();
}
void decl_list()
{
	decl();
	while (tok == ',')
	{
		advance();
		decl();
	}
}
void intstr_list()
{
	while (tok == NUMBER || STRING)
	{
		advance();
		if (tok == ',')
			advance();
		
	}
}
//"!!!!"
void decl()
{
	if (tok == ID)
	{
		advance();
		if (tok == '(')
		{
			advance();
			if (tok == ')')
				advance();
			else
			{
				parameter_list();
				if (tok == ')')
					advance();
				else
					printf("error,need ')'");
			}
		}
		if (tok == '=')
		{
			advance();
			expr();
		}
		if (tok == '[')
		{
			advance();
			if (tok == ']')
				advance();
			else
			{
				expr();
				if (tok == ']')
				{
					advance();
					if (tok == '=')
					{
						advance();
						if (tok == '{')
						{
							advance();
							intstr_list();
							if (tok == '}')
								advance();
							else
								printf("error,need '}");
						}
					}
				}
			}
		}
		else
			return;
	}
}
void parameter_list()
{
	parameter();
	while (tok == ',')
	{
		advance();
		parameter();
	}
}
void stmt()
{
	if (tok == INT || tok == STR || tok == VOID)
	{
		advance();
		decl_list();
		if (tok == ';')
			advance();
	}
	if (tok == '{')
	{
		advance();
		stmt_list();
		if (tok == '}')
			advance();
	}
	if (tok == IF)
	{
		advance();
		if (tok == '(')
		{
			advance();
			expr();
			if (tok == ')')
			{
				advance();
				stmt();
				if (tok == ELSE)
				{
					advance();
					stmt();
				}
			}
		}
	}
	if (tok == WHILE)
	{
		advance();
		if (tok == '(')
		{
			advance();
			expr();
			if (tok == ')')
			{
				advance();
				stmt();
			}
		}
	}
	if (tok == RETURN)
	{
		advance();
		if (tok == ';')
			advance();
		else
		{
			expr();
			if (tok == ';')
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
			expr_list();
			if (tok == ';')
				advance();
		}
	}
	else
		expr_stmt();
	//***************
}
void stmt_list()
{
	stmt();
	while (tok != '\0')
		stmt();
}
void parameter()
{
	type();
	if (tok == ID)
		advance();
}
void type()
{
	if (tok == INT || STR || VOID)
		advance();

}
void expr_stmt()
{
	if (tok == ';')
		advance();
	else
	{
		expr();
		if (tok == ';')
			advance();
	}
}
void expr_list()
{
	expr();
	while (tok == ',')
	{
		advance();
		expr();
	}
}
void id_list()
{
	if (tok == ID)
	{
		advance();
		while (tok == ',')
		{
			advance();
			if (tok == ID)
				advance();
		}
	}

}
void mul_expr()
{
	primary_expr();
	if (tok == '*' || tok == '/' || tok == '%')
	{
		advance();
		mul_expr();
	}
	if (tok == '-')
	{
		advance();
		primary_expr();
	};
}
void primary_expr()
{
	if (tok == '(')
	{
		advance();
		expr();
		if (tok == ')')
			advance();
		else
			printf("error,need ')'");
	}
	if (tok == ID)
	{
		advance();
		if (tok == '(')
		{
			advance();
			if (tok == ')')
				advance();
			else
			{
				expr_list();
				if (tok == ')')
					advance();
				else
					printf("error,need ')'");
			}
		}

		if (tok == ASSIGN)
		{
			advance();
			expr();
		}
		if (tok == '=')
		{
			advance();
			expr();
		}
		if (tok == '[')
		{
			advance();
			expr();
			if (tok == ']')
			{
				advance();
				if (tok == '=')
				{
					advance();
					expr();
				}

			}
		}
		else
			return;
	}
	if (tok == NUMBER || tok == STRING)
		advance();
}
void expr()
{
	cmp_expr();
}
void cmp_expr()
{
	add_expr();
	if (tok == CMP)
	{
		advance();
		add_expr();
	}
}
void add_expr()
{
	mul_expr();
	if (tok == '+' || tok == '-')
	{
		advance();
		add_expr();
	}
}

















int main(int argc, char **argv)
{


	advance();
	program();
	printf("yes");


	return 0;
}