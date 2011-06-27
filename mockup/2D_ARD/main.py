from pylab import *
from scipy.fftpack import *

def dct2d(input):
    return dct(dct(input), axis=0)
    
def idct2d(input):
    return idct(idct(input), axis=0)/(size(input)*4)

c = 340.0
dt = 0.0001
width = 100
height = 100
field = zeros((width, height))

M_prev = field.copy()
M_now = field.copy()
F = field.copy()

F[height/2][width/2] = 10.0
F_mode = dct2d(F)

omega = c*pi*(matrix(arange(0.0,width)**2)/width**2 + (matrix(arange(0.0,height)**2).transpose())/height**2)
M_next = 2*M_prev*cos(omega*dt) - M_now + 2*F_mode/omega**2*(1-cos(omega*dt))

P = idct2d(M_next)

imshow(P)
#contour(P)
show()
