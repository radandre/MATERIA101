M300
;M71 (Livella piano Z)
M71 (Level Z plate)
G21 ; set units to millimeters
T0
G90 (set positioning to absolute)
G28 ;Home all axis
G28 X260
G1 Z5 F3300.0
G1 X50 Y160
G1 Z0
;M71 (Regola vite 1)
M71 (Calibrate screw 1)
G1 Z5 F3300.0
G1 X50 Y80
G1 Z0
;M71 (Regola vite 2)
M71 (Calibrate screw 2)
G1 Z5 F3300.0
G1 X200 Y80
G1 Z0
;M71 (Regola vite 3)
M71 (Calibrate screw 3)
G1 Z5 F3300.0
G1 X200 Y160
G1 Z0
;M71 (Regola vite 4)
M71 (Calibrate screw 4)
G1 Z5 F3300.0
G1 X130 Y100
G1 Z0
;M71 (Verifica viti)
M71 (Check screws)
G1 Z10
M117 Sharebot NG     
M84
