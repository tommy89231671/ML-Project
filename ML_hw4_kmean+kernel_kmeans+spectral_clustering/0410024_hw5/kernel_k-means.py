# -*- coding: utf-8 -*-
"""
Created on Fri Dec 01 22:24:11 2017

@author: tommy
"""
import matplotlib.pyplot as plt
import random as rand
import copy
import numpy as np
def kernel(d1,d2):
    return np.exp((pow(d1[0]-d2[0],2)+pow(d1[1]-d2[1],2))*0.05*(-0.5))
    
fp=open("test2_data.txt","r")
str1=fp.read()
x=[]
y=[]
data=[]
i=0
size=0;
while str1.find(' ',i)!=-1:
    x_end=str1.find(' ',i)
    x.append(float(str1[i:x_end-1]))
    y_end=str1.find('\n',x_end)
    y.append(float(str1[x_end+1:y_end-1]))
    data.append((float(str1[i:x_end-1]),float(str1[x_end+1:y_end-1])))
    i=y_end
    size=size+1
#ans=[]
#fp1=open("test1_ground.txt","r")
#str1=fp1.read()
#for i in range(len(str1)):
#    if i%2==0:
#          ans.append(int(str1[i]))

a=[[]]*size
k=int(input("Enter k clustering:"))
#
x=0
x1=0
r=[0]*size
count=[0]*k
#initialize a
s1=list()
s2=list()

"""initial 2"""
#for i in range(size):
##    if i<size/2:
###        a.append([1/size,0])
##        a[i]=[1/size,0]
##    else:
###        a.append([0,1/size])
##        a[i]=[0,1/size]
#    rd=rand.randint(0,1)
#    tmp=[0]*k
#    if rd==0:
#        
#        tmp[0]=1/size
#        a[i]=tmp
#        s1.append(data[i])
#        x=x+1
#    else:
#        tmp[1]=1/size
#        a[i]=tmp
#        s2.append(data[i])
#        x1=x1+1
#for i in range(x):
#    plt.plot(s1[i][0],s1[i][1],'ro')
#for i in range(x1):    
#    plt.plot(s2[i][0],s2[i][1],'bo')
#plt.show()
"""intitial k"""
xx=[]
yy=[]
for i in range(k):
    xx.append([])
    yy.append([])
for i in range(size):
    rd=rand.randint(0,k-1)
    r[i]=rd
    count[rd]=count[rd]+1
for i in range(size):
    tmp=[0]*k
    tmp[r[i]]=1/count[rd]
    a[i]=tmp
    xx[r[i]].append(data[i][0])
    yy[r[i]].append(data[i][1])
for i in range(k):
        plt.plot(xx[i],yy[i],'o')
tit="kernel kmeans   k="+str(k)
plt.title(tit)
plt.show()

c=copy.deepcopy(a)  

#print(x,xx)



#for i in range(k):
#    ax.append((0,0))
#    ay.append((0,0))
#for n in range(20):
pathcount=0
while 1: 
    pathcount=pathcount+1
    r=[0]*size
    xx=[]
    yy=[]
    for i in range(k):
        xx.append([])
        yy.append([])
    count=[0]*k
    third=[0]*k
    for j in range(k):
        for p in range(size):
                    for q in range(size):
                        third[j]=third[j]+a[p][j]*a[q][j]*kernel(data[p],data[q])

    for i in range(size):
            tmp=0
            d=100000 
            for j in range(k):
                second=0
                for n in range(size):
                    second=second+a[n][j]*kernel(data[i],data[n])
                if kernel(data[i],data[i])-2*second+third[j] < d:
                    d=kernel(data[i],data[i])-2*second+third[j]
                    tmp=j
            xx[tmp].append(data[i][0])
            yy[tmp].append(data[i][1])
            r[i]=tmp
            count[tmp]=count[tmp]+1
            
    for i in range(size):
        for j in range(k):
            if r[i]==j:
                a[i][j]=(1/count[r[i]])
            else:
                a[i][j]=0
        

        
    #print(count)
    for i in range(k):
        plt.plot(xx[i],yy[i],'o')
    
    path=str(k)+"kernel kmeans2_"+str(pathcount)+".png"
    tit="kernel kmeans   k="+str(k)
    plt.title(tit)
    plt.savefig(path)
    plt.show()
    
    if c==a:
        break            
    c=copy.deepcopy(a) 