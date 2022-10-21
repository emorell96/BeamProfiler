from ast import arg
from ctypes import Union
import imp
from PIL import Image
import numpy as np
from scipy import signal
from scipy.signal import convolve
from abc import abstractmethod, ABC, abstractproperty
from scipy.optimize import curve_fit

class Profile(ABC):
    @abstractmethod
    def calculate(self, X: np.array, *args, **kwargs):
        pass

class Gaussian2DProfile(Profile):
    def calculate(self, X: np.array, *args, **kwargs):
        def twoD_Gaussian(X, amplitude, xo, yo, sigma_x, sigma_y, theta, offset):
            x, y = X
            xo = float(xo)
            yo = float(yo)    
            a = (np.cos(theta)**2)/(2*sigma_x**2) + (np.sin(theta)**2)/(2*sigma_y**2)
            b = -(np.sin(2*theta))/(4*sigma_x**2) + (np.sin(2*theta))/(4*sigma_y**2)
            c = (np.sin(theta)**2)/(2*sigma_x**2) + (np.cos(theta)**2)/(2*sigma_y**2)
            g = offset + amplitude*np.exp( - (a*((x-xo)**2) + 2*b*(x-xo)*(y-yo) 
                                    + c*((y-yo)**2)))
            return g.ravel()
        return twoD_Gaussian(X, *args)


class BeamProfiler:
    def calibrate(self, sensor_size_x : float, sensor_size_y: float):
        self.x = sensor_size_x
        self.y = sensor_size_y

    def open(self, filepath : str, mode : str = "L" ) -> None:
        self.image = Image.open(filepath).convert(mode)
        self.image_as_array = np.array(self.image)
    def smooth(self, kernel_size : int = 150, sigma : int = 70) -> None:
        """
        Smooths the image array by convoluting the data with a gaussian filter.
        Works only if the image is a single 'color' (grayscale.)
        It will rewrite the original array.
        """
        kernel = np.outer(signal.windows.gaussian(kernel_size, sigma),
            signal.windows.gaussian(kernel_size, sigma))
        self.image_as_array = convolve(self.image_as_array, kernel)
    def normalize(self) -> None:
        """
        Normalizes the image array by dividing the image array by the maximum value in it.
        """
        self.image_as_array = self.image_as_array/np.max(self.image_as_array)
    def scale(self, scale : float, **kwargs):
        """
        Rescales the image array by resizing the image with PIL and then ovewritting the image array.
        It loads the image from the image_as_array to keep any changes already done to the array.
        """
        im = Image.fromarray(self.image_as_array)
        # calculates the new x/y size of the image in pixels. It assumes the image is grayscale.
        x1, y1 = self.image_as_array.shape[1]//scale, self.image_as_array.shape[0]//scale
        im = im.resize((x1, y1), **kwargs)
        self.image_as_array = np.array(im)
    def fit(self, profile : Profile, first_guess : tuple = None) -> tuple:
        x = np.arange(0, self.image_as_array.shape[1], 1) 
        y = np.arange(0, self.image_as_array.shape[0], 1)

        x, y = np.meshgrid(x, y)

        return curve_fit(profile.calculate, (x, y), self.image_as_array.ravel(), p0=first_guess)
    def calculate_beam_parameters(self, first_guess : tuple = None, convert_to_real_size: bool = False):
        """
        Calculates the beam parameters: ellipticity and width at 1/e^2 (2 sigma)
        Returns the ellipticity, sigma_x, sigma_y, popt, and the pcov from the fit.
        """
        profile = Gaussian2DProfile()
        popt, pcov = self.fit(profile, first_guess= first_guess)

        sigma_x = popt[3]
        sigma_y = popt[4]

        e = min(sigma_x, sigma_y)/max(sigma_x, sigma_y)

        if(convert_to_real_size):
            diagonal_in_pixels = np.sqrt(self.image_as_array.shape[0]**2 + self.image_as_array.shape[1]**2)
            diagonal_in_real = np.sqrt(self.x**2 + self.y**2)
            scale = diagonal_in_real/diagonal_in_pixels
            return (e, 2*sigma_x*scale, 2*sigma_y*scale, popt, pcov)

        return (e, 2*sigma_x, 2*sigma_y, popt, pcov)




    
    




        


