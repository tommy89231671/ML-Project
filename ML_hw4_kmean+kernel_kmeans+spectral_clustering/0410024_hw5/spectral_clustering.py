# -*- coding: utf-8 -*-
"""
Created on Wed Dec  6 01:08:44 2017

@author: tommy
"""
global str
import matplotlib.pyplot as plt
import copy
import random as rand
from numpy.linalg import eig
import numpy as np

def kmeans(U,u,data,k):
        checku=copy.deepcopy(u)
        #z=[0,0]
        a=list()
        for i in range(k):
            a.append([])
            for j in range(k):
                a[i].append((0,0))
        #print(a[2][2])
        xx=[]
        yy=[]
#        ss=[]
#        dd=[]
        r=[0]*size
        for i in range(k):
            xx.append([])
            yy.append([])
#            ss.append([])
#            dd.append([])
        for i in range(size):
            tmp=0
            d=100000
            for j in range(k):
                dd=0
                for l in range(k):
                    dd=dd+(U[i][l]-u[j][l])*(U[i][l]-u[j][l])
                if dd<d:
                    d=dd
                    tmp=j
            r[i]=tmp
#            z[tmp]=z[tmp]+1
            #print(d)
            xx[tmp].append(data[i][0])
            yy[tmp].append(data[i][1])
#            ss[tmp].append(U[i][0])
#            dd[tmp].append(U[i][1])
            for j in range(k):
                a[tmp][j]=(a[tmp][j][0]+U[i][0],a[tmp][j][1]+1)
        #print(r)
        for i in range(k):
            for j in range(k):
                u[i][j]=a[i][j][0]/a[i][j][1]
        for i in range(k):
            plt.plot(xx[i],yy[i],'o')
        plt.show()
        flag=1
        for i in range(k):
            for j in range(k):
                if checku[i][j]!=u[i][j]:
                    flag=0
                    break
            if flag==0:
                break
        #print(u)
        
        
#        ss=input("Enter:")
#        if ss=='e':
#            return
        if flag==1:
            return
        else:
            return kmeans(U,u,data,k)    
            
            
        


        

def weight(d1,d2):
    if d1==d2:
        return 0
    else:     
        return np.exp((pow(d1[0]-d2[0],2)+pow(d1[1]-d2[1],2))*100*(-0.5))
    
fp=open("test2_data.txt","r")
str=fp.read()

x=[]
y=[]
data=[]
i=0
k=2
size=0;
while str.find(' ',i)!=-1:
    x_end=str.find(' ',i)
    y_end=str.find('\n',x_end)
    data.append((float(str[i:x_end-1]),float(str[x_end+1:y_end-1])))
    i=y_end
    size=size+1

W=np.zeros((size,size), dtype=np.float)
D=np.zeros((size,size), dtype=np.float)
for i in range(size):
    tmp=0
    for j in range(size):
        W[i][j]=weight(data[i],data[j])
        tmp=tmp+weight(data[i],data[j])
    D[i][i]=tmp
L=D-W

eigvalue,eigvector=eig(L)
newdata=list()
idx = eigvalue.argsort()
eigvec=list()
eigvalue = eigvalue[idx]
eigvector=eigvector[idx]

#for i in idx:
#    newdata.append(data[i])
#    eigvec.append(eigvector[i])

#print(eigvector)



U=np.zeros((size,k), dtype=np.float)

for i in range(size):
    for j in range(k+1):
        if j!=0:
            U[i][j-1]=eigvector[j][i]
            
            
u=[]
for i in range(k):
    u.append(())
for i in range(k):
        rd=rand.randint(0,size-1)
        uu=[]
        for j in range(k):
            uu.append(U[rd][j])
        u[i]=uu

kmeans(U,u,data,k)



#
#for i in range(size):
#    if U[0][i]>U[1][i]:
#        ans1.append(newdata[i])
#    else:
#        ans2.append(newdata[i])
#for a in ans1:
#    plt.plot(a[0],a[1],'ro')
#for a in ans2:    
#    plt.plot(a[0],a[1],'bo')
#plt.show()