import matplotlib.pyplot as plt
import numpy as np

# change font size
plt.rcParams.update({'font.size': 16})

# create a figure and and the Axes object
fig, ax = plt.subplots()

# x-axis labels and positions.
x_labels = (
    'MapReduced\nSVM',
    'Deep\nLearning\nLocal\nProcessing',
    'Deep\nLearning\nCloud\nVirtualization',
    'Deep\nLearning\nCloud\nDecision\nMechanism'
)
x_pos = np.arange(len(x_labels)) # returns positions: [0, 1, 2, 3].

# set tick locations and labels of the x-axis.
ax.set_xticks(x_pos)
ax.set_xticklabels(x_labels)

# y-axis positions and label for y-axis.
y_pos = ( 163.5, 26.96, 14.64, 8.9 ) # height of each bar.
ax.set_ylabel('Time (sec)')

# style the grid with horizontal lines
ax.grid(axis='y', linewidth=0.1, linestyle='-')
ax.set_axisbelow(True)
ax.set_frame_on(False)
ax.set_xlabel('EHSH Methodologies')

# make a bar plot.
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.bar.html
bars = ax.bar(x_pos, y_pos, width=0.3, align='center', color='#2179dd')

# set a label over each bar
for idx, rect in enumerate(bars.patches):
    x_value = rect.get_x() + rect.get_width() / 2
    y_value = rect.get_height()
    label = str(y_pos[idx])
    ax.annotate(label, (x_value, y_value), xytext=(0, 10), textcoords="offset points", ha='center')

# margin to each limit of the axes.
ax.margins(0.1, 0, tight=False)
ax.tick_params(right=False, top=False, left=False, bottom=False)

# adjust automatically subplot params to fits in to the figure area.
fig.tight_layout() 

# display all open figures.
# plt.show()

# save the figure as pdf vector image.
plt.savefig('figura_matplotlib.pdf')
