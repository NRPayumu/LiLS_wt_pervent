#!/bin/sh

#2019/11/28
./variable/time_fout.out
. variable/exe_1e7.dat
../main $MAC $OFN $INF
. variable/time.dat
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
#root -l '../root_program/root_tree_divcanvas_histgram.cc("../shell/'$TIME'.root")'
cd ../
/usr/bin/make
cd shell
./variable/time_fout.out
. variable/exe_1e7.dat
../main $MAC $OFN $INF
. variable/time.dat
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
