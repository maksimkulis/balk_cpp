import matplotlib.pyplot as plt
import numpy as np


def show():
    with open("outputs/out1.txt", "r") as f1, \
            open("outputs/out2.txt", "r") as f2, \
            open("outputs/out3.txt", "r") as f3, \
            open("outputs/out4.txt", "r") as f4:
        fig, axe = plt.subplots(4, 1, sharex=True, figsize=(5, 5))

        y = []
        for num in f1:
            y.append(float(num))
        axe[0].plot(np.linspace(0, 1, len(y)), np.array(y))

        y = []
        for num in f2:
            y.append(float(num))
        axe[1].plot(np.linspace(0, 1, len(y)), np.array(y))

        y = []
        for num in f3:
            y.append(float(num))
        axe[2].plot(np.linspace(0, 1, len(y)), np.array(y))

        y = []
        for num in f4:
            y.append(float(num))
        axe[3].plot(np.linspace(0, 1, len(y)), np.array(y))
        plt.show()


if __name__ == "__main__":
    show()
