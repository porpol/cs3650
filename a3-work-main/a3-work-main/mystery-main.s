# Write the assembly code for the main function of the mystery program
.text
.globl main

# int main(int argc, char *argv[])
# argc -> %rdi
# argv -> %rsi
# argv[1] -> -8(%rbp)
# argv[2] -> -16(%rbp)
# strtol(argv[1], NULL, 10) -> -8(%rbp)
# strtol(argv[2], NULL, 10) -> -16(%rbp)
# result -> %rdi
main:
  # Prologue:
  enter $16, $0

  # Body:
  # check if there are exactly 2 args
  cmp $3, %rdi
  jne invalid_args

  # storing the two input strings
  movq 8(%rsi), %rdx 
  movq 16(%rsi), %rcx
  movq %rdx, -8(%rbp) 
  movq %rcx, -16(%rbp) 

  # convert input strings to longs
  movq -8(%rbp), %rdi
  movq $0, %rsi 
  movq $10, %rdx 
  call strtol
  movq %rax, -8(%rbp) 

  movq -16(%rbp), %rdi
  movq $0, %rsi
  movq $10, %rdx
  call strtol
  movq %rax, -16(%rbp) 

  # calling crunch function
  movq -8(%rbp), %rdi
  movq -16(%rbp), %rsi
  call crunch
  movq %rax, %rdi
  cmp $0, %rdi
  jl hat # if(result < 0)
  je tea # if(result == 0)
  jmp beer # else

# print error msg
invalid_args:
  leaq error_msg(%rip), %rdi
  call puts
  movq $1, %rax
  
  # Epilogue:
  leave
  ret

hat:
  leaq hat_msg(%rip), %rdi
  call puts
  jmp done

tea:
  leaq tea_msg(%rip), %rdi
  call puts
  jmp done
  
beer:
  leaq beer_msg(%rip), %rdi
  call puts
  jmp done

done:
  movq $0, %rax

  # Epilogue:
  leave
  ret

.data
error_msg:
  .asciz "Two arguments required."
hat_msg:
  .asciz "hat"
tea_msg:
  .asciz "tea"
beer_msg:
  .asciz "beer"
