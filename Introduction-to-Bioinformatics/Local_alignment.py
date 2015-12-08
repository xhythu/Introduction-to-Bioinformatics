import os  #导入os
os.chdir('A:/学习/大四上/生物信息学概论/作业/Homework1/Python')  #转到序列信息存储路径
f=open("LongestCommonSeq.txt") #读取序列信息
sq1=f.readline()[:-1]  #第一条序列
sq2=f.readline()[:-1]   #第二天序列
alpha=1  #匹配
beta=0    #失配
gamma=0   #空位匹配
from Sequense_check import sequense  #从Sequense_check.py中导入sequense函数
same_sq=sequense(sq1,sq2,alpha,beta,gamma)  #调用函数
print(same_sq)  #输出最大公共子串