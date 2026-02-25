/*
Title: Design and Develop a C program to solve simple computational problems using arithmetic expressions and use of each operator leading to simulation of a commercial calculator.
Problem Description: The program should prompt the user to input an arithmetic expression, the calculator should support the following operators: Addition (+), subtraction (-), Multiplication (*), Division(/) and modulus (%) and also should handle the error such as division by zero , unrecognized operator.
Method: switch Statement.
*/
#include<stdio.h>
#include<stdlib.h>
int main(){
int num1,num2;
char op;
float result;
printf("Enter a Expression:");
scanf("%d%c%d",&num1,&op,&num2);
switch(op){
    case'+':
    result=num1+num2;
    printf("Result is %f",result);
    break;
    case'-':
    result=num1-num2;
    printf("Result is %f",result);
      break;
     case'*':
    result=num1*num2;
    printf("Result is %f",result);
      break;
     case'/':
     if(num2==0){
        printf("Division not possible");
        exit(0);
     }
     else{
    result=num1/num2;
    printf("Result is %f",result);
    break;
     }
     case'%':
    result=num1%num2;
    printf("Result is %f",result);
      break;
      default:
      printf("Invalid operator");
}
return 0;
}