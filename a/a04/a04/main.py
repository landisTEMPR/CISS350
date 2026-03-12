C = 0.0001                  # Modify this
N = 15000                   # Modify this
d = 1.2                     # Modify this

# Array sizes and runtimes -- Modify this, replacing with your timing data
data = ((10000, 8.5),    # <-- This means for array size 10000, time is 8.5 sec
        (20000, 9.7),
        (30000, 14.1),
        (40000, 18.8),
        (50000, 25.1))

# Max n
max_n = max([n for (n,_) in data])

# Curve fitting data
curve = tuple((n, C * n**d) for n in [n for (n,_) in data])

# Max y of both runtimes and curve
max_y = max(max(y for (_,y) in data), max(y for (_,y) in curve))

from latextool_basic import *
plot = FunctionPlot(width="6in", height="7in")

# Times for bubblesort
# Modify it carefully with a list of size of array and runtimes.
plot.add(data, line_width='2', color='red', legend='Bubblesort runtime')

# Graph for y = C * n^d for different values of n
# Modify it carefully with a list of n and C*n^d values.
plot.add(curve,
         line_width='2', color='green', legend='$Cn^{d}$')

# Graph for n = N
plot.add(((N, 0),
          (N, max_y)),
          line_width='2', color='blue', legend='$n = N$')

print(plot)

print(r"""
\[
N = %s, \hspace{0.5cm} C = %s, \hspace{0.5cm} d = %s
\]
""" % (N, C, d))

