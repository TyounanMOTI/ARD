from pylab import *
from scipy.fftpack import *
import scipy.io.wavfile as wavfile

c = 340.0
dt = 0.001
width = 100
field = zeros(width)

M_prev = field.copy()
M_now = field.copy()
F = field.copy()

wideness = 10

line, = plot(F)
ylim([-10000, 10000])

omega = c*pi*(arange(1.0,width+1)/width)
mic = zeros(1000)
for i in arange(0, 1000):
    F[width/2-wideness/2:width/2+wideness/2] = (0.5+0.5*cos(arange(-pi, pi, 2*pi/wideness)))*c**2 * sin(2*pi*10/1000*i)
    F_mode = dct(F)
    M_next = 2*M_now*cos(omega*dt) - M_prev + 2*F_mode/omega**2*(1-cos(omega*dt))
    P = idct(M_next)
    M_prev = M_now.copy()
    M_now = M_next.copy()
    mic[i] = P[20]
#    line.set_ydata(P)
#    draw()

figure()
plot(mic/max(mic))
wavfile.write('out.wav', 1000, mic/max(mic))