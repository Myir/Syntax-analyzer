
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "lrparser.tab.h"

void yyerror(char *);
%}


%%


"int"     {strcpy(yylval.Str,yytext);  return INT;}
"char"    {strcpy(yylval.Str,yytext);  return CHAR;}
"str"     {strcpy(yylval.Str,yytext);  return STR;}
"void"    {strcpy(yylval.Str,yytext);  return VOID;}
"print"   {return PRINT;}
"return"  {return RETURN;}
"while"   {return WHILE;}
"else"    {return ELSE;}
"if" 			{return IF;}
"scan" 			{return SCAN;}
"+"|"-"|"/"|"*"|"%"|"="|"{"|"}"|"("|")"|"["|"]"|";"|","|"!="|"++"|"--"|"&"|"&&"|"^"|"||" { return yytext[0]; }
"-=" |"*="      {return ASSIGN;}
"=="|">"|"<"  {return CMP;}                                                                                                                                                                                                                                                           
\".*\"    {strcpy(yylval.Str,yytext);return STRING;}
[A-Za-z][A-Za-z0-9]* {strcpy(yylval.Str,yytext);return ID; }
[0-9]+ {strcpy(yylval.Str,yytext);  return NUMBER; }
[ \t\r\n]+ { /* ignore whitespace */ }
"//".*		    {/*ingore explanation*/}
"/*".*"*/"	    {/*ingore explanation*/}

%%



int yywrap()
{
	return 1;
}
