```
/Users/zichunwang/Qt/6.4.2/macos
/Users/zichunwang/calculator
#cmake -DCMAKE_PREFIX_PATH=path/to/Qt/6.4.2/your_platform -S <source-dir> -B <build-dir> -G Ninja
cmake -DCMAKE_PREFIX_PATH=/Users/zichunwang/Qt/6.4.2/macos -S /Users/zichunwang/calculator/ -B /Users/zichunwang/calculator_built/ -G Ninja
```
