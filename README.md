# SurfCube

by [Tiago Justino](https://github.com/TiagoJustino) and [Dhananjai Hariharan](https://github.com/DhananjaiH).

## Overview

SurfCube is an ambient display for presenting wave and tide data for surfers,
or for those that live near the coast. This allows a user to keep track of the
ocean/sea tide and wave conditions at a set location with a glance. It is also
designed to be visually pleasing and unobtrusive.

## Description

The SurfCube is an ambient display device for surfers and people living close
to the coast. Designed as a table-top object to blend with other objects, the
SurfCube is a rectangular container filled with water that represents tidal
conditions at a certain location.

For this device, water was chosen as the primary display material as it
provides a natural mapping to the information being conveyed. It also works
well as a medium for communicating information through visual and aural
channels. As an ambient notification system, the device is meant to act in
between the “change blind” and “make aware” levels of notifications, as defined
by Mathews et al [1], and thus, does not demand the user’s attention to serve
its purpose.

The SurfCube is a 18.4cm x 9.7cm x 10cm (length x width x height) ambient
device made out of acrylic and wood. It also uses an Arduino Uno, a DC stepper
motor and some syringes. Details on the design and implementation of this
device are further below.

## Relevant Work & Inspirations

This section contains some research and projects that were relevant, or
provided inspiration for this project.

### Water as a display material

Heiner et al. [2] designed the Information Percolator, an ambient device that
acts as a decorative object as well as an information display. This device
consists of an array of vertically arranged tubes containing water. The device
allows air bubbles to pass through the tubes in a controlled manner. By
considering each of the bubbles as a pixel, the display is able to display
patterns and various types of information in the form of text and images. A
video demonstration of the device can be found
[here](http://www.cs.cmu.edu/~hudson/bubbles/).

WaterCalls [3] presents a novel concept for visualizing call traffic in
coordinating emergency call centres. Tempescope [4] is another ambient device
that uses water as a material for representing weather conditions.

Besides these, commercial products such as [Tide
Clocks](https://en.wikipedia.org/wiki/Tide_clock) also exist, which are devices
that make predictions about the tides based on the Moon’s apparent position
about the Earth. These may also be considered as an ambient device, although it
requires significant amount of a user’s attention to gain information.

## Data Specifications

### Data Source

Although there are a wide range of web platforms available for accessing wave
and tidal data, it was observed that most of these made the use of [National
Oceanic and Atmospheric Administration’s
(NOAA)](http://www.noaa.gov/index.html) or [National Data Buoy Center
(NDBC)](http://www.ndbc.noaa.gov/) open data for providing valuable
information. The SurfCube would reflect the data gathered from this source.

### Relevant Data

The following metrics are displayed in this device:

* Tide Height
* Wave Height
* Wave Period
* Water Temperature

### Data Visualization

Water will be used as a medium for communicating this data.

* **Tide Height:** Water level in the display container is adjusted based on
tidal height data. This is done using a dual-syringe pump system that is
controlled using a stepper motor. This setup allows for injecting or pumping
water out of the container as required.

Through a series of tests, we found that 62 steps of the Stepper Motor allows
us to fill 1 mm of water in the tank.

* **Wave Height:** Small waves are generated based on wave height data. The
waves are generated using a mechanical actuator using a Micro Servo motor.
The rotation motion of the servo motor is converted into linear motion using
a scotch-yoke actuator, which holds a platform that creates the waves.

For different wave height values, we adjust the max rotation arc of the servo
motor, as well as the speed with which it moves.

* **Wave Period:** The wave period is displayed by adjusting the gap between
each wave motion.

* **Water Temperature:** Water temperature is indicated using breathing
back-lights. This is done by using a combination of Red, Green and Yellow
LEDs at the back of the display device. The lights also serve another purpose
- it helps create interesting visual effects with the water. This, in
combination with the diffuse texture of the container, make the display look
visually pleasing.

* **Surfing Conditions:** A floating 3D printed ‘surfer’ was created to
indicate surfing conditions in the water. The back-lights of the device make
the surfer easy to notice.

