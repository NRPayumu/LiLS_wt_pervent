#!/bin/sh

#2020/06/16

cd input_file/NeutrinoGenerator
root -l -q Gene_hist.cc'("test",10000000)' 2>E_nu.dat
mv test_all_10000000.dat ../
cd ../../
cmake ../
make
