# delFile and hexview


delFile


DESCRIPTION: Randomizes bytes in a file


INTENDED PURPOSE: I wanted to make a program that would randomize all the bytes in a file so that the original contents couldn't be recovered after the file was deleted. However, I came upon a question that would be crucial to whether the program would work as intended or not:


Does fopen(file, "w") overwrite the original block(s) being used by the file, or does is it set the old blocks as free and then begin writing to new blocks?


I asked this question on stackoverflow, and the answers I received said that it depends on the file system and operating system. From what I saw, it looks like the original contents will not be overwritten in most cases. This was upsetting, since it meant that my program would not actually be overwritting the original contents of the file. All it would do is generate a file filled with random bytes. However, the program still works as intended if the particular file system and operating system overwrite the original blocks. 


Here is the question I asked on stackoverflow:


https://stackoverflow.com/questions/56980104/does-fopenfile-w-write-to-a-new-block?noredirect=1#comment100497128_56980104


USAGE


./delFile -size <file_name>


Only randomizes the bytes that are being used


./delFile -nbytes <num_bytes> <file_name>


./delFile -blocks <file_name>


Randomizes all the bytes in the blocks being used by the file


./delFile -nblocks <num_blocks> <file_name>


Writes n blocks of random bytes to the file


./delFile -help


Provides info on how to use delFile


=====================================


hexview


DESCRIPTION: Displays all bytes in a file in hex. It's basically my version of the hexdump utility.


USAGE


./hexview file.txt


Print hex contents of file


./hexview file.txt bytesPerLine


Prints bytesPerLine bytes on each line


./hexview -help


View usage info
