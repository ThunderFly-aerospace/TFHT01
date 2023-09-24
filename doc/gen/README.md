# PCB

Board size: 30.0x15.0 mm (1.18x0.59 inches)

- This is the size of the rectangle that contains the board
- Thickness: 0.89 mm (35 mils)
- Material: FR4
- Finish: HAL lead-free
- Layers: 2
- Copper thickness: 35 µm

Solder mask: TOP / BOTTOM

- Color: Green

Silk screen: TOP / BOTTOM

- Color: White


Stackup:

| Name                 | Type                 | Color            | Thickness | Material        | Epsilon_r | Loss tangent |
|----------------------|----------------------|------------------|-----------|-----------------|-----------|--------------|
| F.SilkS              | Top Silk Screen      |                  |           |                 |           |              |
| F.Mask               | Top Solder Mask      | Green            |        10 |                 |           |              |
| F.Cu                 | copper               |                  |        35 |                 |           |              |
| dielectric 1         | core                 |                  |       800 | FR4             |       4.5 |        0.020 |
| B.Cu                 | copper               |                  |        35 |                 |           |              |
| B.Mask               | Bottom Solder Mask   | Green            |        10 |                 |           |              |
| B.SilkS              | Bottom Silk Screen   |                  |           |                 |           |              |

# Important sizes

Clearance: 0.2 mm (8 mils)

Track width: 0.3 mm (12 mils)

- By design rules: 0.15 mm (6 mils)

Drill: 0.5 mm (20 mils)

- Vias: 0.5 mm (20 mils) [Design: 0.4 mm (16 mils)]
- Pads: 1.0 mm (39 mils)
- The above values are real drill sizes, they add 0.1 mm (4 mils) to plated holes (PTH)

Via: 0.8/0.4 mm (31/16 mils)

- By design rules: 0.4/0.3 mm (16/12 mils)
- Micro via: yes [0.2/0.1 mm (8/4 mils)]
- Buried/blind via: yes
- Total: 36 (thru: 36 buried/blind: 0 micro: 0)

Outer Annular Ring: 0.15 mm (6 mils)

- By design rules: N/A mm (N/A mils)

Eurocircuits class: 4B
- Using min drill 0.5 mm for an OAR of 0.15 mm


# General stats

Components count: (SMD/THT)

- Top: 1/6 (SMD + THT)
- Bottom: 16/1 (SMD + THT)

Defined tracks:

- 0.3 mm (12 mils)
- 0.4 mm (16 mils)
- 0.5 mm (20 mils)
- 1.0 mm (39 mils)

Used tracks:

- 0.3 mm (12 mils) (54) defined: yes
- 0.4 mm (16 mils) (111) defined: yes

Defined vias:


Used vias:

- 0.8/0.4 mm (31/16 mils) (Count: 36, Aspect: 1.1 A) defined: no

Holes (excluding vias):

- 1.0 mm (39 mils) (12)
- 3.0 mm (118 mils) (6)

Oval holes:


Drill tools (including vias and computing adjusts and rounding):

- 0.5 mm (20 mils) (36)
- 1.0 mm (39 mils) (12)
- 3.0 mm (118 mils) (6)




