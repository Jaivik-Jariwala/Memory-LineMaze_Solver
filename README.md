# mesmerize

[Arduino Maze Solver Robot](https://youtube.com/playlist?list=PL3uaVtgnSHfcN1hnLmKRi3_w1aOq2ehbk&si=3nsC0vLpFWi2FMTr)

# Maze Design

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/4da37012-844e-4861-992f-332cb227e114/Untitled.png)

                Top View 

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/bda792fc-d8d5-4933-8032-e77cac9425fa/Untitled.png)

              Front View

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/14baef84-7818-4456-85e0-3004cf5b8f95/Untitled.png)

            Checkpoint

### Applying Left-hand follow

### Applying Right-hand follow

# Design

Model 1

[Line Following Robot - CAD Model - Download Free 3D model by akshayansinha](https://sketchfab.com/3d-models/line-following-robot-cad-model-e07a600bde234196926d005724d1dfa6)

https://sketchfab.com/3d-models/line-following-robot-cad-model-e07a600bde234196926d005724d1dfa6

Model 2

need one with top plate to cover the bot

and 2 ball-support wheels 

Components

- 2 base Plate
- screw to fit the board
- 2 ball wheel
- 3d printer

- wheels
- holders
- support
- spool

An Autonomous bot must fit into the box of dimensions 220 X 220 X 220 all in mm (lxbxh).

[Building an easy Line Follower Robot using Arduino Uno](https://circuitdigest.com/microcontroller-projects/arduino-uno-line-follower-robot)

# Circuit

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/10e95a4a-6427-493e-821a-76b38c3027ef/Untitled.png)

Components

- Geared Motor
- L293D Motor Driver
- Wire sets
- Led- Green & Red start and stop

- Arduino Uno
- 5 channel IR sensor
- 12V Battery
- Potential difference between 2 points criteria 24V

# Budget

| Serial Number | Item name | Quantity | Price | link | Availability |
| --- | --- | --- | --- | --- | --- |
| 1. | L293D Motor Driver Shield For Microcontrollers-4 Channel Driver-Bipolar Pulse-Width-Method(PWM) | 1 | 129.0 | https://robu.in/product/l293d-motor-driver-servo-shield-for-arduino/ | need to purchase |
| 2.  | Arduino Uno | 1 | 336.0 | NIL | Available (jaivik) |
| 3.  | IR Sensor Array 5 Way TCRT5000L Module Generic | 1 | 195.0 |  |  |
| 4. | Wires  | sets |  |  |  |
| 5.  | Battery | 2 |  |  |  |
|  |  |  |  |  |  |

---

# Criteria to achieve

fit robot in box 220x220 mm

it have to complete dry run in 150s ( 180s actual )

it have to complete shortest path in  100s ( 150s actual )

---

# Notes

from lecture

video 2 : Assembly of robot

- weight distribution 3/4 weight on back and 1/4 on front
- negative battery to ground of driver, positive to input of driver shield

video 3 : understanding the Maze and robot prog

- Understanding maze
- Left hand follow following algorithm & Right hand follow following algorithm
- understanding intersections, dead end

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/ef7189e3-9339-4aad-a8f0-b30f12612419/Untitled.png)

- Junctions LEFT_hand_Follow
    - END : we need to stop
    - T : we need to go left
    - U : need to turn
    - CROSS : need to have 1,2,3 and go 1 at time
    - LEFT TURN : need to go left
    - RIGHT TURN : need to go right
    - Right T : need to go straght
    - LEFT : T need to go Leftsc
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/7ca6a46d-033f-45fd-8d88-742a26ee0d08/Untitled.png)
    
    sample maze 
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/c3d8bcf3-dd05-4b5b-a62d-88158858f90d/Untitled.png)
    
    L B L L L B S B L L B S L L
    
    soln RL
    
    apply on our maze 
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/eb5078a7-c865-4172-9676-2fcedfed7f82/Untitled.png)
    
    [ Start,  L, L, B, L, L, L, B, L, L, S, S, L, B, L, L, S, S, L, B, L, L, B, L, L, B, L, L, B, L, L, B, L, End]
    
    Soln 
    
    L R R R R S/L L R R R R R R R R
    
    video : 4 Path Optimisation 
    
    reduction 
    
    - LBL = S
    - LBS = R
    - RBL = B
    - LBL = S
    - SBS = B
    - SBL = R
    
    example 
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46048df6-d54d-4db8-97e8-9689c541c740/3c29934b-5987-400f-b2d6-fbc3ce8a4052/Untitled.png)
    
    on our calculate reduction 
    
    L, L, B, L, L, L, B, L, L, S, S, L, B, L, L, S, S, L, B, L, L, B, L, L, B, L, L, B, L, L, B, L
    
    ans. 
    
    Video 5: importing lib and programming robot basic movement
