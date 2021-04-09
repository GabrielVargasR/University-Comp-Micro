.global main   
.section .text   
.extern printf   
.extern scanf   
   
main:   
@_assign:   
mov r8, #160 
ldr r9, =foo 
str r8, [r9] 
   
@_assign:   
mov r8, #231 
ldr r9, =bar 
str r8, [r9] 
   
mov r0, #0 
cmp r0, #0 
beq _Label2  
mov r0, #10 
b _Label3  
_Label2 :  
mov r0, #23 
_Label3 :  
ldr r9, =_Temp1 
str r0, [r9] 
   
@_assign:   
ldr r8, =_Temp1 
ldr r8, [r8] 
ldr r9, =var 
str r8, [r9] 
   
@_write:   
ldr r0, =message 
ldr r1, =foo 
ldr r1, [r1] 
bl printf  
   
@_write:   
ldr r0, =message 
mov r2, #168 
ldr r1,  =_Temp4 
str r2, [r1] 
ldr r1, [r1] 
bl printf  
   
@_write:   
ldr r0, =message 
ldr r1, =bar 
ldr r1, [r1] 
bl printf  
   
@_write:   
ldr r0, =message 
ldr r1, =var 
ldr r1, [r1] 
bl printf  
   
_end:   
mov r7, #0x1 
mov r0, #13 
swi 0  
   
