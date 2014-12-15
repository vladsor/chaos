#!/bin/bash

nm -f posix storm | cut -d ' ' -f 1,3 | sort -u --key=2,2 > storm.sym
