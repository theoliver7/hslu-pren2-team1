# PREN2 Team1 - Der Besteiger
Code for the the PREN FS2021 robotics challenge at @ HSLU 

<img src="../media/IMG_20210604_115251.jpg" alt="alt text" width="500" height="320">

## Overview

The goal of the project was to develop a prototype of a vehicle that can detect objects and climb up some stairs while avoiding obstacles on the way. 

The team consisted of two mechanical engineers, two electrical engineers, and two software engineers.

## Hardware
    - Raspberry Pi 4 Model B
    - Raspberry Pi Kamera Module V2
    - Tinyk22(Microcontroller)

## Object Detection & Path Planning
To enable path planning and object detection a tensorflow model was trained via transfer learning. 

The path was planned by converting the captured image into a matrix and running A* algorithm to determine the shortest path. 

<img src="../media/stair-detection.jpg" alt="alt text">
