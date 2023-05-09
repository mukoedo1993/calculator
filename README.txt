# Calculator Zichun Wang #
## What is this project for? ##
I followed a youtube tutorial for this. But I add a switch function so that you can switch between int and float 
to enhance the saving of potential memory resources as required by CS309 course(software engineering).


## What to do for average computer users? ##
calculator.app.zip. Unzip it and use it on macos. It should work.

## What to do? for ordinary developers. Follow the following steps on terminal:##
```
/Users/zichunwang/Qt/6.4.2/macos
/Users/zichunwang/calculator
#cmake -DCMAKE_PREFIX_PATH=path/to/Qt/6.4.2/your_platform -S <source-dir> -B <build-dir> -G Ninja
cmake -DCMAKE_PREFIX_PATH=/Users/zichunwang/Qt/6.4.2/macos -S /Users/zichunwang/calculator/ -B /Users/zichunwang/calculator_built/ -G Ninja
#cd path/to/build/dir
cd .. && cd calculator_built
ninja
```

## What to do? for advanced developers. ##

See ./mainWindow.h for interface and ./mainwindow.cpp and ./main.cpp for interface.

##.What is version control in the project? ##
By using git. Read git's tutorial for more helps.

## What is white box and black box test here? ##
Black box test was done by myself.
Mr. Rahman helped to me to do the white box test.
The interface is so clear and simple so it does not need more explanations.

## What is TDN and GDN? ##
