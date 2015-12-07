# -*- coding: utf-8 -*-
"""
Created on Wed Sep 23 18:23:00 2015

@author: lenovo
"""

from time import clock


service=[]
req=[]


##----------read data----------------


#service
for i in open('SERVICE.txt'):
     service.append(i.split(' ')[0].split('-'))     #可尝试速度改进
     service.append(float(i.split()[2]))
     service.append(float(i.split()[4]))

 
#req            
for i in open('REQ.txt'):
    req.append(i.split('(')[1].split(')')[0].split(','))
    
#process
f=open('PROCESS.txt')
for i in range(1):
    print "--------------process",i+1,":--------------",'\n'
    pro=f.readline()
    process=[]
    for j in pro:
       if j>='A' and j <='Z' and j not in process:
            process.append(j)
            

    start=clock()
    ##----------select data----------------
    std_quality=float(req[i][0])
    std_money=float(req[i][1])
    
    element_num=len(process)    
    
        
    ser=[]
    number=[]   #统计总数
    j=0
    a=-1
    while(j<len(service)/3):
        if(service[j*3][0] in process):
            number.append(0) #初始化
            a=a+1

            for k in range(500):
                b=j+k
                m=service[b*3+1]
                if(m>std_quality): #不取等
                    n=service[b*3+2]
                    if(n<std_money):
                        ser.append(service[b*3:b*3+3])
                        number[a]=number[a]+1 #记录每个活动总数
                      
        j=j+500

    ser.sort(key=lambda x:(x[0][0],x[1]))      #tr从小到大排

  #  print number
#二次筛
    k=0
    i=0
    while(k!=len(ser)):
        j=number[i]-1
        tp_sep=ser[k+j][2]
        tr_first=ser[k+j][1]
        j=j-1   #以第一个元素为基准，从第二个元素开始(此时第一个元素总会留下来)

        while(j!=-1):
            if(ser[k+j][2]<tp_sep):
                if(ser[k+j][1]==tr_first):
                    ser.remove(ser[k+j+1])
                    number[i]=number[i]-1  
                else:   #小于
                    tr_first=ser[k+j][1]
                tp_sep=ser[k+j][2]
                j=j-1

            else:        
                ser.remove(ser[k+j])
                number[i]=number[i]-1
                j=j-1
                
        k=k+number[i]
        i=i+1
  #  print number

    for j in range(element_num-1):
        number[j+1]=number[j]+number[j+1]


    ##----------choose_service----------------
    result=[]  #保存合格服务(过程中)
    final=[]    #最佳
    travel=[]  #遍历辅助
    tra_tr=[]
    tra_tp=[]
    for i in range(element_num):   #初始化
        result.append(0)
        final.append(0)
        tra_tr.append(1)    
        tra_tp.append(0)  
        
     
    for i in range(element_num):    #记录每个元素最后一个数下标
        travel.append(number[i]-1) 

    
    q=0  #初始化
    big_q=0
    flag=1
    n=element_num-1    #从最后一个活动开始遍历
    num0=number[0]
        
    while(flag==1):
        while(n!=0):
            x=travel[n]   #该活动第一个元素(或上次访问到的最后一个元素),x从0开始
            board=number[n-1]-1
            if(n==element_num-1):
                tr=1
                tp=0
            else:
               tr=tra_tr[n+1]
               tp=tra_tp[n+1]  
            while(1):   #找到或最后一个停止循环(该循环内n相同)
               if(x==board):    #超出该层范围（表明该层最后一个已经检测过）
                    travel[n]=number[n]-1   
                    n=n+1
                    if(n==element_num):
                        flag=0  #超出范围，表明所有都遍历结束
                    break             
               fresh_tr=tr*ser[x][1]
               if(fresh_tr>std_quality):
                   fresh_tp=tp+ser[x][2]  
                   if(fresh_tp>=std_money):
                       x=x-1
                   else:
                        result[n]=ser[x][0]
                        tra_tr[n]=fresh_tr
                        tra_tp[n]=fresh_tp 
                        travel[n]=x-1       #如果x已是最后一个数则超出范围
                        n=n-1
                        if(n==0):
                            tr1=tra_tr[1]
                            tp1=tra_tp[1]
                        break
               else: 
                   x=board
            if(flag==0):
                break
        
        if(n==0):
            i=num0-1
            while(i!=0):
                fresh_tr=tr1*ser[i][1]
                if(fresh_tr>std_quality):
                    fresh_tp=tp1+ser[i][2]
                    if(fresh_tp<std_money):
                         new_q=fresh_tr-fresh_tp/100
                         if(new_q>big_q):
                             result[0]=ser[i][0]
                             tra_tr[0]=fresh_tr  #记录TR
                             tra_tp[0]=fresh_tp  #记录TP
                             big_q=new_q  
                             for p in range(element_num):  #记录最佳
                                 final[p]=result[p]
                else:
                    break
                  
                i=i-1   
        n=n+1  #返回上一层

    finish=clock()

    ##----------print_service----------------
    
    for j in pro:
       if (j in process):
           n=0
           while(final[n][0]!=j):
               n=n+1
           print j,"-",final[n][1],
       else:
        print j,
    
    print"Reliability=",tra_tr[0],",Cost=",tra_tp[0],",Q=",big_q,'\n'
    print "start:",start,"\nfinish:",finish    
    print "time:",finish-start

