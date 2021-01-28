import sys

def split_file(FN,Num):
	IFN = args[1] + ".dat"
	OFN = args[1] + "_sp1.dat"
	ip=open(IFN,"r")
	op=open(OFN,"w")
	i = 0
	j = 1
	for li in ip:
		if i % int(Num) == 0 and i != 0:
			op.close()
			#del op
			j += 1
			OFN = args[1] + "_sp" + str(j) +".dat"
			op=open(OFN,"w")
		op.write(li)
		i+=1
	op.close()

args=sys.argv
FN = args[1]
Num= args[2]
split_file(FN,Num)
