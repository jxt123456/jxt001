#include<stdio.h>
#include<assert.h>

typedef struct
{
char * exp;
int pos;
int value;
}T_Env;

void AddSubMulDiv(T_Env * env);

void num (T_Env *env)
{
 env->value= env->exp[env->pos++]-'0';
}

int IsAddSub (char op)
{
   return '+' ==op || '-'==op;
}

void SkipOp(T_Env *pEnv)
{
pEnv->pos++;
}

int IsMulDiv (char op)
{
  return '*'==op || '/'==op;  
}

int IsValidOP (char op)
{
  return IsAddSub(op) || IsMulDiv(op);
}

int BaseCal(int left,char op,int right)
{
 switch(op)
 {
   case '+':
    return left+right;
   case '-':
    return left-right;
   case '*':
    return left*right;
   case '/':
    return left/right;
   default:
   return 0;  
 }
}

typedef void (*FUN_CALL)(T_Env *Env);
typedef int (*FUN_ISOP)(char op);

void Common(T_Env* env,FUN_CALL funCall,FUN_ISOP isop)
{
   int value;
   char op;
   funCall(env);
   value=env->value;
   for(op=env->exp[env->pos];isop(op);op=env->exp[env->pos])
   {
    SkipOp(env);
    funCall(env);
    value=BaseCal(value,op,env->value);
   }
   env->value=value;
}

void bracket(T_Env *env)
{
  char op;
  op=env->exp[env->pos];
  if(op=='(')
  {
    SkipOp(env);
    AddSubMulDiv(env);
    SkipOp(env);
  }
  else
  {
    num(env);
  }
}

void MulDiv(T_Env *env)
{
  Common(env,bracket,IsMulDiv);

}

void AddSubMulDiv(T_Env * env)
{
    Common(env,MulDiv,IsAddSub);
}
int cala(char *input)
{
 T_Env env;
 env.exp=input;
 env.pos=0;
 env.value=0;
 AddSubMulDiv(&env);
 return env.value;

}
int main()
{

assert(cala("1+2")==3);
assert(cala("3-1")==2);
assert(cala("3*3")==9);
assert(cala("9/3")==3);
assert(cala("2*3/3*2")==4);
assert(cala("1+3*5+2+5*4")==38);
assert(cala("3*(3+5)+((5*4)+6)/2")==37);
return 0;

}
