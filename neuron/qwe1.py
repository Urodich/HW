from math import floor
import numpy as np


def calc_out_shape(input_matrix_shape, out_channels, kernel_size, stride, padding):
    out_shape = [input_matrix_shape[0], out_channels, floor((input_matrix_shape[2]-kernel_size+2*padding)/stride+1), floor((input_matrix_shape[2]-kernel_size+2*padding)/stride+1)]
    return out_shape

print(np.array_equal(
    calc_out_shape(input_matrix_shape=[2, 3, 10, 10],
                   out_channels=10,
                   kernel_size=3,
                   stride=1,
                   padding=0),
    [2, 10, 8, 8]))
