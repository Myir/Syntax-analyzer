
%{
#include <stdio.h>
#include<string.h>
enum yytokentype {
	INT = 258,
	EOL = 259,
      CHAR,STR,VOID,ID,NUMBER,PRINT,WHILE,RETURN,ASSIGN,STRING,ELSE,CMP
};
char yylval_x[20];


%}


%%


"int"     {strcpy(yylval_x,yytext);  return INT;}
"char"    {strcpy(yylval_x,yytext);  return CHAR;}
"str"     {strcpy(yylval_x,yytext);  return STR;}
"void"    {strcpy(yylval_x,yytext);  return VOID;}
"print"   {return PRINT;}
"return"  {return RETURN;}
"while"   {return WHILE;}
"else"    {return ELSE;}
"+"|"-"|"*"|"/"|"{"|"}"|"("|")"|"["|"]"|","|";"|"=" { return yytext[0]; }
"-=" |"*="      {return ASSIGN;}
"=="|\>|\<  {return CMP;}
\".*\"    {strcpy(yylval_x,yytext);return STRING;}
[A-Za-z][A-Za-z0-9]* {strcpy(yylval_x,yytext);return ID; }
[0-9]+ {strcpy(yylval_x,yytext);return NUMBER; }
\n	|
[ \t] { /* ignore whitespace */ }
"#"    { return yytext[0];} 


%%


int yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
	return 0;
}

int yywrap()
{
	return 1;
}
