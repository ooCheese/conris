# CONRIS  - CONSOLE TETRIS

CONRIS is  a 'Tetris' game for the Linux Terminal.

```
--------------------
|                    |
|      # # #         |   POINTS: 622
|        #           |   LINES: 14
|        # #         |   LEVEL: 2
|          # #       |
|  # #     #       # |   NEXT: I
|# #   #   # #   # # |   HOLD: Z
|  # # #   # # # # # |
|# # # # # # # # #   |   |A| LEFT
|    #   # # # # #   |   |D| RIGHT
|# # # # # # # # #   |   |S| DOWN
|# #   # # # # # # # |   | | DOWN TO GROUND
|  # # # # # # # # # |   |R| ROTATE
|# # # # # # # #   # |   |H| HOLD
|# # # # # # #   # # |
|# # # # # # #   # # |   |Q| QUIT
|# #   # # # # # # # |
|# #   # # # # # # # |
|# #   # # # # # # # |
|# #   # # # # # # # |
--------------------
```

## Usage

install <b>Makefile</b> (make), <b>gcc</b> (as C-Compiler)
and <b>ncurses</b>

you can install gcc and ncurses on Debian/Ubuntu via apt-get:

```
sudo apt-get install build-essential libncursesw5-dev
```
and make with
```
sudo apt install make
```


compile and run the programm with the command "<b>make run</b>" in the conris folder 
```
  ~/conris$ make run
```

change the configuration (keymapping) in the <b>config.properties</b> file

### Config
change the configuration in (Java-Propertie like) <b>config.properties</b> file

#### Keybindings
only use <b>one</b> ASCII Signs (no int values)\
The Empty (' ') Sign is for SPACE

```
key.down=S
key.left=A
key.right=D
key.rotate=R
key.quit=Q
key.hold=H
key.down2ground= 
```

#### Print Speed
Change the Speed of the prints in the Console.
The Value is in fps (value/1 sec).

```
speed.print=20
```

#### Field Size
Change the field width(x) and height(y). Integer Value > 0 

```
field.x=10
field.y=20
```

#### Countdown
start a Countdown after startup

Enable Countdown. (Java) Bool-Value (true/false) every other word is equels to false 

```
start.countdown=true
```

Number of Counts
```
start.countdown.counts=3
```

The duration of the countdown

```
start.countdown.seconds=1
```

#### Look
change the in the "view" used signs.
only use <b>one</b> ASCII Signs (no int values)

Look of a cell without a block
```
look.empty= 
```

Look of a block

```
look.block=#
```

#### Color
change the Consolecolors

the only valid values are:
(NORMAL,RED,GREEN,YELLOW,BLUE,MAGENTER,CYAN,WHITE)

```
color.field= RED
color.I = CYAN
color.L = WHITE
color.J = BLUE
color.T = MAGENTER
color.S = GREEN
color.Z = RED
color.O = YELLOW
```

### Random
change the (random)seed of the block generator.

if seedbytime is true than the seed whould generate by the (system)time.
otherwise the system use the value of rand.seed (unsigned int)

```
rand.seedbytime=true
rand.seed=0
```

