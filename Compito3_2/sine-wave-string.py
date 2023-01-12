#! /usr/local/bin/python3.9

import matplotlib as mpl
import matplotlib.pyplot as plt
import os
import sys

import numpy as np
from tqdm import tqdm

plt.style.use('dark_background')


def main(driving_force: bool = True):

    STRING_LENGHT = 0.5
    WAVE_AMPLITUDE = 0.5
    N_POINTS = 101
    SIMULATION_ITERATION = 10_000
    TIME_INTERVAL_MINIMUM = 1e-1
    PLOT_EVERY = 10
    WAVENUMBER = 4

    x = np.linspace(0.0, STRING_LENGHT, N_POINTS)
    dx = x[1]-x[0]

    speed = np.linspace(1.0, 0.1, N_POINTS)**2 * 1e-2
    # speed = 1e-2
    proper_speed = dx/TIME_INTERVAL_MINIMUM

    if isinstance(speed, float):
        if speed > proper_speed:
            raise RuntimeError(
                '%.3f > %.3f: stability condition not satisfied!' % (speed, proper_speed))

    U_n0 = np.zeros(N_POINTS)
    U_n1 = np.zeros(N_POINTS)
    U_n2 = np.zeros(N_POINTS)

    if driving_force:
        def U0(t): return WAVE_AMPLITUDE * np.sin(WAVENUMBER / (2 * np.pi) * t)
        U_n0[0] = U0(0)
    else:
        U_n0 = WAVE_AMPLITUDE * np.sin(x * WAVENUMBER * np.pi / STRING_LENGHT)


    U_n1[1:N_POINTS-1] = (  U_n0[1:N_POINTS-1]+ speed[1:N_POINTS-1]**2 / (proper_speed**2) * (U_n0[2:N_POINTS]+U_n0[0:N_POINTS-2]-2 * U_n0[1:N_POINTS-1]))

    plt.figure()
    plt.ylim(-2*WAVE_AMPLITUDE,2*WAVE_AMPLITUDE)

    for i in tqdm(range(1, SIMULATION_ITERATION)):

        if i % PLOT_EVERY == 0:
            plt.clf()
            plt.plot(x,U_n1,color='r')

            plt.ylim(-2*WAVE_AMPLITUDE,2*WAVE_AMPLITUDE)
            plt.text(0.05,0.05,'iteration %6d (time %4.1f)' % (i, i * TIME_INTERVAL_MINIMUM),color='w', transform=plt.gca().transAxes)
            

        if driving_force:
            U_n1[0] = U0(i * TIME_INTERVAL_MINIMUM)

        U_n2[1:N_POINTS-1] = (2 * U_n1[1:N_POINTS-1]-U_n0[1:N_POINTS-1]+(speed[1:N_POINTS-1] / proper_speed)**2 * (U_n1[2:N_POINTS]+U_n1[0:N_POINTS-2]-2 * U_n1[1:N_POINTS-1] ))

        U_n0 = np.copy(U_n1)
        U_n1 = np.copy(U_n2)

        plt.draw()
        plt.pause(1e-10)


if __name__ == "__main__":
    os.system('python3 -m pip install tqdm matplotlib numpy')
    main(True)
