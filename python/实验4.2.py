# -*- coding: utf-8 -*-
"""
Created on Sun Nov 10 16:00:29 2013

@author: Administrator
"""

import re
sentence=raw_input()                
sentence=sentence.lower()
word=sentence.split()                                # devide the sentence into words


for i in range(0,len(word)):            
    single_word=str(word[i])
    if  re.match('[aeiou]',single_word):              #check if the word start with aeiou
            single_word=single_word+'hay'
    
    elif  len(single_word)>=2 and re.match('qu',single_word) :     #check if the word start with qu
            single_word=single_word[2:]+'quay'
    
    else:                                                    #another situation    
        num=0
        for a in range(0,len(single_word)):                 #find the first aieouy
             n=single_word[0+a:1+a]
             if (a==0 and re.match('[aeiou]',n)) or (a!=0 and re.match('[aeiouy]',n)):
                single_word=single_word[a:]+single_word[:a]+'ay'
                break
             else:
                 num+=1
        if num == len(single_word):
            single_word=single_word+'ay'
    print single_word,                                     #print the result
             

