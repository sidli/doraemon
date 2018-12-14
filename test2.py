#!/usr/bin/python

import os

workloads = [
" -P workloads/workloada",
" -P workloads/workloadc",
" -P workloads/workloade",
" -P workloads/workloadb",
" -P workloads/workloadd",
" -P workloads/workloadf"]

threads = [1,5,10,20,50,100,150,200]

workloads2 = " -P workloads/tsworkloada"

cmd = "bin/ycsb.sh run basic -p operationcount=100000 -threads "

def main():
    for wl in workloads:
        for thread in threads:
       	    os.system(cmd + str(thread) + wl + " 2>&1 > log_tmp")
       	    os.system("tail -n 35 log_tmp >> logs")
    os.system(cmd + workloads2 + " 2>&1 > log_tmp")
    os.system("tail -n 35 log_tmp >> logs")

main()

