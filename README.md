# astein | minitalk

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