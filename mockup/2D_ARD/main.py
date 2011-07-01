from pylab import *
from scipy.fftpack import *
import time

def dct2d(input):
    return dct(dct(input), axis=0)

def idct2d(input):
    return idct(idct(input, axis=0))/(4*size(input))

ion()

c = 340.0
fs = 2000.0
dt = 1.0/fs
Lx = 10.0
Ly = 10.0
dx = dy = c/(fs/2)/4
width = floor(Lx/dx)
height = floor(Ly/dy)
print width, height, dx
width= height = 300

field = zeros((width, height))
M_prev = field.copy()
M_now = field.copy()
M_next = field.copy()
F = field.copy()

F[40][30] = 100000.0
F_mode = dct2d(F)

omega = array(c*pi*sqrt(matrix(arange(0.0,width)**2).transpose()/(width-1)**2 + (matrix(arange(0.0,height)**2))/(height-1)**2))
omega[0][0] = 1.0

image = imshow(field, vmin=0.0001, vmax=0.005)

mic = zeros(4000)
for i in arange(0, 2000):
    M_next = 2*M_now*cos(omega*dt) - M_prev + 2*F_mode/omega**2*(1-cos(omega*dt))
    M_next[0,0] = 2*M_now[0,0] - M_prev[0,0]
    P = idct2d(M_next)
    mic[i] = P[10,10]
    M_prev = M_now.copy()
    M_now = M_next.copy()
    F_mode = field
    print i
    image.set_array(P)
    draw()
#    time.sleep(0.05)

#contour(P)
figure()
plot(mic)
show()
