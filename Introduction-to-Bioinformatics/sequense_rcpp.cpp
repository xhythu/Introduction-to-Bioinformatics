#include <Rcpp.h>
#include<fstream> 
#include<string>
#include<iostream>
#include <stdlib.h>
using namespace Rcpp;
using namespace std;

// [[Rcpp::export]]
string sequense(string sq1,string sq2,int alpha0,int beta0,int gamma0) 
{	 //sq1和sq2是两条序列；score_matrix是得分矩阵，back_matrix是回溯矩阵
  int n1=sq1.length();	 
  int n2=sq1.length();
  NumericMatrix score_matrix(n2+1,n1+1);//得分矩阵
  NumericMatrix back_matrix(n2+1,n1+1);//回溯矩阵
  int i=0,j=0;
  for(j=0;j<=n1;j++)      //第一行得分初始化	
    score_matrix(0,j)=i*gamma0;
  for(i=0;i<=n2;i++)     //第一列得分初始化
    score_matrix(i,0)=i*gamma0; 
  NumericVector	temp(3); //记录当前位置要回溯的三个方向反向更新得到的值
  for(i=1;i<=n2;i++)         //矩阵扫描    
  {												   
    for(j=1;j<=n1;j++)								 
    {	
      temp[0]=score_matrix(i-1,j)+gamma0;	//正上方
      temp[2]=score_matrix(i,j-1)+gamma0;	//正左方
      if(sq1[j-1]==sq2[i-1])					//左上角匹配   
        temp[1]=score_matrix(i-1,j-1)+alpha0;		
      else									 //左上角失配
        temp[1]=score_matrix(i-1,j-1)+beta0;
      score_matrix(i,j)=max(temp); //取最大值
      back_matrix(i,j)=which_max(temp);//回溯矩阵记录回溯方向;0:正上方，1:左上角,2:正左方
    }									   
  }
  int temp0=max(score_matrix); //得分矩阵中最高分
  for(i=1;i<=n2;i++)         //矩阵扫描,找出最高分所在的行列号
  {
    for(j=1;j<=n1;j++)
      if(score_matrix(i,j)==temp0)//如果找到
        break;//退出
    if(j<=n1)//如果里层循环因为找到而终止
      break;//退出
  }
  string same_sq=string(temp0,'c');	 //最大公共子串	
  while(temp0>0) 				 //开始回溯
  {	
    if(back_matrix(i,j)==1)  //如果向左上角回溯，说明出现公共子串中的字符 
    {
      same_sq[temp0-1]=sq1[j-1];  //存储字符
      temp0--;					   //更新剩下子串的长度
      i--;					   //位置更新
      j--;	 			
    }	  
    else	//如果是匹配空位置的话，只更新位置
    {
      if(back_matrix(i,j)==0)   	  
        i--;				
      else
        j--;
      
    }
  }	 
  return same_sq;	  //返回最大公共子串
}