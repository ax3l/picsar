from setuptools import setup, find_packages

setup(
    name='picsar_python',
    version='0.0.1',
    description='Python wrapper for high-performance PIC library',
    maintainer='Henri Vincenti',
    maintainer_email='henri.vincenti@cea.fr',
    license='BSD-3-Clause-LBNL',
    packages=find_packages('./'),
    package_data={'': ['picsar_python/picsarpy.so']},
    include_package_data=True,
    platforms='any'
    )
