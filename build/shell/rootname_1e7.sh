#!/bin/sh

#2020/06/16
./variable/time_fout.out
. variable/root_1e7.dat
../main $MAC $OFN $INF $RFN
. variable/time.dat
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} ${RFN}"
echo "Finish shell script!\n"
#root -l '../root_program/root_tree_divcanvas_histgram.cc("../shell/'$TIME'.root")'
#root -l '../root_program/root_tree_divcanvas_histgram.cc("../shell/'$RFN'.root")'
