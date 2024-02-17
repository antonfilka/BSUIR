import numpy as np
import cmath
import matplotlib.pyplot as plt


# Define the signal function
def signal(x):
    return np.cos(x) + np.sin(x)


# Define the DFT algorithm
def DFT(x):
    N = len(x)
    X = np.zeros(N, dtype=complex)
    for k in range(N):
        for n in range(N):
            X[k] += x[n] * cmath.exp(-2j * cmath.pi * k * n / N)
    return X


# Define the FFT algorithm
def FFT(x):
    N = len(x)
    if N == 1:
        return x
    else:
        X_even = FFT(x[::2])
        X_odd = FFT(x[1::2])
        factor = np.exp(-2j * np.pi * np.arange(N) / N)
        return np.concatenate([X_even + factor[:N // 2] * X_odd,
                               X_even + factor[N // 2:] * X_odd])


# Define the IDFT algorithm
def IDFT(X):
    N = len(X)
    x = np.zeros(N, dtype=complex)
    for n in range(N):
        for k in range(N):
            x[n] += X[k] * cmath.exp(2j * cmath.pi * k * n / N)
    return x


# Define the IFFT algorithm
def IFFT(X):
    N = len(X)
    if N == 1:
        return X
    else:
        X_even = IFFT(X[::2])
        X_odd = IFFT(X[1::2])
        factor = np.exp(2j * np.pi * np.arange(N) / N)
        return np.concatenate([X_even + factor[:N // 2] * X_odd,
                               X_even + factor[N // 2:] * X_odd]) / N


# Define the signal properties
N = 8
x = np.linspace(0, 2 * np.pi, N, endpoint=False)
y = signal(x)

# Compute the DFT and FFT of the signal
dft_y = DFT(y)
fft_y = FFT(y)

# Compute the magnitude and phase spectra of the signal
mag_dft_y = np.abs(dft_y)
phase_dft_y = np.angle(dft_y)
mag_fft_y = np.abs(fft_y)
phase_fft_y = np.angle(fft_y)
idft_y = IDFT(dft_y)
ifft_y = IFFT(fft_y)

# Plot the signal and spectra
fig, ax = plt.subplots(nrows=2, ncols=4, figsize=(12, 6))
plt.style.use('ggplot')

n = np.arange(N)
T = x[1] - x[0]
fs = 1 / T

ax[1, 0].plot(n, y, '--')
ax[1, 0].set_title('Sampled signal')
ax[1, 0].grid()
ax[0, 0].plot(x, y)
ax[0, 0].set_title('Source function: sin(x) + cos(x)')
ax[0, 0].grid()
ax[1, 2].plot(mag_dft_y, '--*', )
ax[1, 2].set_title('DFT Magnitude')
ax[1, 2].grid()
ax[0, 2].plot(mag_fft_y, '-g*')
ax[0, 2].set_title('FFT Magnitude')
ax[0, 2].grid()
ax[1, 1].plot(phase_dft_y, '--*')
ax[1, 1].set_title('DFT Phase')
ax[1, 1].grid()
ax[0, 1].plot(phase_fft_y, '-g*')
ax[0, 1].set_title('FFT Phase')
ax[0, 1].grid()
ax[1, 3].plot(idft_y, '--*')
ax[1, 3].set_title('Inverse DTF')
ax[1, 3].grid()
ax[0, 3].plot(ifft_y, '-g*')
ax[0, 3].set_title('Inverse FFT')
ax[0, 3].grid()

plt.tight_layout()
plt.show()


# Compare the computational complexity of DFT and FFT
def num_ops_dft(N):
    return N ** 2


def num_ops_fft(N):
    if N == 1:
        return 0
    else:
        return 2 * num_ops_fft(N // 2) + N


print('Computational complexity of DFT:', num_ops_dft(N))
print('Computational complexity of FFT:', num_ops_fft(N))

# Print the number of operations using FFT
iterations_fft_ = num_ops_fft(N)
sum_count_fft = iterations_fft_
mul_count_fft = iterations_fft_ / 2
print("Number of operations using FFT")
print("Sum: %d, mul: %d" % (sum_count_fft, mul_count_fft))

iterations_dft_ = num_ops_dft(N)
sum_count_dft = iterations_dft_
mul_count_dft = iterations_dft_
print("Number of operations using DFT")
print("Sum: %d, mul: %d" % (sum_count_dft, mul_count_dft))
