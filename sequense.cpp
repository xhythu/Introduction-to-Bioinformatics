#include<stdio.h>			   //���ͷ�ļ�
#include<fstream> 
#include<string>
#include<iostream>
#include <stdlib.h>	 
using namespace std;	    
char * Sequense_check(string,string,int,int ,int);   //������󹫹��Ӵ�
int main(void)
{	
	string a=string(10,'c');
	ifstream fin("A:/ѧϰ/������/������Ϣѧ����/��ҵ/Homework1/LongestCommonSeq.txt"); //��������Ϣ�ļ���������Ҫ���޸�·��			 
	string sq1;		  
	string sq2;
	getline(fin,sq1);		 //�õ�����1
	getline(fin,sq2); 		//�õ�����2										 
	fin.close();  
	int alpha0=1;			  //ƥ��÷�
	int beta0=0;			  //��ƥ��÷�
	int gamma0=0;			  //��λ�÷�		  	
	char *same_sq=Sequense_check(sq1,sq2,alpha0,beta0,gamma0);//�����󹫹��Ӵ�  	
	cout<<same_sq;    //�����󹫹��Ӵ�
	return 0;
}
char * Sequense_check(string sq1,string sq2,int alpha0,int beta0,int gamma0) 
{	 //sq1��sq2���������У�score_matrix�ǵ÷־���back_matrix�ǻ��ݾ���n1/n2������1/����2�ĳ���
	int n1=sq1.length();	 
	int n2=sq1.length();
	int i=0,j=0;
	int **score_matrix=new int*[n2+1];	   //�÷־���
  	int **back_matrix=new int*[n2+1];	   //���ݾ���
	for(i=0;i<=n2;i++)					   //��ʼ��
	{
		score_matrix[i]=new int[n1+1];		
		back_matrix[i]=new int[n1+1];	
	}
    score_matrix[0][0]=0;	
	back_matrix[0][0]=0;
	for(j=1;j<=n1;j++)                             //��һ�е÷ֳ�ʼ��	
	{
		score_matrix[0][j]=score_matrix[0][j-1]+gamma0;
		back_matrix[0][j]=0;
	}
	for(i=1;i<=n2;i++)     //��һ�е÷ֳ�ʼ��	
	{
		score_matrix[i][0]=score_matrix[i-1][0]+gamma0; 
		back_matrix[i][0]=0;
	}
	int	temp[3]; //��¼��ǰλ��Ҫ���ݵ�������������µõ���ֵ
	for(i=1;i<=n2;i++)         //����ɨ��    
	{												   
		for(j=1;j<=n1;j++)								 
		{	
			temp[0]=score_matrix[i-1][j]+gamma0;	//���Ϸ�
			temp[2]=score_matrix[i][j-1]+gamma0;	//����
			if(sq1[j-1]==sq2[i-1])					//���Ͻ�ƥ��   
				temp[1]=score_matrix[i-1][j-1]+alpha0;		
			else									 //���Ͻ�ʧ��
				temp[1]=score_matrix[i-1][j-1]+beta0;
			if(temp[0]>=temp[1] && temp[0]>=temp[2])  //ȡ���ߵ����ֵ��Ϊ��ǰλ�õĵ÷֣�����¼���ݷ���	   
			{
				score_matrix[i][j]=temp[0];  
				back_matrix[i][j]=0;      //0���������Ϸ�����
			}
			else
			{
				if(temp[1]>temp[0] && temp[1]>=temp[2])	 
				{										 
					score_matrix[i][j]=temp[1];  		 
					back_matrix[i][j]=1; 			//1���������Ͻǻ��ݣ����ݵ���һ���ַ�һ�������ڹ����Ӵ��е��ַ�	   
				}
				else
				{
					score_matrix[i][j]=temp[2];  		 
					back_matrix[i][j]=2; 		   //2�������󷽻���
				} 
			}	 		  
		}									   
	}	
	int temp0=0,temp_x=0,temp_y=0;	  //temp0:��󹫹��Ӵ��ĳ��ȣ�temp_x��temp_y��Ӧ�����Ӵ����һ���ַ������������е�λ��
	for(i=1;i<=n2;i++) 
	{			 
		for(j=1;j<=n1;j++)   //��þ����е÷�����λ�ã����÷ּ���󹫹��Ӵ��ĳ���  
		{
			if(score_matrix[i][j]>=temp0)
			{
				temp0=score_matrix[i][j];
				temp_x=i;
				temp_y=j;
			}	  										
		}
	}	
	i=temp_x;			  //������ʼλ���к�     
	j=temp_y;			  //������ʼλ���к�
	char *same_sq=new char[temp0];	 //��󹫹��Ӵ�	
	while(temp0>0) 				 //��ʼ����
	{	
		if(back_matrix[i][j]==1)  //��������Ͻǻ��ݣ�˵�����ֹ����Ӵ��е��ַ� 
		{
			same_sq[temp0-1]=sq1[j-1];  //�洢�ַ�
			temp0--;					   //����ʣ���Ӵ��ĳ���
			i--;					   //λ�ø���
			j--;	 			
		}	  
		else	//�����ƥ���λ�õĻ���ֻ����λ��
		{
			if(back_matrix[i][j]==0)   	  
				i--;				
			else
				j--;
			
		}
	}	 
	delete score_matrix;				 //���پ���
	delete back_matrix;
	return same_sq;	  //������󹫹��Ӵ�
}	 