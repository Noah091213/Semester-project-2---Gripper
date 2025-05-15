# Soda can gripper

This gripper is an attachement for a UR5, meant to pick up empty cans of soda or beer. 

## Table of Contents

- [About the Project](#about-the-project)
- [Getting Started](#getting-started)
- [Usage](#usage)

## About the Project

The gripper is primarily 3d printed, and controlled with a Raspberry Pi 4. The plan is to use a 24v power supply to power the project, and a 12v dc motor to open and close.

## Getting Started

- Copy the github repo on the Raspberry Pi.
- Create a sub folder for the build
- Open the subfolder and run cmake, then make
- Run the compiled program

### Prerequisites

To run the program, pigpio is requried to be installed on the Raspberry Pi first.
Instructions for downloading the library can be found here https://abyz.me.uk/rpi/pigpio/download.html

### Installation

Step-by-step guide on how to install and run the project. If changes need to be made and pushed to github use the SSH key instead

```bash
# Example to only download
git clone https://github.com/Noah091213/Semester-project-2---Gripper
mkdir build
cd build
cmake ..
make
# Profit!
```
```bash
# Example to download and be able to upload later
git clone git@github.com:Noah091213/Semester-project-2---Gripper.git
mkdir build
cd build
cmake ..
make
# Profit with extra steps!
```

## Usage

To run the program use the following:

```bash
# To run the program
cd build
sudo ./uv5Gripper
# Using sudo is very important as the Pi needs access to the GPIO pins for the program to run
```

