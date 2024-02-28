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
    Create a communication programme in the form of a client and a server using UNIX signals.
</p>
</div>
<br>
<!-- PROJECT HEADER END -->

## :bulb: Lessons learned
- UNIX Signals
- C signal handling

## Installation
```
$ git clone --recurse-submodule https://github.com/ahokcool/minitalk.git  # Clone
$ cd minitalk                                                             # Change directory
$ make                                                                    # Compile
$ ./server                                                                # Start server
$ ./client "Message" <PID of Server>                                      # Send Messages
```

## Test
`make test`

## Connection Procedure
To get more of an binary vibe I renamed the signals...<br />
   ```USR1``` = ```BIT_0```<br />
   ```USR2``` = ```BIT_1```<br />
| Step																				| Client->Server					 				| Server->Client					|
| ------------- 																	| ------------- 					 				| -------------  					|
| say hello																			| ```BIT_0```						 		 				| ```BIT_0``` 							|
| ur ready server?																	| ```BIT_1``` (each second)				 				| ```BIT_1``` (if ready) 					|
| send message literally 'bit by bit'<br /> (waiting for an answer after each bit)	| ```BIT_0``` (if bit of current char is 0)<br />```BIT_1``` (if bit of current char is 1)	 		| ```BIT_0```<br />(to confirm the reception)	|
| send and additional ```/0``` to indicate the end of the message	| ```BIT_0``` (8 times)| ```BIT_1```								|

☝️only if all characters of the message have been transmitted and the client recives the ```BIT_1``` signal from the server it prints ```SUCCESS```!

This allows multiple clients to connect to the server at the same time:

<p align="center">
 <a href="./">
  <img src="images/twoclients.gif" alt="Logo" width="600">
 </a>
</p>

<!-- ahokcool FOOTER-->
---
<p align="center">
  <a href="#top">🔝 back to top 🔝</a>
</p>
