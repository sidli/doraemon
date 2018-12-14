#!/usr/bin/python

import os

workloads = ["workloads/tsworkloada",
"workloads/workloada",
"workloads/workloadc",
"workloads/workloade",
"workloads/workload_template",
"workloads/tsworkload_template",
"workloads/workloadb",
"workloads/workloadd",
"workloads/workloadf"]

cmd = "bin/ycsb.sh run basic -P "

def main():
    for wl in workloads:
        os.system(cmd + wl)

main()

