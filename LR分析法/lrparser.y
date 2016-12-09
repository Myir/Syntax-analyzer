%{

#include <stdio.h>
#include "ast.h"
int yylex(void);
void yyerror(char *);

%}

%union{
    char       Str[30];
	past		pAst;
};

%nonassoc ')'
%nonassoc ELSE

%token <Str> NUMBER 
%token <Str> ID STRING 
%token <Str> INT CHAR STR VOID RETURN WHILE ELSE ASSIGN CMP IF SCAN PRINT
%type  <pAst> program external_declaration type declarator function_definition declaration compound_statement init_declarator_list init_declarator intstr_list initializer parameter_list parameter  statement direct_declarator expression_statement expr cmp_expr add_expr mul_expr primary_expr selection_statement iteration_statement expr_list id_list jump_statement print_statement scan_statement begin_scope end_scope statement_list assign_expr x

%%

x:program                                {showAst($1,0);}
    ;
	
program
    : external_declaration               { $$=newExpr("program",$1,NULL,NULL);}
    | program external_declaration       { $$=newExpr("program",$1,$2,NULL);}
    ;
	
external_declaration: function_definition  { $$=newExpr("external_declaration",$1,NULL,NULL);}
                    | declaration          { $$=newExpr("external_declaration",$1,NULL,NULL);}
                    ;
	


function_definition: type declarator compound_statement { $$=newExpr("function_definition",$1,$2,$3);}
                    ;
				
declaration: type init_declarator_list ';'              { $$=newExpr("declaration",$1,$2,NULL);}
           ;				
		   
init_declarator_list: init_declarator                   { $$=newExpr("init_declarator_list",$1,NULL,NULL);}
                    | init_declarator_list ',' init_declarator { $$=newExpr("init_declarator_list",$1,$3,NULL);}
                    ;
init_declarator: declarator                             { $$=newExpr("init_declarator",$1,NULL,NULL);}
               | declarator '=' add_expr                { $$=newExpr("init_declarator",$1,$3,NULL);}
               | declarator '=' '{' intstr_list '}'     { $$=newExpr("init_declarator",$1,$4,NULL);}
			   ;
			  
intstr_list: initializer                                { $$=newExpr("intstr_list",$1,NULL,NULL);}
           | intstr_list ',' initializer                { $$=newExpr("intstr_list",$1,$3,NULL);}
           ;	

initializer: NUMBER                                     {$$ = newExpr("initializer",newNum($1),NULL,NULL);}
           | STRING		                                {$$ = newExpr("initializer",newSTR($1),NULL,NULL);}
           ;

declarator: direct_declarator                           { $$=newExpr("declarator",$1,NULL,NULL);}
          ;
direct_declarator: ID                                        { $$=newExpr("direct_declarator",newID($1),NULL,NULL);}
                 | direct_declarator '(' parameter_list ')'  { $$=newExpr("direct_declarator",$1,$3,NULL);}
                 | direct_declarator '(' ')'                 { $$=newExpr("direct_declarator",$1,NULL,NULL);}
                 | ID '[' expr ']'                           { $$=newExpr("direct_declarator",newID($1),$3,NULL);}
                 | ID '[' ']'	                             { $$=newExpr("direct_declarator",newID($1),NULL,NULL);}
				 ;
parameter_list
        : parameter                       { $$=newExpr("parameter_list",NULL,NULL,$1);}
        | parameter_list ',' parameter    { $$=newExpr("parameter_list",NULL,$1,$3);}
        ;

parameter
        : type ID                         { $$=newExpr("parameter",NULL,$1,newID($2));}
        ;

type                                      
        : INT                             {$$ = newExpr("type",newTYPE($1),NULL,NULL);}
        | STR                             {$$ = newExpr("type",newTYPE($1),NULL,NULL);}
        | VOID                            {$$ = newExpr("type",newTYPE($1),NULL,NULL);}
        ;				 

statement: compound_statement              { $$=newExpr("statement",$1,NULL,NULL);}
             | expression_statement        { $$=newExpr("statement",$1,NULL,NULL);}
             | selection_statement         { $$=newExpr("statement",$1,NULL,NULL);}
             | iteration_statement         { $$=newExpr("statement",$1,NULL,NULL);}
             | jump_statement              { $$=newExpr("statement",$1,NULL,NULL);}
             | print_statement             { $$=newExpr("statement",$1,NULL,NULL);}
             | scan_statement              { $$=newExpr("statement",$1,NULL,NULL);}
             | declaration                 { $$=newExpr("statement",$1,NULL,NULL);}
			 ;
			 
compound_statement: begin_scope end_scope             { $$=newExpr("compound_statement",$1,$2,NULL);}
                  | begin_scope statement_list end_scope { $$=newExpr("compound_statement",$1,$2,$3);}
                  ;
				  
    begin_scope: '{'                                  { $$=newExpr("begin_scope",NULL,NULL,NULL);}
               ;
			   
    end_scope: '}'                                    { $$=newExpr("end_scope",NULL,NULL,NULL);}
             ;
			 
    statement_list: statement                          { $$=newExpr("statement_list",$1,NULL,NULL);}
                  | statement_list statement           { $$=newExpr("statement_list",$1,$2,NULL);}
                  ;
				  
    expression_statement: ';'                          { $$=newExpr("expression_statement",NULL,NULL,NULL);}
                        | expr ';'                     { $$=newExpr("expression_statement",$1,NULL,NULL);}
                        ;
						
    selection_statement: IF '(' expr ')' statement     { $$=newExpr("selection_statement",$3,$5,NULL);}
                       | IF '(' expr ')' statement ELSE statement { $$=newExpr("selection_statement",$3,$5,$7);}
                       ;
					   
    iteration_statement: WHILE '(' expr ')' statement			{$$=newExpr("selection_statement",$3,$5,NULL);}
                       ;
					   
    jump_statement: RETURN ';'           { $$=newExpr("jump_statement",NULL,NULL,NULL);}
                  | RETURN expr ';'      { $$=newExpr("jump_statement",$2,NULL,NULL);}
                  ;
				  
    print_statement: PRINT ';'              { $$=newExpr("print_statement",NULL,NULL,NULL);}
                   | PRINT expr_list ';'    { $$=newExpr("print_statement",$2,NULL,NULL);}
                   ;
				   
    scan_statement: SCAN id_list ';'        { $$=newExpr("scan_statement",$2,NULL,NULL);}
                  ;

expr: assign_expr                           { $$=newExpr("expr",$1,NULL,NULL);}
    ;
	
assign_expr: cmp_expr                        { $$=newExpr("assign_expr",$1,NULL,NULL);}
           | ID ASSIGN assign_expr           { $$=newExpr("assign_expr",newID($1),$3,NULL);}
           | ID '=' assign_expr              { $$=newExpr("assign_expr",newID($1),$3,NULL);}
           | ID '[' expr ']' '=' assign_expr { $$=newExpr("assign_expr",newID($1),$3,$6);}
           ;
		   
cmp_expr
    : add_expr                               { $$=newExpr("cmp_expr",NULL,NULL,$1);}
    | cmp_expr CMP add_expr                  { $$=newExpr("cmp_expr",NULL,$1,$3);}
    ;

add_expr
    : mul_expr                               { $$=newExpr("add_expr",NULL,NULL,$1);}
    | add_expr '+' mul_expr                  { $$=newExpr("add_expr",NULL,$1,$3);}
    | add_expr '-' mul_expr                  { $$=newExpr("add_expr",NULL,$1,$3);}
    ;

mul_expr
    : primary_expr                           { $$=newExpr("mul_expr",NULL,NULL,$1);}
    | mul_expr '*' primary_expr              { $$=newExpr("mul_expr",NULL,$1,$3);}
    | mul_expr '/' primary_expr              { $$=newExpr("mul_expr",NULL,$1,$3);}
    | mul_expr '%' primary_expr              { $$=newExpr("mul_expr",NULL,$1,$3);}
    | '-' primary_expr                       { $$=newExpr("mul_expr",NULL,NULL,$2);}
    ;

primary_expr: ID '(' expr_list ')'           { $$=newExpr("primary_expr",newID($1),NULL,$3);}
            | ID '(' ')'                     { $$=newExpr("primary_expr",newID($1),NULL,NULL);}
            | '(' expr ')'                   { $$=newExpr("primary_expr",$2,NULL,NULL);}
            | ID                             { $$=newExpr("primary_expr",newID($1),NULL,NULL);}
            | initializer                    { $$=newExpr("primary_expr",$1,NULL,NULL);}
            | ID '[' expr ']'                { $$=newExpr("primary_expr",newID($1),NULL,$3);}
		    ;

expr_list
    : expr                            { $$=newExpr("expr_list",NULL,NULL,$1);}
    | expr_list ',' expr              { $$=newExpr("expr_list",NULL,$1,$3);}
    ;

id_list
    : ID                              { $$=newExpr("id_list",NULL,NULL,newID($1));}
    | id_list ',' ID                  { $$=newExpr("id_list",NULL,$1,newID($3));}
    ;

%%


