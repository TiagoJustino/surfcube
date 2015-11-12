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
(NOAA)](http://www.noaa.gov/index.html) [National Data Buoy Center
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
water out of the container as required. Through a series of tests, we found
that 62 steps of the Stepper Motor allows us to fill 1 mm of water in the tank.

* **Wave Height:** Small waves are generated based on wave height data. The
waves are generated using a mechanical actuator using a Micro Servo motor.
The rotation motion of the servo motor is converted into linear motion using
a scotch-yoke actuator, which holds a platform that creates the waves. For
different wave height values, we adjust the max rotation arc of the servo
motor, as well as the speed with which it moves.

* **Wave Period:** The wave period is displayed by adjusting the gap between
each wave motion.

* **Water Temperature:** Water temperature is indicated using breathing
back-lights. This is done by using a combination of Red, Green and Yellow
LEDs at the back of the display device. The lights also serve another purpose -
it helps create interesting visual effects with the water. This, in
combination with the diffuse texture of the container, make the display look
visually pleasing.

* **Surfing Conditions:** A floating 3D printed ‘surfer’ was created to
indicate surfing conditions in the water. The back-lights of the device make
the surfer easy to notice.

## Materials

The following materials were used in this project:

* [Acrylic Sheets](http://www.lowes.com/pd_55844-1638-11G0810A_0__?productId=3143395) - 8in x 10in x 0.083in (used for prototyping)
* [Acrylic Sheets](https://www.homedepot.ca/en/home/p.clear-acrylic-sheet---118-inch-x-36-inch-x-72-inch.1000126445.html?redir=s) - 36in x 72in x 0.118in
* [Arduino Uno](http://www.adafruit.com/products/50)
* [Adafruit motor shield](http://www.adafruit.com/products/1438)
* [Micro Servo (x 1)](http://www.adafruit.com/products/1438)
* [200 step DC Stepper Motor (x 1)](http://www.adafruit.com/products/1438)
* Sheet of wood (x1)
* [150ml Syringe (x2)](http://www.amazon.com/gp/product/B013DI05HI)
* Red, Green and Yellow LEDs (2 each)
* [Threaded Rod](http://www.amazon.com/gp/product/B00HS7VYIU)
* [Motor Shaft Coupler](http://www.amazon.com/gp/product/B00DCAINOU)
* 12V DC Power Adapter
* Silicone Sealant (x1)
* Hot Glue

## Design & Method

After two rounds of prototyping, we arrived at this design for the project.

### Water Tank

The image shows below the acrylic cube which acts as the container for the water.
This ‘tank’ is designed in a rectangular manner, so that it may accommodate the
wave actuator, which will discuss shortly. The finished product is designed
such that, only a cubical part of the ‘tank’ is visible, thereby hiding the
actuator from view. The various dimensions were designed using Inkscape and
Adobe Illustrator, and cut from an acrylic sheet using a laser cutter.

This phase had to be completed first so as to be able to test various
mechanical actuators in the given configuration. As the sketch suggests, we
discussed the possibility of using a mesh to separate the two parts of the
container. However, we concluded that adding this part provided no design
significance in terms of aesthetics, with the added possibility that it might
impede the flow of waves.

![SurfCube Sketch](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image01.jpg)

![Final Acrylic Tank](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image02.jpg)

### Wave Actuator

After testing different types of mechanical actuators, we were able to
successfully able to generate waves using a [Scotch-Yoke
mechanism](https://commons.wikimedia.org/wiki/File:Scotch_yoke_animation.gif#/media/File:Scotch_yoke_animation.gif).
This was necessary to use as we needed to convert the rotational motion from
the Micro Servo Motor to linear motion. We added a flat platform surface that
would create the waves in the tank. The design of the mechanism also ensures
that the actuator maintains a strict linear motion and does not sway from the
force of the water.

The actuator can be seen in the image above. This part was designed using
Tinkercad and 3D printed.

Here is a video of the wave actuator in action - Youtube:
[https://youtu.be/HZYjWmM6quM](https://youtu.be/HZYjWmM6quM).

![Final Acrylic Tank](https://upload.wikimedia.org/wikipedia/commons/5/59/Scotch_yoke_animation.gif "Scotch yoke animation by BRoys - By Uploader. Licensed under CC BY-SA 2.5 via Commons")

*Scotch yoke animation by BRoys - By Uploader. Licensed under CC BY-SA 2.5 via Commons*

### Water Pump

A dual-syringe pump mechanism was designed for pumping water in/out of the cube
based on tide height levels. The pump system is controlled using a DC Stepper
Motor. The design for this system was inspired by
[this](https://hackaday.io/project/1838-open-syringe-pump). The threaded rod
and bolt for the motor were purchased separately, and were crucial for
operating this system.

The parts that hold the syringe were designed using Tinkercad and 3D printed.

![Stepper-controlled water pump](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image05.jpg)

Here is a video of the water pump in action - Youtube: [https://youtu.be/-vanxsn2oxY](https://youtu.be/-vanxsn2oxY)

### Lighting

Red, Green and Yellow LEDs were used to provide a backlight in the display
case. This, in combination with the water, adds a good visual effect to the
display. The LEDs are made to glow in a breathing pattern, that appears to
complement the water flow (code was taken from
[here](http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/)).

The LEDs are placed such that they illuminate the display from one of the side
walls. This is done by placing them between one of the outer walls of the cube,
and the wooden case.

Here is a short video on how the cube looks with light breathing through the
cube - Youtube: [https://youtu.be/0_491yBwqlU](https://youtu.be/0_491yBwqlU).

### Surfing Conditions

We also try to represent surfing conditions using a small 3D printed surfer
"Sam The Surfer". From tests, we found that the 3D printed surfer would drown
after experiencing some really violent waves. This happened due to the odd
weight distribution. This was later fixed by adding a heavy object (screw) to
the base of the surfer, and using some styrofoam (See two images below).

![3D printed Surfers](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image04.jpg)

![Fixed Surfer](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image07.jpg)

Here’s a video of Sam The Surfer - Youtube: [https://youtu.be/d6fK8g5SR70](https://youtu.be/d6fK8g5SR70)

### Device Casing

In order to make the final product more aesthetic, we decided to create a wood
casing to hold the device. The sketch below describes how the acrylic container
fits into the wooden casing. As mentioned earlier, one purpose of the wooden
casing is hide the wave actuator from view.

The case dimensions were made in Inkscape and cut using a laser cutter.

![Laser cut wood case](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image06.jpg)

![Final SurfCube](https://raw.githubusercontent.com/TiagoJustino/surfcube/master/images/image08.jpg)

## The finished product

After putting all the components together, we have our final finished product!
Here is a video of the working product - Youtube (Part 1):
[https://youtu.be/Xg0Dip0avz8](https://youtu.be/Xg0Dip0avz8)

## Challenges

As this project involved working with water, some major challenges were encountered, which required a lot of experimentation.

1. Preventing water leakage and protecting the electronics from water damage;

2. Moving water in and out of the container to represent the tidal data;

3. Creating waves of varying sizes and speeds to represent the wave data.

  1. Designing a 3D printing an efficient wave actuator that converts the rotational motion of the Micro Servo to a linear motion.

4. Aesthetic design of the device


## References

1. Matthews, T., Rattenbury, T., Carter, S., Dey, A., & Mankoff, J  "A peripheral display toolkit". (2003).

2. Jeremy M. Heiner, Scott E. Hudson, Kenichiro Tanaka. "The Information Percolator: Ambient Information Display in a Decorative Object". UIST ‘99, pg 141-148.

3. Mårten Pettersson. "WaterCalls: An ambient call queue for cooperation between emergency service centers". Personal and Ubiquitous Computing 2004, pg 192-199.

4. Tempescope website. http://www.tempescope.com/ 
