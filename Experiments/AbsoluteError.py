import subprocess as sub

def calculateAbsoluteError(filename):
	y = []
	catedra = open("./enunciado/test/" + filename + ".txt.out", "r")
	propio = open("./enunciado/test/" + filename + "_propio.txt.out", "r")
	err = 0
	for l1, l2 in zip(catedra, propio):
		err += abs(float(l1) - float(l2))

def main(filename, p):
	sub.run("../tp1 ./enunciado/test/" + filename + ".txt " + str(p), shell=True)
	calculateAbsoluteError(filename)

main("test_15_segundos", 0.8)