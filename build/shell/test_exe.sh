#!/bin/sh

. variable/test_exe.dat
../main $MAC $OFN $INF
echo "\n\n"
echo "../main ${MAC} ${OFN} ${INF} "
echo "Finish shell script!\n"
