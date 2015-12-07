# -*- coding: utf-8 -*-
"""
Created on Mon Nov 25 21:32:17 2013

@author: lenovo
"""

index=dict()


'input sentence in 100 line'

word_line=[]
for i in range (3):                   
    strings_input=raw_input()
    word_line.append(strings_input)



'create the index in dictionary  '

for i in range (3):                  
    word=word_line[i].split()               
    for n in word:                        #search the word
        if n not in index:
            index[n]=[i+1]
        else:   
            index[n].append(i+1)
for x in index:                           #delete the word which appears more than once
    index[x]=list(set(index[x]))




'print the dictionary in order  '  
   
i=[]                                   
for x in index:
    i.append(x)                       #put the strings in dictionary into the list
i.sort()
for n in i:                                     #print in other line
    print n,':',str(set(index[n]))[5:-2]        
    
    
    
    
'Query the keywords'   
   
while True:                               #start the circulation 
   
    keywords = raw_input()
    keyword = keywords.split()
    length=len(keyword) 
    a='first'
    if length == 0:                        #if the input is none
        break
    else:
        for i in range(len(keyword)):
            if keyword[i] in index:
                if a == 'first':          # if the input word is the first word
                   a = index[keyword[i]]
                else: 
                    a = a & index[keyword[i]]      
            else:
                print'None'
                break
    if a == set([]) : 
        print 'None'
    else:
        print str(sorted(a)).strip('[]') 
            
            
