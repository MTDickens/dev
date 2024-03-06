let rec string_to_char_list (s: string) =
  match s with
  | "" -> []
  | x -> (String.get x 0) :: (string_to_char_list (String.sub x 1 ((String.length x) - 1)))
  
let rec split_char_list l = 
  let rec loop (w: char list) l: char list list = 
    match w, l with
    | [], []      -> [] (* When w is of [], we don't add w to the list*)
    | _, []       -> w::[]
    | [], ' '::xs -> loop [] (xs) (* When w is of [], we don't add w to the list*)
    | _, ' '::xs  -> w::(loop [] xs)
    | _, x::xs    -> loop (w@[x]) xs
  in loop [] l
      

(* "Haiyaa!  Uncle Roger disappointed~" -> ["Haiyaa!", "Uncle", "Roger", "disappointed~"]*)
let split_string (s: string) = split_char_list(string_to_char_list s)