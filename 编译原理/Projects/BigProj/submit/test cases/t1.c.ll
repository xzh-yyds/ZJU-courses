; ModuleID = 't1.c'
source_filename = "t1.c"

@ans = internal global i32 0
@0 = private unnamed_addr constant [9 x i8] c"ans = %d\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @gcd(i32 %0, i32 %1) {
entry:
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  %b = alloca i32, align 4
  store i32 %1, i32* %b, align 4
  %2 = load i32, i32* %b, align 4
  %ifequal = icmp eq i32 %2, 0
  br i1 %ifequal, label %then, label %else

then:                                             ; preds = %entry
  %3 = load i32, i32* %a, align 4
  ret i32 %3

else:                                             ; preds = %entry
  %4 = load i32, i32* %b, align 4
  %5 = load i32, i32* %a, align 4
  %6 = load i32, i32* %b, align 4
  %7 = srem i32 %5, %6
  %8 = call i32 @gcd(i32 %4, i32 %7)
  ret i32 %8
}

define i32 @main() {
entry:
  %0 = load i32, i32* @ans, align 4
  %1 = call i32 @gcd(i32 9, i32 36)
  %2 = call i32 @gcd(i32 3, i32 6)
  %3 = mul i32 %1, %2
  store i32 %3, i32* @ans, align 4
  %4 = load i32, i32* @ans, align 4
  %5 = load i32, i32* @ans, align 4
  %call = call i32 (...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @0, i32 0, i32 0), i32 %5)
  %return = call i32 (...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  ret i32 0
}

declare i32 @printf(...)
