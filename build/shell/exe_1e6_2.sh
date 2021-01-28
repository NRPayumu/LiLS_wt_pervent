#!/bin/sh

#2019/11/27
./variable/time_fout.out
. variable/exe_1e6.dat
time ../main $MAC $OFN $INF
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
cd ../
/usr/bin/make
cd shell
./variable/time_fout.out
. variable/exe_1e6.dat
time ../main $MAC $OFN $INF
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
