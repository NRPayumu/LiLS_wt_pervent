#!/bin/sh

. variable/exe_1e6.dat
time ../main $MAC $OFN $INF
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
