# balk_cpp

Calculate the balk problem.
##### Usage:
```sh
make run [INPUT=<input_file_name>]
```
##### Input file format:
```txt
balk_size segment_length E J
[term1]
[term2]
[term3]
...
```
balk_size: int. Number of balk segments.   
segment_length: double. Length of each balk segment.   
E J: doubles. Еlastic material constants.   
Term is one of the following constructions:
```txt
R shift
Z shift
K shift coef
P shift force
M shift moment
Q begin end force
```
R - hinge support.   
Z - rigid fixing.   
K - elastic support. Coef - elasticity coefficient.   
P - concetrated force.   
M - moment.   
Q - uniform load.   

#### A simple example:
##### input.txt file:
```txt
10 1.0 100 200
R 0
Z 10
P 7 50
```
Run the program:
```sh
make run INPUT="input.txt"
```

![Alt text](https://github.com/maksimkulis/balk_cpp/blob/master/doc/image.png)
