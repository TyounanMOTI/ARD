from pylab import *
from scipy.fftpack import *
import scipy.io.wavfile as wavfile

def on_key(event):
    if event.key == 'q':
        quit()

c = 340.0
fs = 1000.0
dt = 1.0/fs
dx = c/(fs/2.0)/4.0
L = 10.0
width = ceil(L/dx)
#width = 100
print width
field = zeros(width)

M_prev = field.copy()
M_now = field.copy()
M_next = field.copy()
F = field.copy()

fig = figure()
ax = fig.add_subplot(111)
ax.set_animated(True)
line, = ax.plot(field)
ylim([-150, 150])
fig.canvas.mpl_connect('key_press_event', on_key)

wideness = 10
emit_position = 15
omega = c*pi*(arange(0.0,width)/(width-1))
simulation_length = 500
mic = zeros(simulation_length)

for i in arange(0, simulation_length):
    F[emit_position-wideness/2:emit_position+wideness/2] = (0.5+0.5*cos(arange(-pi, pi, 2*pi/wideness)))*c**2 * sin(2*pi*10/fs*i) * 10
    F_mode = dct(F)

    M_next[0] = 2*M_now[0] - M_prev[0]
    M_next[1:width] = 2*M_now[1:width]*cos(omega[1:width]*dt) - M_prev[1:width] + 2*F_mode[1:width]/omega[1:width]**2*(1-cos(omega[1:width]*dt))
    P = idct(M_next)/(2*width)
    M_prev = M_now.copy()
    M_now = M_next.copy()
    mic[i] = P[2]
    line.set_ydata(P)
    draw()

figure()
plot(mic)
figure()
plot(abs(fft(mic)))
show()
#wavfile.write('out.wav', 1000, mic/max(mic))
