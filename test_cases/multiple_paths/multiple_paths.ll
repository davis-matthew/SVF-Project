; ModuleID = '/home/project/test_cases/multiple_paths/multiple_paths.c'
source_filename = "/home/project/test_cases/multiple_paths/multiple_paths.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@x = dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @init() #0 {
  store i32 3, i32* @x, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @sink() #0 {
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @src() #0 {
  %1 = load i32, i32* @x, align 4
  %2 = icmp ne i32 %1, 3
  br i1 %2, label %3, label %4

3:                                                ; preds = %0
  call void @init()
  br label %4

4:                                                ; preds = %3, %0
  call void @sink()
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  store i32 0, i32* @x, align 4
  call void @src()
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{i32 7, !"frame-pointer", i32 2}
!3 = !{!"clang version 14.0.0"}
