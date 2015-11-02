def sequense(sq1,sq2,alpha0,beta0,gamma0): #函数
	n1=len(sq1)   #得到长度
	n2=len(sq2)
	score_matrix = [] #得分矩阵
	back_matrix= []   #回溯矩阵
	for i in range(0, n2+1):   #构造矩阵并初始化
		tmp1 = []
		tmp2 = []
		for j in range(0, n1+1):
			tmp1.append(0)
			tmp2.append(0)
		score_matrix.append(tmp1)
		back_matrix.append(tmp2)
	for j in range(1, n1+1):  #第一行初始化
		score_matrix[0][j]=score_matrix[0][j-1]+gamma0
	for i in range(1, n2+1):  #第一列初始化
		score_matrix[i][0]=score_matrix[i-1][0]+gamma0	
	temp=[0,0,0]   #三个回溯方向得到的值
	for i in range(1,n2+1):   #扫描矩阵
		for j in range(1,n1+1):
			temp[0]=score_matrix[i-1][j]+gamma0  #正上方
			temp[2]=score_matrix[i][j-1]+gamma0   #正左方
			if sq2[i-1]==sq1[j-1]:  #匹配
				temp[1]=score_matrix[i-1][j-1]+alpha0
			else:  #不匹配
				temp[1]=score_matrix[i-1][j-1]+beta0			
			score_matrix[i][j]=max(temp) 
			back_matrix[i][j]=temp.index(score_matrix[i][j])
	u=[]  #得分矩阵每行最大值
	n=[]  #得分矩阵每行的最大值在每行中的位置
	for i in range(0,n2+1):
		u.append(max(score_matrix[i]))#存储每行的最大值
		n.append(score_matrix[i].index(u[i])) #存储每行的最大值在每行中的位置
	temp0=max(u)   #总的最大值
	temp_x=u.index(temp0)  #总的最大值所在行号
	temp_y=n[temp_x]  #总的最大值所在列号
	sq=['c' for i in range(temp0)]    #最大公共子串
	while temp0>0:  #循环
		if back_matrix[i][j]==1:  #如果向左上角回溯，说明出现公共子串中的字符 
			sq[temp0-1]=sq1[j-1]  #存储字符
			temp0-=1				   #更新剩下子串的长度
			i-=1				   #位置更新
			j-=1 			
		else:	#如果是匹配空位置的话，只更新位置
			if back_matrix[i][j]==0:   	  
				i-=1			
			else:
				j-=1
	same_sq=''.join(sq) #反转
	return same_sq  #返回最大公共子串	