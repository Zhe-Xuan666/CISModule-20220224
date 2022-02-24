POUT=/home/cismodule/Downloads/makefrom_StaticLib
$POUT
ar rvs ../libcismodule.a ../v4l2_camera.o ../Cuda.o ../readIni.o ../myFuncts.o
cp ../libcismodule.a ../src/b.h ../src/myFuncts.h ../config.ini $POUT
