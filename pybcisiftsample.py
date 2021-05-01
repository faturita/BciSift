import pybcisift
import numpy as np
el = np.zeros((1,256))
el = np.random.rand(1,256) * 100
descr = pybcisift.extract_full(1,(200, 256),(4,1),True,5,el.tolist()[0])
print(descr)
print(len(descr))



