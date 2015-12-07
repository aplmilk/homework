# -*- coding: utf-8 -*-
'''This is a program that can calculate the optimized combination of 
different activities.'''
import time
#@profile

KEEP = 5
#create a service dictionary indexed by A to Z
START = time.clock()
PROCESS_FILE = open("PROCESS.TXT")
PROCESS = PROCESS_FILE.readlines()
DICT_OF_SERVICE = {'A':[], 'B':[], 'C':[], 'D':[], 'E':[], 'F':[], \
    'G':[] , 'H':[], 'I':[],'J':[], 'K':[], 'L':[], 'M':[], 'N':[]}
for service_line in open("SERVICE.TXT"):
    curList = service_line.split(' ')
    index = curList[0][0]
    DICT_OF_SERVICE[index].append([int(curList[0][2:]), \
    float(curList[2]), float(curList[4])])
    
for keyOfServDict in DICT_OF_SERVICE.keys():
    DICT_OF_SERVICE[keyOfServDict].sort(key=lambda x: x[2])
    
    
#create process list including process dictionary by given PROCESS
DICT_OF_PROCESS = []
NOTATION_OF_PROCESS = []
RESULT = []
INDEX_OF_PROCESS = 0
for process_line in PROCESS:
    DICT_OF_PROCESS.append({})
    NOTATION_OF_PROCESS.append({})
    RESULT.append([1, 0, 0])
    for edge_of_dag in process_line.split(')')[:-1]:
        DICT_OF_PROCESS[INDEX_OF_PROCESS][edge_of_dag[-1]] = []
        DICT_OF_PROCESS[INDEX_OF_PROCESS][edge_of_dag[-3]] = []
        NOTATION_OF_PROCESS[INDEX_OF_PROCESS][edge_of_dag[-1]] = 0
        NOTATION_OF_PROCESS[INDEX_OF_PROCESS][edge_of_dag[-3]] = 0
    INDEX_OF_PROCESS += 1
#  select items whose price is lower than given standard
#  and the reliability is higher than given standard.
#  Then sort them by the offset from the minimum standard
#  of Q and select first KEEPNumber service.
LIST_OF_REQ = []
INDEX_OF_PROCESS = 0
for REQline in open("REQ.TXT"):
    RP = REQline[1:-2].split(',')
    LIST_OF_REQ.append((float(RP[0]), float(RP[1]), \
    len(DICT_OF_PROCESS[INDEX_OF_PROCESS])))
    INDEX_OF_PROCESS += 1
for INDEX_OF_CUR_PROCESS in range(0, 4):
    cur_reliability = LIST_OF_REQ[INDEX_OF_CUR_PROCESS][0]
    cur_price = LIST_OF_REQ[INDEX_OF_CUR_PROCESS][1]
    curNumOfNodes = LIST_OF_REQ[INDEX_OF_CUR_PROCESS][2]
    for key_of_process in DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS].keys():
        for curServ in DICT_OF_SERVICE[key_of_process]:
            if curServ[-1] < cur_price:
                if curServ[1] > cur_reliability:
                    DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][key_of_process].\
                    append(curServ[:3])
                    DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][key_of_process][-1].\
                    append(curServ[1] * 0.9 ** (curNumOfNodes-1)-(curNumOfNodes\
                    -1)-curServ[-1]/100)                 
                    cur_reliability = curServ[1]
    
            else:
                cur_reliability = LIST_OF_REQ[INDEX_OF_CUR_PROCESS][0]
                break
        DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][key_of_process].sort(key=lambda \
        x: x[-1],reverse=True)
        DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][key_of_process] = \
        DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][key_of_process][:KEEP]
    
    for k in NOTATION_OF_PROCESS[INDEX_OF_CUR_PROCESS].keys():
        NOTATION_OF_PROCESS[INDEX_OF_CUR_PROCESS][k] = 0
    for k in NOTATION_OF_PROCESS[INDEX_OF_CUR_PROCESS].keys():
        cur_r = 1
        cur_p = 0
        cur_q = -10000
        if(len(DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k])<KEEP):
            num = len(DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k])
        else:
            num = KEEP
        for (k2, v2) in NOTATION_OF_PROCESS[INDEX_OF_CUR_PROCESS].items():
            if k2 != k:
                cur_r *= DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k2][v2][1]
                cur_p += DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k2][v2][2]
        for i in range(0, num):
            if cur_q < cur_r*DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k][i][1]\
            -(cur_p  + DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k][i][2])/100:
                cur_q = cur_r*DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k][i][1]\
                -(cur_p  +  DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k][i][2])/100
                NOTATION_OF_PROCESS[INDEX_OF_CUR_PROCESS][k] = i
        RESULT[INDEX_OF_CUR_PROCESS][2] = cur_q
        RESULT[INDEX_OF_CUR_PROCESS][0] = cur_r * DICT_OF_PROCESS[\
        INDEX_OF_CUR_PROCESS][k][ NOTATION_OF_PROCESS[\
        INDEX_OF_CUR_PROCESS][k]][1]
        RESULT[INDEX_OF_CUR_PROCESS][1] = cur_p + DICT_OF_PROCESS[\
        INDEX_OF_CUR_PROCESS][k][NOTATION_OF_PROCESS[\
        INDEX_OF_CUR_PROCESS][k]][2]
END = time.clock()
INDEX_OF_CUR_PROCESS = 0
for process_line in PROCESS:
    for k in DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS].keys():
        process_line = process_line.replace(k, k + '-' + str(\
            DICT_OF_PROCESS[INDEX_OF_CUR_PROCESS][k][\
            NOTATION_OF_PROCESS[INDEX_OF_CUR_PROCESS][k]][0]))
    process_line = process_line.replace("\n", ', ') if  process_line[-1] \
          == '\n' else (process_line + ', ')
    process_line = process_line + " Reliability = " + str(RESULT[\
        INDEX_OF_CUR_PROCESS][0]) + ", Cost = " + str(RESULT[\
        INDEX_OF_CUR_PROCESS][1]\
        ) + ", Q = " + str(RESULT[INDEX_OF_CUR_PROCESS][2]) + "\n"
    print process_line
    INDEX_OF_CUR_PROCESS += 1
print "Start: " + str(START)
print "End: " + str(END)
print "End - Start: " + str(END-START)


