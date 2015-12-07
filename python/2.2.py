# -*- coding: utf-8 -*-
"""
Created on Sat Oct 19 17:05:34 2013

@author: lenovo
"""

a = list(xrange(1,1000000))

for i in xrange(1,1000000):
	if(a[i]!=0):
		for x in range((2*i),1000000,i):
			a[x] = 0
su = [x for x in a if x!=0]
def xun(n):
    return [str(n)[i:] + str(n)[:i] for i in xrange(len(str(n)))]
    
b = set([str(x) for x in su])
c = []

for x in [str(x) for x in su]:
    if '0' in x or '2' in x or '4' in x or '5' in x or '6' in x or '8' in x:
        continue
    else:
        c.append(2)
        c.append(5)
        if set(xun(x)).issubset(b):
            c.append(int(x))
d=[]
for x in c:
    if x not in d:
        d.append(x)
d.sort()

sum = 0
for x in d:
    if x in d:
        sum+=1
print sum