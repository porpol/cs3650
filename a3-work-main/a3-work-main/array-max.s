# Write the assembly code for the array_max function
.text
.globl array_max

# unsigned long array_max(unsigned long n, unsigned long *items)
# n -> %rdi
# items -> %rsi
# max -> %rax
# i -> %rdx
# items[i] -> %rcx
array_max:
  # Prologue:
  enter $16, $0

  # Body:
  # store max
  movq (%rsi), %rax # max = items[0]

  # store i (index)
  movq $0, %rdx # i = 0

loop:
  # check if out of bounds
  cmp %rdi, %rdx
  jge done # if(i >= n)

  # store current array elem
  movq (%rsi, %rdx, 8), %rcx

  # increment i
  inc %rdx # i++

  # check if current array elem is greater than max
  cmp %rax, %rcx
  jg update_max # if(items[i] > max)
  jmp loop

update_max:
  movq %rcx, %rax # max = items[i]
  jmp loop

done:
  # Epilogue:
  leave
  ret