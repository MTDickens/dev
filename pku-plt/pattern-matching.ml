let rec listSum (l: int list) = 
	match l with
	| [] -> 0
	| (x :: y) -> x + listSum y