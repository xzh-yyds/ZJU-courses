; ModuleID = 't3.c'
source_filename = "t3.c"

@i = internal global i32 0
@0 = private unnamed_addr constant [14 x i8] c"\22hello,%d\\0D\22\00", align 1

define i32 @go(i32 %0) {
entry:
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  %1 = load i32, i32* %a, align 4
  %ifequal = icmp eq i32 %1, 1
  br i1 %ifequal, label %then, label %else

then:                                             ; preds = %entry
  ret i32 1

else:                                             ; preds = %entry
  %2 = load i32, i32* %a, align 4
  %ifequal1 = icmp eq i32 %2, 2
  br i1 %ifequal1, label %then2, label %else3

then2:                                            ; preds = %else
  ret i32 1

else3:                                            ; preds = %else
  %3 = load i32, i32* %a, align 4
  %4 = sub i32 %3, 1
  %5 = call i32 @go(i32 %4)
  %6 = load i32, i32* %a, align 4
  %7 = sub i32 %6, 2
  %8 = call i32 @go(i32 %7)
  %9 = add i32 %5, %8
  ret i32 %9
}

define i32 @main() {
entry:
  %0 = load i32, i32* @i, align 4
  %1 = call i32 @go(i32 10)
  store i32 %1, i32* @i, align 4
  %2 = load i32, i32* @i, align 4
  %3 = load i32, i32* @i, align 4
  %call = call i32 (...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0, i32 0, i32 0), i32 %3)
  ret i32 0
}

declare i32 @printf(...)
