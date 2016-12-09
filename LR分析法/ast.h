

typedef struct _ast ast;
typedef struct _ast *past;
struct _ast{
	char ivalue[30];
	char nodeType[30];
	past left;
	past mid;
	past right;
};
void showAst(past node, int nest);
past newNum(char* x);
past newSTR(char* x);
past newID(char* x);
past newTYPE(char* x);
past newExpr(char* nodeType, past left, past mid, past right);