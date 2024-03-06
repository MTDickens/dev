let factorial n =
  let result = ref 1 in
  for i = 2 to n do
    result := i * !result
  done;
  !result

let () =
  print_endline "Enter a number:";
  let n = read_int () in
  let result = factorial n in
  print_endline ("Factorial of " ^ string_of_int n ^ " is " ^ string_of_int result)
