from setuptools import setup, Extension

setup(

    ext_modules=[Extension('approximate_point_using_newton_polynomial',
                           ['NewtonInterpolationPolynomial.cpp'],),],
)

