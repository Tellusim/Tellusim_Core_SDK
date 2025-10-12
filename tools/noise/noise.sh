#!/bin/bash

SIZE=64
LAYERS=32
SIGMA=1.6
BITS=8
INIT=10
GRID=8

NAME=noise_${SIZE}x${SIZE}_l${LAYERS}_s${SIGMA}_i${INIT}

./noised -size $SIZE -layers $LAYERS -bits $BITS -init $INIT -sigma $SIGMA -seed 1 -o ${NAME}_x.image -oh ${NAME}_x.txt -of ${NAME}_f_x.image -ox ${NAME}_fx_x.image -oy ${NAME}_fy_x.image
./noised -size $SIZE -layers $LAYERS -bits $BITS -init $INIT -sigma $SIGMA -seed 3 -o ${NAME}_y.image -oh ${NAME}_y.txt -of ${NAME}_f_y.image -ox ${NAME}_fx_y.image -oy ${NAME}_fy_y.image

ts_imaged -v ${NAME}_f_x.image -grid $GRID -o ${NAME}_f_x.image
ts_imaged -v ${NAME}_f_y.image -grid $GRID -o ${NAME}_f_y.image

ts_imaged -v ${NAME}_fx_x.image -grid $GRID -o ${NAME}_fx_x.image
ts_imaged -v ${NAME}_fx_y.image -grid $GRID -o ${NAME}_fx_y.image

ts_imaged -v ${NAME}_fy_x.image -grid $GRID -o ${NAME}_fy_x.image
ts_imaged -v ${NAME}_fy_y.image -grid $GRID -o ${NAME}_fy_y.image

ts_imaged -v ${NAME}_x.image ${NAME}_y.image -combine -o ${NAME}.image
