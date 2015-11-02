library("Rcpp") #加载Rcpp包
sourceCpp("sequense.cpp")#加载cpp文件
setwd('A:/学习/大四上/生物信息学概论/作业/Homework1/R') #转到序列信息存储路径
rt<-readLines("LongestCommonSeq.txt")  #读出两条序列
sq1<-unlist(strsplit(rt[1],''))        #分割成字符串
sq2<-unlist(strsplit(rt[2],''))
alpha0=1  #匹配值
beta0=0   #失配值
gamma0=0   #空位匹配值
sq1<-paste(sq1,sep="",collapse = "")  #字符串转string
sq2<-paste(sq2,sep="",collapse = "")
r1<-sequense(sq1,sq2,alpha0,beta0,gamma0) #调用函数，返回最大公共子串
print(r1)   #打印最大公共子串
