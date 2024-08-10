from setuptools import find_packages
from setuptools import setup

setup(
    name='voyager_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('voyager_msgs', 'voyager_msgs.*')),
)
