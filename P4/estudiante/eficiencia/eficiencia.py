import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from subprocess import call

# p = subprocess.run("/home/daniel/Proyectos/ED/P4/cmake-build-release/test_eficiencia",)

# subprocess.run('START "" "'  + '"', shell=True)

call(["/home/daniel/Proyectos/ED/P4/cmake-build-release/test_eficiencia", "-p", "data/diccionario.txt", "-p",
      "data/letras.txt", "-p", 'P', "-p", '0'])
# data/diccionario.txt data/letras.txt P 0
