from beamprofiler import BeamProfiler, Gaussian2DProfile
import matplotlib.pyplot as plt
import numpy as np

beamProfiler = BeamProfiler()

beamProfiler.calibrate(6177.6, 4650.4)
beamProfiler.open("beam.bmp")
# plt.imshow(beamProfiler.image_as_array)

beamProfiler.smooth()
# plt.imshow(beamProfiler.image_as_array)
beamProfiler.scale(4) # reduces the scale of the image by 4 for easier calculations.
beamProfiler.normalize()

plt.imshow(beamProfiler.image_as_array)
plt.colorbar()
e, x, y, popt, pcov = beamProfiler.calculate_beam_parameters(first_guess=(1, 300, 125, 80, 50, 0, 0), convert_to_real_size=True)
print(f"The beam has an ellipticity of {e:.2f}, a width (1/e^2) of {x:.2e} um x {y:.2e}")
plt.figure()

profile = Gaussian2DProfile()

x = np.arange(0, beamProfiler.image_as_array.shape[1], 1) 
y = np.arange(0, beamProfiler.image_as_array.shape[0], 1)

x, y = np.meshgrid(x, y)

Z = profile.calculate((x, y), *popt)
plt.imshow(Z.reshape(beamProfiler.image_as_array.shape))
plt.colorbar()

plt.show()