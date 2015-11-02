#include<stdio.h>			   //诸多头文件
#include<fstream> 
#include<string>
#include<iostream>
#include <stdlib.h>	 
using namespace std;	    
char * Sequense_check(string,string,int,int ,int);   //返回最大公共子串
int main(void)
{	
	string a=string(10,'c');
	ifstream fin("A:/学习/大四上/生物信息学概论/作业/Homework1/LongestCommonSeq.txt"); //打开序列信息文件，如有需要请修改路径			 
	string sq1;		  
	string sq2;
	getline(fin,sq1);		 //得到序列1
	getline(fin,sq2); 		//得到序列2										 
	fin.close();  
	int alpha0=1;			  //匹配得分
	int beta0=0;			  //不匹配得分
	int gamma0=0;			  //空位得分		  	
	char *same_sq=Sequense_check(sq1,sq2,alpha0,beta0,gamma0);//获得最大公共子串  	
	cout<<same_sq;    //输出最大公共子串
	return 0;
}
char * Sequense_check(string sq1,string sq2,int alpha0,int beta0,int gamma0) 
{	 //sq1和sq2是两条序列；score_matrix是得分矩阵，back_matrix是回溯矩阵，n1/n2是序列1/序列2的长度
	int n1=sq1.length();	 
	int n2=sq1.length();
	int i=0,j=0;
	int **score_matrix=new int*[n2+1];	   //得分矩阵
  	int **back_matrix=new int*[n2+1];	   //回溯矩阵
	for(i=0;i<=n2;i++)					   //初始化
	{
		score_matrix[i]=new int[n1+1];		
		back_matrix[i]=new int[n1+1];	
	}
    score_matrix[0][0]=0;	
	back_matrix[0][0]=0;
	for(j=1;j<=n1;j++)                             //第一行得分初始化	
	{
		score_matrix[0][j]=score_matrix[0][j-1]+gamma0;
		back_matrix[0][j]=0;
	}
	for(i=1;i<=n2;i++)     //第一列得分初始化	
	{
		score_matrix[i][0]=score_matrix[i-1][0]+gamma0; 
		back_matrix[i][0]=0;
	}
	int	temp[3]; //记录当前位置要回溯的三个方向反向更新得到的值
	for(i=1;i<=n2;i++)         //矩阵扫描    
	{												   
		for(j=1;j<=n1;j++)								 
		{	
			temp[0]=score_matrix[i-1][j]+gamma0;	//正上方
			temp[2]=score_matrix[i][j-1]+gamma0;	//正左方
			if(sq1[j-1]==sq2[i-1])					//左上角匹配   
				temp[1]=score_matrix[i-1][j-1]+alpha0;		
			else									 //左上角失配
				temp[1]=score_matrix[i-1][j-1]+beta0;
			if(temp[0]>=temp[1] && temp[0]>=temp[2])  //取三者的最大值作为当前位置的得分，并记录回溯方向	   
			{
				score_matrix[i][j]=temp[0];  
				back_matrix[i][j]=0;      //0代表向正上方回溯
			}
			else
			{
				if(temp[1]>temp[0] && temp[1]>=temp[2])	 
				{										 
					score_matrix[i][j]=temp[1];  		 
					back_matrix[i][j]=1; 			//1代表向左上角回溯，回溯的下一个字符一定是属于公共子串中的字符	   
				}
				else
				{
					score_matrix[i][j]=temp[2];  		 
					back_matrix[i][j]=2; 		   //2代表正左方回溯
				} 
			}	 		  
		}									   
	}	
	int temp0=0,temp_x=0,temp_y=0;	  //temp0:最大公共子串的长度，temp_x和temp_y对应公共子串最后一个字符在两个序列中的位置
	for(i=1;i<=n2;i++) 
	{			 
		for(j=1;j<=n1;j++)   //获得矩阵中得分最大的位置，最大得分即最大公共子串的长度  
		{
			if(score_matrix[i][j]>=temp0)
			{
				temp0=score_matrix[i][j];
				temp_x=i;
				temp_y=j;
			}	  										
		}
	}	
	i=temp_x;			  //回溯起始位置行号     
	j=temp_y;			  //回溯起始位置列号
	char *same_sq=new char[temp0];	 //最大公共子串	
	while(temp0>0) 				 //开始回溯
	{	
		if(back_matrix[i][j]==1)  //如果向左上角回溯，说明出现公共子串中的字符 
		{
			same_sq[temp0-1]=sq1[j-1];  //存储字符
			temp0--;					   //更新剩下子串的长度
			i--;					   //位置更新
			j--;	 			
		}	  
		else	//如果是匹配空位置的话，只更新位置
		{
			if(back_matrix[i][j]==0)   	  
				i--;				
			else
				j--;
			
		}
	}	 
	delete score_matrix;				 //销毁矩阵
	delete back_matrix;
	return same_sq;	  //返回最大公共子串
}	 