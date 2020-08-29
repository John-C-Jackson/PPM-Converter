# Authors
John Jackson jcj52@nau.edu\
Sara Huber skh258@nau.edu

# Usage
Example:
```
./ppm_read_write 6 input.ppm output.ppm
```
Our program follows the usage format specified in the project requirements specifications, 
taking in the name of the program, the number corresponding to the desired file conversion, 
and the two files to be run through the program (in that order). The program is designed to catch many of the potential errors that could arise when trying to run the program, and utilizes five support functions in addition to the main (one for error reporting, and the remaining four to read or 
write P6 or P3 .ppm files).

# Known Issues
There are some major issues we weren't able to resolve in time.
* This program doesn't convert ASCII to binary nor vice versa.
* The file data is probably not stored correctly. We had some success converting a P6 to another P6, (i.e. storing rawbits data in memory and writing that data to a new file), but the resulting image is roughly 3 times smaller than expected.
