; ModuleID = 't4.c'
source_filename = "t4.c"

@0 = private unnamed_addr constant [7 x i8] c"a = %d\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [7 x i8] c"a = %d\00", align 1
@3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@4 = private unnamed_addr constant [7 x i8] c"a = %d\00", align 1
@5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@6 = private unnamed_addr constant [7 x i8] c"b = %d\00", align 1
@7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @main() {
entry:
  %a = alloca i32, align 4
  store i32 3, i32* %a, align 4
  %0 = load i32, i32* %a, align 4
  %1 = add i32 %0, 4
  store i32 %1, i32* %a, align 4
  %2 = load i32, i32* %a, align 4
  %3 = load i32, i32* %a, align 4
  %call = call i32 (...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @0, i32 0, i32 0), i32 %3)
  %return = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  %4 = load i32, i32* %a, align 4
  %ifequal = icmp eq i32 %4, 4
  %b = alloca i32, align 4
  store i32 1, i32* %b, align 4
  %5 = load i32, i32* %a, align 4
  %6 = load i32, i32* %a, align 4
  %7 = add i32 %5, %6
  store i32 %7, i32* %a, align 4
  %8 = load i32, i32* %a, align 4
  %9 = load i32, i32* %b, align 4
  %10 = load i32, i32* %a, align 4
  %call1 = call i32 (...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @2, i32 0, i32 0), i32 %10)
  %return2 = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  br label %con

loop:                                             ; preds = %con
  %11 = load i32, i32* %b, align 4
  %12 = load i32, i32* %a, align 4
  %13 = add i32 %11, %12
  store i32 %13, i32* %b, align 4
  %14 = load i32, i32* %b, align 4
  %15 = load i32, i32* %a, align 4
  %16 = add i32 %15, 1
  store i32 %16, i32* %a, align 4
  %17 = load i32, i32* %a, align 4
  br label %con

con:                                              ; preds = %loop, %entry
  %18 = load i32, i32* %a, align 4
  %less = icmp slt i32 %18, 100
  br i1 %less, label %loop, label %outer

outer:                                            ; preds = %con
  %19 = load i32, i32* %a, align 4
  %call3 = call i32 (...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @4, i32 0, i32 0), i32 %19)
  %return4 = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @5, i32 0, i32 0))
  %20 = load i32, i32* %b, align 4
  %call5 = call i32 (...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @6, i32 0, i32 0), i32 %20)
  %return6 = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @7, i32 0, i32 0))
  ret i32 0
}

declare i32 @printf(...)
