from setuptools import setup, Extension

module = Extension('sheller', sources=['sheller.c'])

setup(
    name='sheller',
    version='1.0',
    description='Komutları popen() ile çalıştıran modül',
    ext_modules=[module],
)
