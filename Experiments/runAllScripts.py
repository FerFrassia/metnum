import generateExperiments
import config as c
import runExperiments
import generateGraphs

generateExperiments.generarTests(c.minNodes, c.maxNodes)
runExperiments.runTests()
generateGraphs.generateGraphs()
