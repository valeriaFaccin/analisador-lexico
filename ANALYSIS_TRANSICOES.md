BODY -> D C
D -> int VAR ; D
D -> ''
C -> begin CMD end
CMD -> VAR = EXPR ; CMD
CMD -> if COND CMD
CMD -> for COND CMD
CMD -> ''
COND -> EXPR < EXPR
COND -> EXPR > EXPR
COND -> EXPR == EXPR
COND -> EXPR != EXPR
EXPR -> EXPR + TERM
EXPR -> EXPR - TERM
EXPR -> TERM
TERM -> TERM * FACT
TERM -> TERM / FACT
TERM -> FACT
FACT -> ( EXPR )
FACT -> VAR
FACT -> NUM



num = 2
var = 1
; = "26"
* = "24"
/ = "25"
+ = "22"
< = "20"
> = "21"
= = "27"
== = "29"
!= = "30"
- = "23"
begin = "7"
end = "13"
for = "17"
if = "14"
int = "10"

/*

    2 1 31 29 ...
0   <'R', 2>
1   <'A', 1>
2   <'E', 9>
3   
.
.
. 
*/
