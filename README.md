# Vec
C++ header only extensible Vector &amp; Matrix math/container library

Vector
------
A Vector is a specialisation of an array which hides the internal layout and function. This allows for the array storage to be fixed size, dynamic size, and/or dynamic capacity as desired on a case-by-case basis.

* Vector can be of a fixed size e.g. **Vector3f**
* Vector can be of dynamic size e.g. **VectorN10f**
* Vector can be of dynamic size and capacity e.g. **VectorXf**

Debug-Performance
-----------
Vec is efficient even under debug builds as it uses direct member access whenever possible within library functions. Developers may spend >90% of the time executing unoptimised code so this performance is important for an efficient workflow. Here we compare the Assembly (ASM) generated from the simple access of vector made with the code 'data.vec[0U]' vs 'data[0U]' where the later uses an overloaded-operator:
   
    [Clang 5.0 -O0]
    mov rsi, qword ptr [rbp - 8]
    movss xmm0, dword ptr [rsi] # xmm0 = mem[0],zero,zero,zero
    movss dword ptr [rbp - 20], xmm0
    
Normally only 'oerators[]' or member-accessors can be used to read/write member data many other vector libraries. Notice there is a function call generated for every access of the vectors data:

    [CLang 5.0 -O0]
    mov rdi, qword ptr [rbp - 8]
    mov rsi, rcx
    call VectorT<float, 3u, CartesianTag>::operator[](unsigned long) const
    movss xmm0, dword ptr [rax] # xmm0 = mem[0],zero,zero,zero
    movss dword ptr [rbp - 20], xmm0
    
    VectorT<float, 3u, CartesianTag>::operator[](unsigned long) const: # @VectorT<float, 3u, CartesianTag>::operator[](unsigned long) const
    push rbp
    mov rbp, rsp
    mov qword ptr [rbp - 8], rdi
    mov qword ptr [rbp - 16], rsi
    mov rsi, qword ptr [rbp - 8]
    mov rdi, qword ptr [rbp - 16]
    shl rdi, 2
    add rsi, rdi
    mov rax, rsi
    pop rbp
    ret

With optimisations enabled you should expect little difference in performance.
