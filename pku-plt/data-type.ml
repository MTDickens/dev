type ast =
  ANum of int
  | APlus of ast * ast
  | AMinus of ast * ast
  | ATimes of ast * ast ;;

let rec eval (a: ast) =
  match a with
  | ANum n -> n
  | APlus (x,y) -> (eval x) + (eval y)
  | AMinus (x,y) -> (eval x) - (eval y)
  | ATimes (x,y) -> (eval x) * (eval y) ;;