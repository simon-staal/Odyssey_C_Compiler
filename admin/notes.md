Codegen Notes
=============
For our codegen method (of ast node), we need the following parameters:
- Output stream: where the assembly is being printed to
- Context struct (TBD): Stores the info we need regarding stuff
- Destreg: register where the result of the operation is stored


Registers
---------
$0: Set to 0
$at (1): Don't touch
$v0-$v1 (2-3): Return value from subroutine (if value is 1 word then only $v0 is needed)
$a0-$a3 (4-7): Function arguments
$t0-$t9 (8-15, 24-25): Temporary registers (whatever we want)
$s0-$s7 (16-23): Saved registers (value is preserved across function calls)
$k0-$k1 (26-27): Don't touch
$gp (28): Global pointer (used for static global variables - probably ignore)
$sp (29): Stack pointer
$fp (30): Frame pointer
$ra (31): Return address in subroutine call


Stack Frame Shit
----------------
The stack grows downwards (i.e. decrement $sp to allocate space), and a stack frame contains 5 sections (order is top of the stack to bottom of the stack -- lower addressed memory to higher addressed memory):
- Argument section (must always allocate at least 4 words), used to store arguments that are passed to any subroutine that are called by the current subroutine. **Slots are allocated by the caller but used by the callee**
- Saved registers section, used to store the values in $s0-$s7 which need to be preserved across function calls (must copy values back before returning)
- Return address section, used to store $ra (so in can be restored after nested function call)
- Pad section, used to ensure the total size of the stack is a multiple of 8 (doubleword alighned)
- Local Data storage section, used for any local variable storage (enough words must be reserved for a function to fit all it's local data, including the value of any temporary registers it needs to preserve across subroutine calls)

**More specific stuff**
- For a function, search through it's scope to see if it contains a function call, if it doesn't it's a leaf function (i.e. doesn't need to store $ra in the stack)
- If a function doesn't contain any declarations in it's scope, it's a simple function that doesn't need any stack pointer changes
- If a function does contain declarations (i.e. local variables that need space to be stored), it's stack can just contain space for those local variables:
```
int g(int x, int y){
  int a[32];
  // Do stuff
  return a[0];
}
```
Would produce the following assembly:
```
addiu $sp,$sp,(-128) # push stack frame to allocate space for array of 32 ints (32*4 = 128)
... # do stuff
lw $v0,0($sp) # $sp is pointing at start of array a
addiu $sp,$sp,128 # pop stack frame
jr $ra # return
```

Stack implementation
--------------------
Current mental model for our stack allocation is as follows:
- At the start of a function call, stack decrements by 8, storing $ra and $fp (this is the bottom of the stack frame)
- When needed, local variables can be stored in the stack and the stack pointer get incremented as needed.
- When a sub-function call is encountered, all data registers are stored in the stack, and the required space for arguments of the called sub-function is created at the top of the stack.
- At the start of a function, the frame pointer will update to the stack pointer, which has decremented by 8 to store $ra and $fp. This means that when local variables are stored and the stack is decremented, the offset stored in the variable map will be relative to the frame pointer (i.e. 1st variable stored will have an offset of 4 provided it's size is 1 word).
