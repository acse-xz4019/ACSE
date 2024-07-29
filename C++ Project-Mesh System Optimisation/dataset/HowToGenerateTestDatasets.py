import numpy as np
# create a 2d array generator, which will generate a 2d array of size n x 3
# float values in the range of lowrange to highrange

def generate_2d_array(n, lowrange, highrange):
    return np.random.uniform(lowrange, highrange, (int(n), 3))


# create a random ununiform 2d array generator, which will generate a 2d array of size n x 3
# float values in the range of lowrange to highrange
def generate_2d_array_ununiform(n, lowrange, highrange):
    return np.random.rand(n, 3) * (highrange - lowrange) + lowrange

# increase the number of sources and adjust the temperature to meet the new requirements
def increased_sparse_varied_temperature_field(x, y, z):
    scale_factor_to_100_adjusted = 72.579
    increased_sparse_varied_positions = [
        {"A": 3 * scale_factor_to_100_adjusted, "x0": 20, "y0": 20, "z0": 20, "sigma": 12},
        {"A": 2 * scale_factor_to_100_adjusted, "x0": 80, "y0": 80, "z0": 80, "sigma": 18},
        {"A": 1.5 * scale_factor_to_100_adjusted, "x0": 50, "y0": 50, "z0": 50, "sigma": 25},
        {"A": 2.5 * scale_factor_to_100_adjusted, "x0": 40, "y0": 40, "z0": 60, "sigma": 15},
        {"A": 2.2 * scale_factor_to_100_adjusted, "x0": 60, "y0": 20, "z0": 40, "sigma": 12},
        {"A": 1.8 * scale_factor_to_100_adjusted, "x0": 20, "y0": 60, "z0": 80, "sigma": 20},
        {"A": 1.6 * scale_factor_to_100_adjusted, "x0": 70, "y0": 50, "z0": 30, "sigma": 18},
        {"A": 1.4 * scale_factor_to_100_adjusted, "x0": 30, "y0": 70, "z0": 70, "sigma": 16}
    ]

    T = np.zeros(x.shape)
    for source in increased_sparse_varied_positions:
        T += source["A"] * np.exp(-((x-source["x0"])**2 + (y-source["y0"])**2 + (z-source["z0"])**2) / (2 * source["sigma"]**2))
    return T

# increase the number of sources and adjust the pressure to meet the requirements
def adjusted_complex_pressure_field(x, y, z, scale_factor):
    scale_factor = 382.615
    sources = [
        {"A": 2 * scale_factor, "x0": 30, "y0": 30, "z0": 50, "sigma": 20},
        {"A": 1.5 * scale_factor, "x0": 70, "y0": 70, "z0": 50, "sigma": 15},
        {"A": 1.2 * scale_factor, "x0": 50, "y0": 50, "z0": 50, "sigma": 25},
        {"A": 0.8 * scale_factor, "x0": 20, "y0": 80, "z0": 50, "sigma": 10},
        {"A": 2 * scale_factor, "x0": 80, "y0": 20, "z0": 50, "sigma": 20}
    ]

    P = np.zeros(x.shape)
    for source in sources:
        P += source["A"] * np.exp(-((x-source["x0"])**2 + (y-source["y0"])**2 + (z-source["z0"])**2) / (2 * source["sigma"]**2))
    return P

# source nodes
source = generate_2d_array(1e3, 0, 100)
# target nodes
target = generate_2d_array(1e3, 0, 100)
# source nodes sample from a temperature field
sourceTem = increased_sparse_varied_temperature_field(source[:, 0], source[:, 1], source[:, 2])
# target nodes sample from a temperature field
targetTem = increased_sparse_varied_temperature_field(target[:, 0], target[:, 1], target[:, 2])
# source nodes sample from a pressure field
sourcePre = adjusted_complex_pressure_field(source[:, 0], source[:, 1], source[:, 2], 382.615)
# target nodes sample from a pressure field
targetPre = adjusted_complex_pressure_field(target[:, 0], target[:, 1], target[:, 2], 382.615)

# write to csv
np.savetxt('source.csv', np.column_stack((source, sourceTem, sourcePre)), delimiter=',')
np.savetxt('groundtruth.csv', np.column_stack((target, targetTem, targetPre)), delimiter=',')
np.savetxt('target.csv', np.column_stack((target, np.zeros(target.shape[0]), np.zeros(target.shape[0]))), delimiter=',')