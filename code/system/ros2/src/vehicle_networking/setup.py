from setuptools import setup

package_name = 'vehicle_networking'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/config', ['config/device_identifiers.json']),
    ],
    install_requires=[
        'setuptools',
        'pyserial',
    ],
    zip_safe=True,
    maintainer='ethanreynolds',
    maintainer_email='ethanreynolds451@gmail.com',
    description='All code to manage interfacing between computer and connected devices',
    license='None',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'get_device_info_tool = vehicle_networking.get_device_info_tool:main',
            'serial_manager = vehicle_networking.serial_manager:main',
            'control_serial_interface = vehicle_networking.control_serial_interface:main',
            'sensor_serial_interface = vehicle_networking.sensor_serial_interface:main', 
        ],
    },
)
