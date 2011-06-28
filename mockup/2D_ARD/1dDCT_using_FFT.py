from pylab import *
from scipy.fftpack import *

hat = 0.5 + 0.5*cos(arange(-pi,pi,2*pi/100))
wav = 0.5 + 0.5*sin(arange(-pi,pi,2*pi/100))

def reflect(target):
    return concatenate((target, target[::-1]))

def interleave_zero(target):
    out = target.copy()
    out = out.repeat(2)
    for i in arange(0, size(out), 2):
        out[i] = 0

    return out

def prepare(target):
    return interleave_zero(reflect(target))

def mydct(target):
    return real(fft(prepare(target)))[0:size(target)]

