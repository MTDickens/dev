(* Change Penny *)

let changeP (x: int) = if (x >= 0) then 1 else 0

(* Two circumstances: use no nickel, or use at least one nickel *)
let rec changePN (x: int) = if (x >= 0) then changeP (x) + changePN(x - 5) else 0

let rec changePND (x: int) = if (x >= 0) then changePN(x) + changePND(x - 10) else 0

let rec changePNDQ (x: int) = if (x >= 0) then changePND(x) + changePNDQ(x - 25) else 0

let rec change (x: int) = if (x >= 0) then changePNDQ(x) + changePNDQ(x - 100) else 0