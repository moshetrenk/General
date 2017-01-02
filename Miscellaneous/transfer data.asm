;12/01/2015
;Assembly - Transfering Data Between Files
INCLUDE Irvine32.inc

.data
input_filename DD  100 DUP(0)
BUFFER DB 17 DUP(0)
prompt DB "Please enter the input_filename", 0dh, 0ah, 0
prompt2 DB "Please enter an output filename", 0dh, 0ah, 0
errormsg DB "Error with inputfile handle", 0dh, 0ah, 0
errormsg2 DB "Error with outputfile handle", 0dh, 0ah, 0
fileHandle DD ?
bytesRead DD ?

output_filename DD 100 DUP(0)
;C:\Users\Moshe_000\Desktop\Ring.txt
BUFFER2 DB 17 DUP (0)
outputfileHandle DD ?
bytesWrote DD ?

.code
main PROC
call Clrscr

mov ecx, 100h							;user can enter up to 100 characters for the filename
mov edx, OFFSET prompt2					;prompt user to
call writestring						;enter a filename

mov edx, OFFSET output_filename			;read it in
call readstring

mov edx, OFFSET output_filename			;create the output file
call CreateOutputFile

cmp eax, INVALID_HANDLE_VALUE			;if the file handle failed then output and exit
je failed2

mov outputfilehandle, eax

mov ecx, 100h							;user can enter up to 100 characters for the filename
mov edx, OFFSET prompt					;prompt user to enter input filename
call writestring

mov edx, OFFSET input_filename			;read it in
call readstring

mov edx, OFFSET input_filename			
call openinputfile						
cmp eax, INVALID_HANDLE_VALUE			;verify that the input file was vaild
je failed

mov fileHandle,eax						;save the inputfilehandle

start:									
mov eax, fileHandle						;put inputfilehandle into eax
mov ecx, 16								;allow 16 bytes to be read each iteration
mov edx, offset buffer					;mov the buffer's offset into edx
call readfromfile						;read
jc failed								;jump carry

mov eax, outputfilehandle				;put outputfilehandle into eax
mov edx, offset buffer					;mov buffer's offset into edx
call writetofile						
cmp eax, 16								;if 16 bytes were read in then loop start
jne getlastbytes						;if not then get the last bytes
je start

getlastbytes:
mov byte ptr [edx + eax], 0				;move a zero into the last location of the buffer
call writetofile						

jmp exitpoint								;if everything worked until here then jump until the exit point

failed:									;indicates a problem with the input file handle
mov edx, offset errormsg
call writestring

failed2:								;indicates a problem with the output file handle
mov edx, offset errormsg2
call writestring

exitpoint:									;exitpoint
call readchar							;hold the screen
call crlf								;carriage return line feed
