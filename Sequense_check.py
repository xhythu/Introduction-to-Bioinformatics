def sequense(sq1,sq2,alpha0,beta0,gamma0): #����
	n1=len(sq1)   #�õ�����
	n2=len(sq2)
	score_matrix = [] #�÷־���
	back_matrix= []   #���ݾ���
	for i in range(0, n2+1):   #������󲢳�ʼ��
		tmp1 = []
		tmp2 = []
		for j in range(0, n1+1):
			tmp1.append(0)
			tmp2.append(0)
		score_matrix.append(tmp1)
		back_matrix.append(tmp2)
	for j in range(1, n1+1):  #��һ�г�ʼ��
		score_matrix[0][j]=score_matrix[0][j-1]+gamma0
	for i in range(1, n2+1):  #��һ�г�ʼ��
		score_matrix[i][0]=score_matrix[i-1][0]+gamma0	
	temp=[0,0,0]   #�������ݷ���õ���ֵ
	for i in range(1,n2+1):   #ɨ�����
		for j in range(1,n1+1):
			temp[0]=score_matrix[i-1][j]+gamma0  #���Ϸ�
			temp[2]=score_matrix[i][j-1]+gamma0   #����
			if sq2[i-1]==sq1[j-1]:  #ƥ��
				temp[1]=score_matrix[i-1][j-1]+alpha0
			else:  #��ƥ��
				temp[1]=score_matrix[i-1][j-1]+beta0			
			score_matrix[i][j]=max(temp) 
			back_matrix[i][j]=temp.index(score_matrix[i][j])
	u=[]  #�÷־���ÿ�����ֵ
	n=[]  #�÷־���ÿ�е����ֵ��ÿ���е�λ��
	for i in range(0,n2+1):
		u.append(max(score_matrix[i]))#�洢ÿ�е����ֵ
		n.append(score_matrix[i].index(u[i])) #�洢ÿ�е����ֵ��ÿ���е�λ��
	temp0=max(u)   #�ܵ����ֵ
	temp_x=u.index(temp0)  #�ܵ����ֵ�����к�
	temp_y=n[temp_x]  #�ܵ����ֵ�����к�
	sq=['c' for i in range(temp0)]    #��󹫹��Ӵ�
	while temp0>0:  #ѭ��
		if back_matrix[i][j]==1:  #��������Ͻǻ��ݣ�˵�����ֹ����Ӵ��е��ַ� 
			sq[temp0-1]=sq1[j-1]  #�洢�ַ�
			temp0-=1				   #����ʣ���Ӵ��ĳ���
			i-=1				   #λ�ø���
			j-=1 			
		else:	#�����ƥ���λ�õĻ���ֻ����λ��
			if back_matrix[i][j]==0:   	  
				i-=1			
			else:
				j-=1
	same_sq=''.join(sq) #��ת
	return same_sq  #������󹫹��Ӵ�	