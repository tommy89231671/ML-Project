# -*- coding: utf-8 -*-
"""
Created on Fri Dec 01 00:13:41 2017

@author: tommy
"""
import matplotlib.pyplot as plt
import copy
import random as rand




          
fp=open("test1_data.txt","r")
str1=fp.read()
x=[]
y=[]
i=0
size=0;
while str1.find(' ',i)!=-1:
    x_end=str1.find(' ',i)
    x.append(float(str1[i:x_end-1]))
    y_end=str1.find('\n',x_end)
    y.append(float(str1[x_end+1:y_end-1]))
    i=y_end
    size=size+1
ux=[]
uy=[]
i=0
k=int(input("k clustering:"))
for i in range(k):
    rd=rand.randint(0,size-1)
    ux.append(x[rd])
    uy.append(y[rd])
    
    
    
"""start clustering"""
pathcount=0
while 1:
    pathcount=pathcount+1
    checkux=copy.copy(ux)
    checkuy=copy.copy(uy)
    r=[]
    ax=[]
    ay=[]
    xx=[]
    yy=[]
    for i in range(k):
        ax.append((0,0))
        ay.append((0,0))
        xx.append([])
        yy.append([])
    for i in range(size):
        tmp=0
        d=100000
        for j in range(k):
            if (x[i]-ux[j])*(x[i]-ux[j])+(y[i]-uy[j])*(y[i]-uy[j])<d:
                d=(x[i]-ux[j])*(x[i]-ux[j])+(y[i]-uy[j])*(y[i]-uy[j])
                tmp=j
        r.insert(i,tmp)
        xx[tmp].append(x[i])
        yy[tmp].append(y[i])
        ax[tmp]=(ax[tmp][0]+x[i],ax[tmp][1]+1)
        ay[tmp]=(ay[tmp][0]+y[i],ay[tmp][1]+1) 
    for i in range(k):
        ux[i]=ax[i][0]/ax[i][1]
        uy[i]=ay[i][0]/ay[i][1]
    if ux==checkux and uy==checkuy:
        break
#    ckc=0
#    for i in range(size):
#        if r[i]==ans[i]:
#            ckc=ckc+1
#    print(float(ckc)/float(size))
    for i in range(k):
        plt.plot(xx[i],yy[i],'o')
        plt.plot(ux[i],uy[i],'o')
    path=str(k)+"means1_"+str(pathcount)+".png"
    tit="kmeans   k="+str(k)
    plt.title(tit)
    plt.savefig(path)
    
    plt.show()
    