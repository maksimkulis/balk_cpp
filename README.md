# balk_cpp

Calculate the balk problem.
##### Usage:
```sh
make run INPUT=<input_file_name> [OUTPUT=<output_folder_name>]
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
##### examples/input1.txt file:
```txt
20 1.0 210e9 8.3e-8
R 0
R 3
R 9
R 17
Z 20
M 2 100.9
Q 6 13 -15
K 15 0.0001
P 16 -100
```
Run the program:
```sh
make run INPUT="examples/input1.txt" OUTPUT="outputs"
```
If all is OK, you will see a very cool picture of the deformed balk. Also this code creates a folder "outputs", where you can see the results of function calculation

```sh
ls outputs
```
```
image.png  out1.txt  out2.txt  out3.txt out4.txt
```
##### image.png:

![Alt text](https://github.com/maksimkulis/balk_cpp/blob/master/doc/image.png)
