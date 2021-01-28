#!/bin/sh

. variable/exe_1e4.dat
time ../main $MAC $OFN $INF
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
