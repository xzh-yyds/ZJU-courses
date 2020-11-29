; ModuleID = 't2.c'
source_filename = "t2.c"

@k = internal global i32 0
@f = internal global i32 0
@0 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @go(i32 %0, i32 %1) {
entry:
  %b = alloca i32, align 4
  store i32 %0, i32* %b, align 4
  %a = alloca i32, align 4
  store i32 %1, i32* %a, align 4
  %fk = alloca i32, align 4
  store i32 0, i32* %fk, align 4
  %t = alloca double, align 8
  store double 0.000000e+00, double* %t, align 8
  %2 = load i32, i32* %a, align 4
  %greater = icmp sgt i32 %2, 0
  br i1 %greater, label %then, label %else

then:                                             ; preds = %entry
  %3 = load i32, i32* %a, align 4
  %4 = load i32, i32* %b, align 4
  %5 = load i32, i32* %a, align 4
  %6 = sub i32 %5, 1
  %7 = call i32 @go(i32 %4, i32 %6)
  %8 = mul i32 %3, %7
  ret i32 %8

else:                                             ; preds = %entry
  ret i32 1
}

define i32 @main() {
entry:
  %0 = load i32, i32* @k, align 4
  store i32 0, i32* @k, align 4
  %1 = load i32, i32* @k, align 4
  %2 = load i32, i32* @f, align 4
  %3 = load i32, i32* @k, align 4
  %4 = call i32 @go(i32 %3, i32 5)
  store i32 %4, i32* @f, align 4
  %5 = load i32, i32* @f, align 4
  %6 = load i32, i32* @f, align 4
  %call = call i32 (...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32 %6)
  %return = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  %7 = load i32, i32* @k, align 4
  %call1 = call i32 (...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32 %7)
  %return2 = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  ret i32 0
}

declare i32 @printf(...)
