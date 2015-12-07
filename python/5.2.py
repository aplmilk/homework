# -*- coding: utf-8 -*-
"""
Created on Sat Nov 30 14:04:17 2013

@author: lenovo
"""



index=dict()


'input sentence in 100 line'

word_line=[]
for i in range (100):                   
    strings_input=raw_input()
    word_line.append(strings_input)



'create the index in dictionary  '

for i in range (100):                  
    word=word_line[i].split()               
    for n in word:                        #search the word
        if n not in index:
            index[n]=[i+1]
        else:   
            index[n].append(i+1)
for x in index:                           #delete the word which appears more than once
    index[x]=set(index[x])




'Query the keywords:AND OR OR'

            

while True:
    keywords = raw_input()                      #input the keyword
    a='first' 
    if keywords.split()==[]:                         #if the input is none
        break
    elif keywords[0:4]=='AND:':               #the patton start with AND:
        keyword = keywords[4:].split()
        if keyword==[]:                       # if the input is only 'AND:'
            break
        else:
            for i in range(0,len(keyword)):
                if keyword[i] in index:
                    if a == 'first':          # if the input word is the first word
                       a = index[keyword[i]]
                    else: 
                       a = a & index[keyword[i]]      
                else:
                     a='first'
                     break
        if a == set([]) or a=='first':
            print 'None'
        else:
            print str(sorted(a)).strip('[]') 
    elif keywords[0:3]=='OR:':                        #the patton start with AND:
        keyword = keywords[3:].split()
        if  keyword==[]:                          # if the input is only 'OR:'
                break
        else:
            for i in range(0,len(keyword)):
                if keyword[i] in index:
                    if a == 'first':          # if the input word is the first word
                       a = index[keyword[i]]
                    else: 
                        a = a | index[keyword[i]]      

        if a == set([]) or a=='first'  :
            print 'None'
        else:
            print str(sorted(a)).strip('[]')
                    
    else:                                       #another patton :
        keyword = keywords.split()
        for i in range(0,len(keyword)):
            
            if keyword[i] in index:
                if a == 'first':          # if the input word is the first word
                   a = index[keyword[i]]
                else: 
                   a = a & index[keyword[i]]      
            else:
                a='first'
                break
        if a == set([]) or a=='first'  : 
           print 'None'
        else:
          print str(sorted(a)).strip('[]')
          
    



    
       
    

   
