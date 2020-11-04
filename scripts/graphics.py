import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import numpy as np
import sys
import os


def make_markers(axe, terms, y, balk_size):
    for term in terms:
        if term[0] == "R":
            axe.plot(term[1], 0, marker=6, color='red')
        elif term[0] == "Z":
            axe.plot(term[1], 0, marker="x", color='red')
        elif term[0] == "P":
            sign = 1 if term[2] > 0 else -1
            length = (np.max(y) - np.min(y)) / 2
            axe.arrow(term[1], length * (-sign), 0, length * sign, width=balk_size / 200,
                      head_width=balk_size / 100, head_length=length/5, length_includes_head=True, color='green')
        elif term[0] == "M":
            axe.plot(term[1], 0, marker="o", color='green')
        elif term[0] == "K":
            axe.plot(term[1], 0, marker="d", color='green')
        elif term[0] == "Q":
            sign = 1 if term[3] > 0 else -1
            axe.fill_between(np.array([term[1], term[2]]), - np.ones(
                shape=2) * (np.max(y) - np.min(y)) * sign / 5, 0, facecolor="orange", color='orange', alpha=0.2)


def make_vertical_lines(axes, terms, balk_size):
    for term in terms:
        for axe in axes:
            axe.axvline(term[1], c='k', alpha=0.1)
            if term[0] == "Q":
                axe.axvline(term[2], c='k', alpha=0.1)


def show(balk_size, segment_length, E, J, terms, output_dir):
    with open(os.path.join(output_dir, "out1.txt"), "r") as f1, \
            open(os.path.join(output_dir, "out2.txt"), "r") as f2, \
            open(os.path.join(output_dir, "out3.txt"), "r") as f3, \
            open(os.path.join(output_dir, "out4.txt"), "r") as f4:
        fig, axe = plt.subplots(4, 1, sharex=True, figsize=(5, 5))
        y = []
        for num in f1:
            y.append(float(num))
        axe[0].margins(y=1)
        axe[0].plot(np.linspace(0, balk_size, len(y)),
                    np.array(y), linestyle="--")
        axe[0].plot(np.linspace(0, balk_size, len(y)),
                    np.zeros(shape=len(y)), color='C0')
        make_markers(axe[0], terms, y, balk_size)
        axe[0].set_title(r"$w(x)$", size=6, loc="left", pad=2)

        y = []
        for num in f2:
            y.append(float(num))
        axe[1].plot(np.linspace(0, balk_size, len(y)), np.array(y))
        axe[1].set_title(r"$\theta(x)$", size=6, loc="left", pad=2)

        y = []
        for num in f3:
            y.append(float(num))
        axe[2].plot(np.linspace(0, balk_size, len(y)), np.array(y))
        axe[2].set_title(r"$M(x)$", size=6, loc="left", pad=2)

        y = []
        for num in f4:
            y.append(float(num))
        axe[3].plot(np.linspace(0, balk_size, len(y)), np.array(y))
        axe[3].set_title(r"$Q(x)$", size=6, loc="left", pad=2)

        make_vertical_lines(axe, terms, balk_size)
        hinge_support = mlines.Line2D([], [], color='red', marker=6, linestyle='None',
                                      markersize=5, label='Hinge support')
        rigid_fixing = mlines.Line2D([], [], color='red', marker='x', linestyle='None',
                                     markersize=5, label='Rigid fixing')
        concetrated_force = mlines.Line2D([], [], color='green', marker='|', linestyle='None',
                                          markersize=5, label='Concetrated force')
        elastic_support = mlines.Line2D([], [], color='green', marker='d', linestyle='None',
                                        markersize=5, label='Elastic support')
        moment = mlines.Line2D([], [], color='green', marker='o', linestyle='None',
                               markersize=5, label='Moment')
        uniform_load = mlines.Line2D([], [], color='orange', alpha=0.2, marker='s', linestyle='None',
                                     markersize=5, label='Uniform load')
        fig.legend(handles=[hinge_support, rigid_fixing, concetrated_force,
                            elastic_support, moment, uniform_load], prop={'size': 5}, framealpha=0.5)

        plt.savefig(os.path.join(output_dir, "image.png"))
        plt.show()


def parse_file(file):
    args = file.readline().split()

    balk_size = int(args[0])
    segment_length = float(args[1])
    E = float(args[2])
    J = float(args[3])

    terms = []
    for line in file:
        term = line.split()
        term[1] = int(term[1])
        if term[0] in {"K", "P", "M"}:
            term[2] = float(term[2])
        elif term[0] in {"Q"}:
            term[2] = int(term[2])
            term[3] = float(term[3])
        terms.append(term)

    return balk_size, segment_length, E, J, terms


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise RuntimeError("write the input file")

    input_file_name = sys.argv[1]
    with open(input_file_name, "r") as file:
        show(*parse_file(file), sys.argv[2])
