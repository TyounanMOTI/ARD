#!/Library/Frameworks/Python.framework/Versions/2.7/bin/python

from pylab import *

data = []
for line in open(sys.argv[1], "r"):
  data.append(float(line));

plot(data)
show()
