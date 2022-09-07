import subprocess as sub

test = "test_15_segundos"

def main(filename, p):
	sub.run("./tp1 ./enunciado/tests/" + filename + ".txt " + str(p), shell=True)

main(test, 0.8)