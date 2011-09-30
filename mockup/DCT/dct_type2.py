from pylab import *
from numpy.fft import *

def sin_1wave(length):
    return sin(2*pi/length*arange(length))

def cos_1wave(length):
    return cos(2*pi/length*arange(length))

def head1(length):
    x = zeros(10)
    x[0] = 1
    return x

def complex_to_ce(x):
    return hstack((x, x[1:len(x)-1][::-1].conj()))

def rotator(length):
    return cos(-2*pi/(4*length)*arange(length))

def prepare_tilde(x):
    return hstack((x[0::2], x[1::2][::-1]))

def phase_shift(x):
    return x.real*cos(-2*pi*arange(len(x))/(4*len(x))) - x.imag*sin(-2*pi*arange(len(x))/(4*len(x)))

x = sin_1wave(8) # input

# prepare tilde x
tilde_x = prepare_tilde(x)

# fft
f = rfft(tilde_x)

# complex to conjugate-even
f_ce = complex_to_ce(f)

# post process
y = phase_shift(f_ce) * 2
