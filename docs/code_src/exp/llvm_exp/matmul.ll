; Function Signature: matmul(Array{Int64, 2}, Array{Int64, 2})
;  @ REPL[6]:1 within `matmul`
define nonnull ptr @julia_matmul_6754(ptr noundef nonnull align 8 dereferenceable(32) %"A::Array", ptr noundef nonnull align 8 dereferenceable(32) %"B::Array") #0 {
top:
  %gcframe1 = alloca [3 x ptr], align 16
  call void @llvm.memset.p0.i64(ptr align 16 %gcframe1, i8 0, i64 24, i1 true)
  %thread_ptr = call ptr asm "movq %fs:0, $0", "=r"() #12
  %tls_ppgcstack = getelementptr i8, ptr %thread_ptr, i64 -8
  %tls_pgcstack = load ptr, ptr %tls_ppgcstack, align 8
  store i64 4, ptr %gcframe1, align 16
  %frame.prev = getelementptr inbounds ptr, ptr %gcframe1, i64 1
  %task.gcstack = load ptr, ptr %tls_pgcstack, align 8
  store ptr %task.gcstack, ptr %frame.prev, align 8
  store ptr %gcframe1, ptr %tls_pgcstack, align 8
;  @ REPL[6]:2 within `matmul`
; ┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:114 within `*`
; │┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:117 within `matprod_dest`
; ││┌ @ array.jl:191 within `size`
     %0 = getelementptr inbounds i8, ptr %"A::Array", i64 16
     %.size.sroa.0.0.copyload = load i64, ptr %0, align 8
     %.size3.sroa.1.0..sroa_idx = getelementptr inbounds i8, ptr %"B::Array", i64 24
     %.size3.sroa.1.0.copyload = load i64, ptr %.size3.sroa.1.0..sroa_idx, align 8
; ││└
; ││┌ @ array.jl:372 within `similar`
; │││┌ @ boot.jl:592 within `Array` @ boot.jl:582
; ││││┌ @ boot.jl:571 within `checked_dims`
; │││││┌ @ boot.jl:541 within `_checked_mul_dims`
        %1 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 %.size.sroa.0.0.copyload, i64 %.size3.sroa.1.0.copyload)
        %2 = extractvalue { i64, i1 } %1, 0
        %3 = extractvalue { i64, i1 } %1, 1
; ││││││ @ boot.jl:544 within `_checked_mul_dims`
        %4 = icmp ugt i64 %.size.sroa.0.0.copyload, 9223372036854775806
        %5 = or i1 %4, %3
; ││││││ @ boot.jl:545 within `_checked_mul_dims`
        %6 = icmp ugt i64 %.size3.sroa.1.0.copyload, 9223372036854775806
        %7 = or i1 %6, %5
; │││││└
; │││││ @ boot.jl:572 within `checked_dims`
       br i1 %7, label %L13, label %L17

L13:                                              ; preds = %top
       %8 = call [1 x ptr] @j_ArgumentError_6759(ptr nonnull @"jl_global#6760.jit")
       %gc_slot_addr_0 = getelementptr inbounds ptr, ptr %gcframe1, i64 2
       %9 = extractvalue [1 x ptr] %8, 0
       store ptr %9, ptr %gc_slot_addr_0, align 16
       %ptls_field = getelementptr inbounds ptr, ptr %tls_pgcstack, i64 2
       %ptls_load = load ptr, ptr %ptls_field, align 8
       %"box::ArgumentError" = call noalias nonnull align 8 dereferenceable(16) ptr @ijl_gc_pool_alloc_instrumented(ptr %ptls_load, i32 752, i32 16, i64 136385482142064) #10
       %"box::ArgumentError.tag_addr" = getelementptr inbounds i64, ptr %"box::ArgumentError", i64 -1
       store atomic i64 136385482142064, ptr %"box::ArgumentError.tag_addr" unordered, align 8
       store ptr %9, ptr %"box::ArgumentError", align 8
       call void @ijl_throw(ptr nonnull %"box::ArgumentError")
       unreachable

L17:                                              ; preds = %top
; ││││└
; ││││┌ @ boot.jl:535 within `new_as_memoryref`
; │││││┌ @ boot.jl:512 within `GenericMemory`
        %.not = icmp eq i64 %2, 0
        br i1 %.not, label %L19, label %L21

L19:                                              ; preds = %L17
; ││││││ @ boot.jl:514 within `GenericMemory`
        %.instance = load atomic ptr, ptr getelementptr inbounds (ptr, ptr @"+Core.GenericMemory#6765.jit", i64 4) unordered, align 256
        %.not19 = icmp eq ptr %.instance, null
        br i1 %.not19, label %fail, label %L23

L21:                                              ; preds = %L17
; ││││││ @ boot.jl:516 within `GenericMemory`
        %"Memory{Int64}[]" = call ptr @jl_alloc_genericmemory(ptr nonnull @"+Core.GenericMemory#6765.jit", i64 %2)
        br label %L23

L23:                                              ; preds = %L21, %L19
        %value_phi = phi ptr [ %"Memory{Int64}[]", %L21 ], [ %.instance, %L19 ]
; │││││└
; │││││┌ @ boot.jl:522 within `memoryref`
        %.data_ptr = getelementptr inbounds { i64, ptr }, ptr %value_phi, i64 0, i32 1
        %10 = load ptr, ptr %.data_ptr, align 8
        %gc_slot_addr_022 = getelementptr inbounds ptr, ptr %gcframe1, i64 2
        store ptr %value_phi, ptr %gc_slot_addr_022, align 16
; ││││└└
      %ptls_field29 = getelementptr inbounds ptr, ptr %tls_pgcstack, i64 2
      %ptls_load30 = load ptr, ptr %ptls_field29, align 8
      %"new::Array" = call noalias nonnull align 8 dereferenceable(48) ptr @ijl_gc_pool_alloc_instrumented(ptr %ptls_load30, i32 848, i32 48, i64 136385430811568) #10
      %"new::Array.tag_addr" = getelementptr inbounds i64, ptr %"new::Array", i64 -1
      store atomic i64 136385430811568, ptr %"new::Array.tag_addr" unordered, align 8
      %11 = getelementptr inbounds ptr, ptr %"new::Array", i64 1
      store ptr %10, ptr %"new::Array", align 8
      store ptr %value_phi, ptr %11, align 8
      %"new::Array.size_ptr" = getelementptr inbounds i8, ptr %"new::Array", i64 16
      store i64 %.size.sroa.0.0.copyload, ptr %"new::Array.size_ptr", align 8
      %"new::Tuple.sroa.2.0.new::Array.size_ptr.sroa_idx" = getelementptr inbounds i8, ptr %"new::Array", i64 24
      store i64 %.size3.sroa.1.0.copyload, ptr %"new::Tuple.sroa.2.0.new::Array.size_ptr.sroa_idx", align 8
      store ptr %"new::Array", ptr %gc_slot_addr_022, align 16
; │└└└
; │┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:253 within `mul!` @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:285
; ││┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:287 within `_mul!`
; │││┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:868 within `generic_matmatmul!`
      %12 = call nonnull ptr @"j__generic_matmatmul!_6770"(ptr nonnull %"new::Array", ptr nonnull %"A::Array", ptr nonnull %"B::Array", ptr nocapture nonnull readonly @"_j_const#1")
      %frame.prev32 = load ptr, ptr %frame.prev, align 8
      store ptr %frame.prev32, ptr %tls_pgcstack, align 8
; └└└└
  ret ptr %12

fail:                                             ; preds = %L19
; ┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:114 within `*`
; │┌ @ /cache/build/builder-demeter6-3/julialang/julia-release-1-dot-11/usr/share/julia/stdlib/v1.11/LinearAlgebra/src/matmul.jl:117 within `matprod_dest`
; ││┌ @ array.jl:372 within `similar`
; │││┌ @ boot.jl:592 within `Array` @ boot.jl:582
; ││││┌ @ boot.jl:535 within `new_as_memoryref`
; │││││┌ @ boot.jl:514 within `GenericMemory`
        %jl_undefref_exception = load ptr, ptr @jl_undefref_exception, align 8
        call void @ijl_throw(ptr nonnull %jl_undefref_exception)
        unreachable
; └└└└└└
}
