import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

data = np.genfromtxt("results.csv", delimiter=",", skip_header=1)

analog_values = data[:, 0]
db_values = data[:, 1]

func_shape = lambda t,a,b: a+b*np.log(t)
fitted_params = curve_fit(func_shape, analog_values, db_values)
a, b = fitted_params[0]
print(f"a={a}\nb={b}")

approx_range = np.arange(1, 4096, 1)
db_approx = func_shape(approx_range, a, b)

fig, ax = plt.subplots()
ax.plot(analog_values, db_values, marker="o", label="Actual dB")
ax.plot(approx_range, db_approx, label="Approximation", linestyle="--")
ax.set_xlabel("Analog Values / X-Axis")
ax.set_ylabel("dB Values")
ax.set_title(f"Analog vs. dB Approximation \nForm a+b*np.log(t) a={np.round(a, 3)} b={np.round(b, 3)}")
ax.legend()
ax.grid(True)
fig.savefig("CalibrationPlot.png")
print("Plot saved successfully!")
input()