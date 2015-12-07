# -*- coding: utf-8 -*-
"""
Created on Sun Nov 10 16:00:29 2013

@author: Administrator
"""

sentence=raw_input()
sentence=sentence.lower()
word=sentence.split()

result=[]

for i in range(0,len(word)):
    single_word=word[i]
    if  single_word[0] in 'aeiou':
            single_word=single_word+'hay'
    
    elif  len(single_word)>=2 and single_word[0]=='q' and single_word[1]=='u' :
            single_word=single_word[2:]+'quay'
    
    else:
        n=0
        for a in range(0,len(single_word)):
            if (a==0 and single_word[a] in 'aeiou') or (a!=0 and single_word[a] in'aeiouy'):
                break
            n+=1
        single_word=single_word[n:]+single_word[:n]+'ay'
    print single_word,

