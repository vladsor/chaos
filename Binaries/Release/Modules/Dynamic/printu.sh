#!/bin/sh

nm -A --defined-only $1 | cut -d ' ' -f 3 | sort -u >.defined

nm -u -A $1 | cut -d ' ' -f 11 | sort -u >.undefined
comm -1 -3 .defined .undefined
#comm -1 -3 .defined .undefined
