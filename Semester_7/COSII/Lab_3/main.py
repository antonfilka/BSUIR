import cv2 as cv
import numpy as np

import os
import sys

TAU = 1.0 #Specifies the offset of the wavelet transform.


HEIGHT = 700 #Specifies the height of the image to show.


def wavelet(x): #Represents the mother wavelet with `x` parameter.
    return -x * np.exp(-x*x / 2)

def low_pass_kernel(n): #Returns the low pass filter kernel with even `n` parameter.

    result = np.zeros((n // 2, n))

    for i in np.arange(n // 2):
        result[i, 2*i] = wavelet(-TAU / 2.0)
        result[i, 2*i + 1] = wavelet(TAU / 2.0)

    return 1/np.sqrt(2) * result

def high_pass_kernel(n): #Returns the high pass filter kernel with even `n` parameter.
    result = np.zeros((n // 2, n))

    for i in np.arange(n // 2):
        result[i, 2*i] = wavelet(-TAU / 2.0)
        result[i, 2*i + 1] = -wavelet(TAU / 2.0)

    return 1/np.sqrt(2) * result

def wavelet_transform(image): #Performs the wavelet transform of the `image`.
    if image.shape[0] % 2:
        comps = []

        for k in np.arange(image.shape[2]):
            comp = image[:, :, k]

            # Add extra row.
            comp = np.concatenate((
                comp,
                np.array([comp[-1, :]])
            ), axis=0)

            comps.append(comp.reshape((comp.shape[0], comp.shape[1], 1)))

        # Combine components.
        image = np.concatenate(comps, axis=2)

    if image.shape[1] % 2:
        comps = []

        for k in np.arange(image.shape[2]):
            comp = image[:, :, k]

            # Add extra column.
            comp = np.concatenate((
                comp,
                np.array([comp[:, -1]]).T
            ), axis=1)

            comps.append(comp.reshape((comp.shape[0], comp.shape[1], 1)))

        # Combine components.
        image = np.concatenate(comps, axis=2)

    # Result coefficients.
    coeff_a = []
    coeff_h = []
    coeff_v = []
    coeff_d = []

    for k in np.arange(image.shape[2]):
        approx = np.dot(image[:, :, k], low_pass_kernel(image.shape[1]).T)
        detail = np.dot(image[:, :, k], high_pass_kernel(image.shape[1]).T)

        a = np.dot(low_pass_kernel(approx.shape[0]), approx)
        h = np.dot(high_pass_kernel(approx.shape[0]), approx)
        v = np.dot(low_pass_kernel(detail.shape[0]), detail)
        d = np.dot(high_pass_kernel(detail.shape[0]), detail)

        # Get rid of negative values.
        h = np.abs(h)
        v = np.abs(v)
        d = np.abs(d)

        # Normalize coefficients.
        a = np.uint8(a / np.max(a) * 255.0)
        h = np.uint8(h / np.max(h) * 255.0)
        v = np.uint8(v / np.max(v) * 255.0)
        d = np.uint8(d / np.max(d) * 255.0)

        coeff_a.append(a.reshape((a.shape[0], a.shape[1], 1)))
        coeff_h.append(h.reshape((h.shape[0], h.shape[1], 1)))
        coeff_v.append(v.reshape((v.shape[0], v.shape[1], 1)))
        coeff_d.append(d.reshape((d.shape[0], d.shape[1], 1)))

    # Combine components.
    a = np.concatenate(coeff_a, axis=2)
    h = np.concatenate(coeff_h, axis=2)
    v = np.concatenate(coeff_v, axis=2)
    d = np.concatenate(coeff_d, axis=2)

    return a, h, v, d

def main(): #The main function of the program.
    path = input('path: ')

    if not os.path.exists(path):
        print(f'error: \'{path}\' does not exists', file=sys.stderr)
        sys.exit(1)

    image = cv.imread(path, cv.IMREAD_COLOR)

    # The size of the image to show.
    size = (int(HEIGHT * image.shape[1]/image.shape[0]), HEIGHT)

    # The size of the coefficients to show.
    coeff_size = (size[0] // 2, size[1] // 2)

    level = int(input('level: '))

    for l in np.arange(level):
        cv.imshow(f'Initial {l+1}', cv.resize(
            image, size,
            interpolation=cv.INTER_NEAREST
        ))

        # Transform the image.
        a, h, v, d = wavelet_transform(image)

        cv.imshow(f'Approximation {l+1}', cv.resize(
            a, coeff_size,
            interpolation=cv.INTER_NEAREST
        ))

        cv.imshow(f'Horizontal {l+1}', cv.resize(
            h, coeff_size,
            interpolation=cv.INTER_NEAREST
        ))

        cv.imshow(f'Vertical {l+1}', cv.resize(
            v, coeff_size,
            interpolation=cv.INTER_NEAREST
        ))

        cv.imshow(f'Diagonal {l+1}', cv.resize(
            d, coeff_size,
            interpolation=cv.INTER_NEAREST
        ))

        print(f'scale = {4 ** (l+1)}')

        # Wait for user.
        cv.waitKey(0)
        cv.destroyAllWindows()

        # Update the image for the next iteration.
        image = a

    sys.exit(0)

if __name__ == '__main__':
    main()