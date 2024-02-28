<!-- ahokcool HEADER START-->
---
<a id="top"></a>
<div align="center">
  <a href="https://github.com/ahokcool/ahokcool/blob/main/README.md">
    <img src="images/alexgit.png" alt="Logo" width="150">
  </a><br>
  An overview of all my projects can be found here: <a href="https://github.com/ahokcool/ahokcool/blob/main/README.md" target="_blank">ahokcool</a><br><br>
  <a href="https://www.42lisboa.com">
    <img src="images/logo42.svg" alt="Logo" width="100">
  </a><br>
  This project was created as part of my studies at: <a href="https://www.42lisboa.com" target="_blank">42 Lisboa</a><br>
</div>

---
<!-- ahokcool HEADER END-->
<!-- PROJECT HEADER START -->
<br />
<div align="center">
  <a href="./">
    <img src="images/logo.gif" alt="Logo" width="600">
  </a>
  <h1 align="center">minitalk</h1>
<p align="center">
    Createing a communication program in the form of a client and server using UNIX signals.
</p>
</div>
<br>
<!-- PROJECT HEADER END -->

## :bulb: Lessons learned
- working with the API of [a graphics library](https://github.com/42Paris/minilibx-linux)
- understanding points in 2 and 3 dimensional space, vectors and trigonometric functions
- [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- Using a [rotation matrix](https://en.wikipedia.org/wiki/Rotation_matrix) to transform coordinates

## Installation
```
$ git clone --recurse-submodules https://github.com/ahokcool/fdf.git)   # Clone
$ cd fdf                                                                # Change directory
$ make                                                                  # Compile
$ ./fdf map_file                                                        # Run
```


# astein | minitalk

## Install

`git clone --recurse-submodule https://github.com/ahokcool/minitalk.git`

## Test

`make test`

## Connection Procedure
to get more of an binary vibe I renamed the signals...<br />
   ```USR1``` = ```BIT_0```<br />
   ```USR2``` = ```BIT_1```<br />
| Step																				| Client->Server					 				| Server->Client					|
| ------------- 																	| ------------- 					 				| -------------  					|
| say hello																			| ```BIT_0```						 		 				| ```BIT_0``` 							|
| ur ready server?																	| ```BIT_1``` (each second)				 				| ```BIT_1``` (if ready) 					|
| send message literally 'bit by bit'<br /> (waiting for an answer after each bit)	| ```BIT_0``` (if bit of current char is 0)<br />```BIT_1``` (if bit of current char is 1)	 		| ```BIT_0```<br />(to confirm the reception)	|
| send and additional ```/0``` to indicate the end of the message	| ```BIT_0``` (8 times)| ```BIT_1```								|

☝️only if all characters of the message have been transmitted and the client recives the ```BIT_1``` signal from the server it prints ```SUCCESS```!



<!-- ahokcool FOOTER-->
---
<p align="center">
  <a href="#top">🔝 back to top 🔝</a>
</p>
